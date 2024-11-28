#pragma once

#include "object.h"
#include "model.h"
#include "CameraManager.h"

class Item : public Object {
public:
    Item ( glm::vec3 pos ) : Object ( ) {
        Pos = pos;
        model = nullptr;
    }

    virtual void Update ( );
    virtual void Render_2pass ( const Program* program );
    virtual void Render ( const Program* program );
    virtual void Initialize ( const std::string& strName );
    virtual void RenderShadow ( glm::mat4 lightView , const Program* program ) override;

private:
    Model* model;
    glm::vec3 Pos;
    glm::mat4 modelTransform;
};