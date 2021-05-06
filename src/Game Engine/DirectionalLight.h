#pragma once
#include "Light.h"

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
                     GLfloat red, GLfloat green, GLfloat blue, 
                     GLfloat aIntensity, GLfloat dIntensity);

    void Initialize();
    void Start();

    void Update();
    void Render();

    TYPES GetType() { return DIRECTIONAL_LIGHT; };

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
        GLuint diffuseIntensityLocation, GLuint directionLocation);

    glm::mat4 CalculateLightTransform();

    ~DirectionalLight();

private:
};

