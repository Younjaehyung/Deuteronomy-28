#pragma once

#include "object.h"
#include "model.h"
#include "CameraManager.h"
#include "Sound.h"

class DoorState {

};


class Door : public Object {
public:
    Door ( ) {

    }
    Door ( glm::vec3 pos ) {
        Pos = pos;
        model = nullptr;
        objectID = eLayerType::Item;
    }

    virtual void Update ( );
    virtual void Render_2pass ( const Program* program , glm::mat4 _cameraTransform );
    virtual void Render ( const Program* program , glm::mat4 _cameraTransform );
    virtual void Initialize ( const std::string& strName );
    virtual void RenderShadow ( glm::mat4 lightView , const Program* program ) override;
    virtual bool HandleCollision ( Object* );
private:
    ModelPtr model;

    float DoorRotatef = 0.0f;
    glm::mat4 DoorRotate;
    glm::mat4 modelTransform;
    int Doortype;

};