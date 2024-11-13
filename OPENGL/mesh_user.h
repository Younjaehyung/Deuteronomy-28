#pragma once

#include "common_include.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "program.h"

CLASS_PTR ( Mesh );
CLASS_PTR ( UBOBUFFER );

const int MAX_BONE_INFLUENCE = 4;
struct Vertex {
    Vertex ( ) {}

    Vertex ( float px , float py , float pz )
    {
        position.x = px; position.y = py; position.z = pz;
        texCoord.s = 0.f; texCoord.t = 0.f;
        normal.x = 0.f; normal.y = 0.f; normal.z = 0.f;
    }

    Vertex ( glm::vec3 pv , glm::vec3 nv , glm::vec2 tv )
    {
        position = pv;
        normal = nv;
        texCoord = tv;
    }

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    //bone indexes which will influence this vertex
    int m_BoneIDs[ 4 ] = {};
    //weights from each bone
    float m_Weights[ 4 ] = {};
};


CLASS_PTR ( Material );
class Material {
public:
    static MaterialUPtr Create ( ) {
        return MaterialUPtr ( new Material ( ) );
    }
    TexturePtr diffuse;
    TexturePtr specular;
    float shininess{ 32.0f };

    void SetToProgram ( const Program* program ) const; //텍스쳐를 프로그램에 세팅

private:
    Material ( ) {}
};

class Mesh {
public:
    static MeshUPtr Create (const std::vector<Vertex>& vertices ,const std::vector<uint32_t>& indices ,uint32_t primitiveType );
    
   
    static MeshUPtr CreateBox ( );
    static MeshUPtr CreatePlane ( );

    const VertexLayout* GetVertexLayout ( ) const {
        return m_vertexLayout.get ( );
    }

    BufferPtr GetVertexBuffer ( ) const { return m_vertexBuffer; }
    BufferPtr GetIndexBuffer ( ) const { return m_indexBuffer; }

    void SetMaterial ( MaterialPtr material ) { m_material = material; }
    MaterialPtr GetMaterial ( ) const { return m_material; }

    void Draw ( const Program* program ) const;

private:
    Mesh ( ) {}
    void Init (
      const std::vector<Vertex>& vertices ,
      const std::vector<uint32_t>& indices ,
      uint32_t primitiveType );



    uint32_t m_primitiveType{ GL_TRIANGLES };
    VertexLayoutUPtr m_vertexLayout;
    BufferPtr m_vertexBuffer;
    BufferPtr m_indexBuffer;

    MaterialPtr m_material;
};

class UBOBUFFER {
    uint32_t uboBones{ 0 };
    bool Init ( uint32_t MAX_BONES ) {
        glGenBuffers ( 1 , &uboBones );
        glBindBuffer ( GL_UNIFORM_BUFFER , uboBones );
        glBufferData ( GL_UNIFORM_BUFFER , sizeof ( glm::mat4 ) * MAX_BONES , nullptr , GL_DYNAMIC_DRAW );
        glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
        return true;
    }
    UBOBUFFER ( ) {}
public:
    static UBOBUFFERUPtr Create ( uint32_t MAX_BONES ) {
        auto UBO = UBOBUFFERUPtr ( new UBOBUFFER ( ) );
        if ( !UBO->Init ( MAX_BONES ) )
            return nullptr;
        return std::move ( UBO );
    }
    
   

    void UpdateBoneMatrices ( const std::vector<glm::mat4>& transforms ) {
        glBindBuffer ( GL_UNIFORM_BUFFER , uboBones );
        glBufferSubData ( GL_UNIFORM_BUFFER , 0 , sizeof ( glm::mat4 ) * transforms.size ( ) , transforms.data ( ) );
        glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
    }

    void Bind ( uint32_t programID ,const std::string& UniformName) {
        uint32_t blockIndex = glGetUniformBlockIndex ( programID , UniformName.c_str() );
        glUniformBlockBinding ( programID , blockIndex , 0 );
        glBindBufferBase ( GL_UNIFORM_BUFFER , 0 , uboBones );

    }

};