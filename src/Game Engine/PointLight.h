#pragma once
#include "Light.h"
class PointLight :
    public Light
{
public:
    PointLight();
    PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
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

    ~PointLight();

protected:
    GLfloat constant, linear, exponent;
};

