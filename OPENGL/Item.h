#pragma once

#include "object.h"
#include "model.h"
#include "CameraManager.h"

class ItemState {

};


class Item : public Object {
public:
    Item ( ) {

    }
    Item ( glm::vec3 pos ) {
        Pos = pos;
        model = nullptr;
    }

    virtual void Update ( );
    virtual void Render_2pass ( const Program* program , glm::mat4 _cameraTransform );
    virtual void Render ( const Program* program , glm::mat4 _cameraTransform );
    virtual void Initialize ( const std::string& strName );
    virtual void RenderShadow ( glm::mat4 lightView , const Program* program ) override;
    virtual bool HandleCollision ( Object* );
private:
    ModelPtr model;

    float itemRotatef = 0.0f;
    glm::mat4 itemRotate;
    glm::mat4 modelTransform;
    int Itemptype;
};