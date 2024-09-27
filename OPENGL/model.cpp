#include "model.h"
#include <sstream>

ModelUPtr Model::Load ( const std::string& filename ) {
    auto model = ModelUPtr ( new Model ( ) );
  
    if ( !model->LoadByAssimp ( filename ) )
        return nullptr;
    return std::move ( model );
}


bool Model::LoadByAssimp ( const std::string& filename ) {
    Assimp::Importer importer;
    auto scene = importer.ReadFile ( filename , aiProcess_Triangulate | aiProcess_FlipUVs );

    this->filename = filename;

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
    vertices.resize ( mesh->mNumVertices );
    for ( uint32_t i = 0; i < mesh->mNumVertices; i++ ) {
        auto& v = vertices[ i ];
        v.position = glm::vec3 ( mesh->mVertices[ i ].x , mesh->mVertices[ i ].y , mesh->mVertices[ i ].z );
        v.normal = glm::vec3 ( mesh->mNormals[ i ].x , mesh->mNormals[ i ].y , mesh->mNormals[ i ].z );
        v.texCoord = glm::vec2 ( mesh->mTextureCoords[ 0 ][ i ].x , mesh->mTextureCoords[ 0 ][ i ].y );
    }

    std::vector<uint32_t> indices;
    indices.resize ( mesh->mNumFaces * 3 );
    for ( uint32_t i = 0; i < mesh->mNumFaces; i++ ) {
        indices[ 3 * i ] = mesh->mFaces[ i ].mIndices[ 0 ];
        indices[ 3 * i + 1 ] = mesh->mFaces[ i ].mIndices[ 1 ];
        indices[ 3 * i + 2 ] = mesh->mFaces[ i ].mIndices[ 2 ];
    }

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