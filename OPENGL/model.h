#pragma once

#include "common_include.h"
#include "mesh_user.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "lib/assimp-vc143-mtd.lib")


CLASS_PTR ( Model );
class Model {
public:
    static ModelUPtr Load ( const std::string& filename );  //model loading
        
    int GetMeshCount ( ) const { return ( int ) m_meshes.size ( ); }
    MeshPtr GetMesh ( int index ) const { return m_meshes[ index ]; }
    void Draw ( const Program* program ) const;
   
    std::string Get ( ) const { return filename; }

private:
    Model ( ) {}
    bool LoadByAssimp ( const std::string& filename );  //파일이름을 토대로 텍스쳐를 가져와 매핑
    void ProcessMesh ( aiMesh* mesh , const aiScene* scene );   //텍스쳐 매핑
    void ProcessNode ( aiNode* node , const aiScene* scene );   //vertex 

    std::vector<MeshPtr> m_meshes;
    std::vector<MaterialPtr> m_materials;
    std::string filename;
};
