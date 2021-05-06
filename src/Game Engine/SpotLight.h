#pragma once
#include "PointLight.h"
class SpotLight :
    public PointLight {
public:
    SpotLight();
    SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
        GLfloat red, GLfloat green, GLfloat blue,
        GLfloat aIntensity, GLfloat dIntensity,
        GLfloat con, GLfloat lin, GLfloat exp,
        GLfloat edg);

    void Initialize();
    void Start();

    void Update();
    void Render();

    TYPES GetType() { return SPOT_LIGHT; };

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
        GLuint diffuseIntensityLocation, GLuint positionLocation, GLfloat directionLocation,
        GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
        GLfloat edgeLocation);

    ~SpotLight();

private:
    GLfloat edge, procEdge;
};

