#pragma once

#include "common_include.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "program.h"
#include <assimp/light.h>

CLASS_PTR ( Mesh );
CLASS_PTR ( UBOBUFFER );
CLASS_PTR ( UBOBUFFER_L );
CLASS_PTR ( UBOBUFFER_LIGHT );
const int MAX_LIGHTS = 20;
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
    //원래 4
    int m_BoneIDs[ MAX_BONE_INFLUENCE ];
    //weights from each bone
    float m_Weights[ MAX_BONE_INFLUENCE ];
};



struct LightD {
    //const char* name;
    aiLightSourceType type; // 조명 유형 (예: 점광, 방향광, 스포트라이트 등)

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 direction = glm::vec3 ( 0.0f );

    glm::vec3 colorAmbient = glm::vec3 ( 0.0f );
    glm::vec3 colorDiffuse = glm::vec3 ( 0.0f );
    glm::vec3 colorSpecular = glm::vec3 ( 0.0f );


    float cutoff;      // 스포트라이트 각도
    float outerCutoff; // 스포트라이트 외각 각도
    glm::vec3 attenuation; // 감쇠 계수 (Point Light에 대한 감쇠 계수)
};

struct Light_ORI {
    int directional = 0 ;

    glm::vec3 position{ glm::vec3 ( 3.0f, 3.0f, 3.0f ) }; //광원의 위치
    glm::vec3 direction{ glm::vec3 ( -0.2f, -1.0f, -0.3f ) };	//Directional Light
    glm::vec2 cutoff{ glm::vec2 ( 20.0f, 5.0f ) };	//Spot Light 보이는 부분
   
    glm::vec3 attenuation;
    
    glm::vec3 ambient{ glm::vec3 ( 0.0f, 0.0f, 0.0f ) };  //광원의 색
    glm::vec3 diffuse{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };  //오브젝트의 색
    glm::vec3 specular{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };
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

class UBOBUFFER_L {
public:
   

    void Bind ( GLuint program , const std::string& name ) {
        GLuint blockIndex = glGetUniformBlockIndex ( program , name.c_str ( ) );
        glUniformBlockBinding ( program , blockIndex , 0 );
        glBindBufferBase ( GL_UNIFORM_BUFFER , 0 , ubo_bufferID );
    }

    void UpdateData ( const std::vector<LightD>& lightData ) {
        glBindBuffer ( GL_UNIFORM_BUFFER , ubo_bufferID );
        glBufferSubData ( GL_UNIFORM_BUFFER , 0 , sizeof ( LightD ) * lightData.size ( ) , lightData.data ( ) );
        glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
    }

    static UBOBUFFER_LUPtr Create ( uint32_t lights ) {
        auto UBO = UBOBUFFER_LUPtr ( new UBOBUFFER_L ( ) );
        if ( !UBO->Init ( lights ) )
            return nullptr;
        return std::move ( UBO );
    }

private:
    bool Init ( uint32_t lights ) {
        glGenBuffers ( 1 , &ubo_bufferID );
        glBindBuffer ( GL_UNIFORM_BUFFER , ubo_bufferID );
        glBufferData ( GL_UNIFORM_BUFFER , sizeof ( LightD ) * lights , nullptr , GL_DYNAMIC_DRAW );
        glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
        return true;
    }
    UBOBUFFER_L ( ) {}

    uint32_t ubo_bufferID;
};


class UBOBUFFER_LIGHT {
public:


    void Bind ( uint32_t program , const std::string& name ) {
        uint32_t blockIndex = glGetUniformBlockIndex ( program , name.c_str ( ) );
        glUniformBlockBinding ( program , blockIndex , 0 );
        glBindBufferBase ( GL_UNIFORM_BUFFER , 0 , ubo_bufferID );
    }

    void UpdateData ( const std::vector<Light_ORI>& lightData ) {
        glBindBuffer ( GL_UNIFORM_BUFFER , ubo_bufferID );
        glBufferSubData ( GL_UNIFORM_BUFFER , 0 , sizeof ( Light_ORI ) * lightData.size ( ) , lightData.data ( ) );
        //std::cout << "DATA :" << lightData.size ( ) << std::endl;
        glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
    }

    static UBOBUFFER_LIGHTUPtr Create ( uint32_t lights ) {
        auto UBO = UBOBUFFER_LIGHTUPtr ( new UBOBUFFER_LIGHT ( ) );
        if ( !UBO->Init ( lights ) )
            return nullptr;
        return std::move ( UBO );
    }

private:
    bool Init ( uint32_t lights ) {
        glGenBuffers ( 1 , &ubo_bufferID );
        glBindBuffer ( GL_UNIFORM_BUFFER , ubo_bufferID );
        glBufferData ( GL_UNIFORM_BUFFER , sizeof ( Light_ORI ) * lights , nullptr , GL_DYNAMIC_DRAW );
        glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
        return true;
    }
    UBOBUFFER_LIGHT ( ) {}

    uint32_t ubo_bufferID{ 0 };
};