#include "model.h"
#include <sstream>

ModelPtr Model::Load ( const std::string& filename ) {
    auto model = ModelUPtr ( new Model ( ) );
  
    if ( !model->LoadByAssimp ( filename ) )
        return nullptr;
    return std::move ( model );
}


bool Model::LoadByAssimp ( const std::string& filename ) {
    Assimp::Importer importer;
    auto scene = importer.ReadFile ( filename , aiProcess_Triangulate | aiProcess_FlipUVs );

    this->filename = filename;
    std::cerr << "Successed to load model :" << filename << std::endl;
    if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) {
        std::cerr << "Failed to load model :" << filename << std::endl;
        return false;
    }

    auto dirname = filename.substr ( 0 , filename.find_last_of ( "/" ) );

    //람다 함수
    auto LoadTexture = [&]( aiMaterial* material , aiTextureType type ) -> TexturePtr {
        if ( material->GetTextureCount ( type ) <= 0 )
            return nullptr;
        aiString filepath;
        material->GetTexture ( type , 0 , &filepath );


        if ( filepath.data[ 0 ] == '*' ) {
            // Assimp 내장 텍스처일 경우 처리
            int textureIndex = std::stoi ( filepath.C_Str ( ) + 1 ); // "*0"에서 인덱스 추출
            auto embeddedTexture = scene->mTextures[ textureIndex ];
            std::cerr << "Texture embeddedTexture : " << embeddedTexture->pcData << std::endl;
            if ( embeddedTexture && embeddedTexture->mHeight == 0 ) {
                // 텍스처가 메모리에 포함되어 있음 (compressed format)
                auto image = Image::LoadFromMemory ( reinterpret_cast< const unsigned char* >( embeddedTexture->pcData ) ,
                                                   embeddedTexture->mWidth , false ); // flipVertical 값을 설정
                return Texture::CreateFromImage ( image.get ( ) );
            }
        }

        // std::stringstream을 사용하여 경로 생성
        std::stringstream ss;
        ss << dirname << "/" << filepath.C_Str ( );
        std::string fullpath = ss.str ( );

        auto image = Image::Load ( fullpath );
        if ( !image )
            return nullptr;

        return Texture::CreateFromImage ( image.get ( ) );
     };

    for ( uint32_t i = 0; i < scene->mNumMaterials; i++ ) {
        auto material = scene->mMaterials[ i ];
        auto glMaterial = Material::Create ( );
        glMaterial->diffuse = LoadTexture ( material , aiTextureType_DIFFUSE );
        glMaterial->specular = LoadTexture ( material , aiTextureType_SPECULAR );
        m_materials.push_back ( std::move ( glMaterial ) );
    }

    ProcessNode ( scene->mRootNode , scene );
    return true;
}

//트리구조로 되어있어 재귀적으로 함수를 호출해서 세팅함
void Model::ProcessNode ( aiNode* node , const aiScene* scene ) {
    for ( uint32_t i = 0; i < node->mNumMeshes; i++ ) {
        auto meshIndex = node->mMeshes[ i ];
        auto mesh = scene->mMeshes[ meshIndex ];
        ProcessMesh ( mesh , scene );
    }

    for ( uint32_t i = 0; i < node->mNumChildren; i++ ) {
        ProcessNode ( node->mChildren[ i ] , scene );
    }
}

//삼각형 MESH에 대한 세팅
void Model::ProcessMesh ( aiMesh* mesh , const aiScene* scene ) {
    std::cerr << "process mesh: "<< mesh->mName.C_Str ( ) <<" vert "<< mesh->mNumVertices <<"face" << mesh->mNumFaces << std::endl;
 

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;


    vertices.resize ( mesh->mNumVertices );
    for ( uint32_t i = 0; i < mesh->mNumVertices; i++ ) {

        
        auto& v = vertices[ i ];
        InitVertexBoneData ( v );

        v.position = glm::vec3 ( mesh->mVertices[ i ].x , mesh->mVertices[ i ].y , mesh->mVertices[ i ].z );
        v.normal = glm::vec3 ( mesh->mNormals[ i ].x , mesh->mNormals[ i ].y , mesh->mNormals[ i ].z );

    
        if ( mesh->mTextureCoords[ 0 ] )
        {
            glm::vec2 vec;
            vec.x = ( mesh->mTextureCoords[ 0 ][ i ].x );
            vec.y = ( mesh->mTextureCoords[ 0 ][ i ].y );
            v.texCoord = vec;
        }
        else // 존재하지 않을 경우 그냥 0을 넣어주기
        {
            v.texCoord = glm::vec2 ( 0.f , 0.f );
        }
    
    
    }

   
    indices.resize ( mesh->mNumFaces * 3 );
    for ( uint32_t i = 0; i < mesh->mNumFaces; i++ ) {
        indices[ 3 * i ] = mesh->mFaces[ i ].mIndices[ 0 ];
        indices[ 3 * i + 1 ] = mesh->mFaces[ i ].mIndices[ 1 ];
        indices[ 3 * i + 2 ] = mesh->mFaces[ i ].mIndices[ 2 ];
    }

    ExtractBoneWeightForVertices ( vertices , mesh , scene );
    std::cerr << "MESH" << std::endl;

    auto glMesh = Mesh::Create ( vertices , indices , GL_TRIANGLES );
    if ( mesh->mMaterialIndex >= 0 )
        glMesh->SetMaterial ( m_materials[ mesh->mMaterialIndex ] );

    m_meshes.push_back ( std::move ( glMesh ) );

    std::cerr << "process mesh complete " << std::endl;


}

void Model::Draw ( const Program* program ) const {
    for ( auto& mesh : m_meshes ) {
        mesh->Draw ( program );
    }
}

void Model::InitVertexBoneData ( Vertex& vertex )
{
    for ( int i = 0; i < MAX_BONE_INFLUENCE; i++ )
    {
        vertex.m_BoneIDs[ i ] = -1;
        vertex.m_Weights[ i ] = 0.f;
    }
}

void Model::SetVertexBoneData ( Vertex& vertex , int boneID , float weight )
{
    for ( int i = 0; i < MAX_BONE_INFLUENCE; i++ )
    {
        if ( vertex.m_BoneIDs[ i ] < 0 )
        {
            // 하나만 채우고 도망가기
            vertex.m_Weights[ i ] = weight;
            vertex.m_BoneIDs[ i ] = boneID;
            break;
        }
    }
}

void Model::ExtractBoneWeightForVertices ( std::vector<Vertex>& vertices , aiMesh* mesh , const aiScene* scene )
{
    for ( int boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++ )
    {
        int boneID = -1;

        std::string boneName = mesh->mBones[ boneIndex ]->mName.C_Str ( );

        if ( boneInfoMap.find ( boneName ) == boneInfoMap.end ( ) )
        {
            BoneInfo boneInfo;
            boneInfo.id = boneCounter;
            auto offsetMat = mesh->mBones[ boneIndex ]->mOffsetMatrix;
            boneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat (
                    mesh->mBones[ boneIndex ]->mOffsetMatrix
            );

            boneInfoMap[ boneName ] = boneInfo;
            boneID = boneCounter;
            boneCounter++;
        }
        else
        {
            boneID = boneInfoMap[ boneName ].id;
        }
        assert ( boneID != -1 );
        auto weights = mesh->mBones[ boneIndex ]->mWeights;
        int numWeights = mesh->mBones[ boneIndex ]->mNumWeights;

        for ( int weightIndex = 0; weightIndex < numWeights; weightIndex++ )
        {
            int vertexId = weights[ weightIndex ].mVertexId;
            float weight = weights[ weightIndex ].mWeight;
            assert ( vertexId <= vertices.size ( ) );
            SetVertexBoneData ( vertices[ vertexId ] , boneID , weight );
        }
    }
}