#pragma once

#include "Light.h"
#include "OmniShadowMap.h"

class PointLight :
    public Light
{
public:
    PointLight();
    PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
                GLfloat near, GLfloat far,
                GLfloat red, GLfloat green, GLfloat blue, 
                GLfloat aIntensity, GLfloat dIntensity,
                GLfloat con, GLfloat lin, GLfloat exp);

    void Initialize();
    void Start();

    void Update();
    void Render();

    TYPES GetType() { return POINT_LIGHT; };

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
        GLuint diffuseIntensityLocation, GLuint positionLocation,
        GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

    std::vector<glm::mat4> CalculateLightTransform();

    GLfloat GetFarPlane() { return farPlane; }

    ~PointLight();

protected:
    GLfloat constant, linear, exponent;

    GLfloat farPlane;
};

