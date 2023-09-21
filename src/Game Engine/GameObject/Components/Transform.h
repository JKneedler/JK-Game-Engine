#pragma once

#include <GL/glew.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "../BaseComponent.h"

class Transform :
    public BaseComponent {

public:
    Transform();
    Transform(glm::vec3 startPos);
    Transform(glm::vec3 startPos, glm::vec3 startScale);
    Transform(glm::vec3 startPos, glm::quat startRot, glm::vec3 startScale);

    void Initialize();
    void Start();

    void Update();

    void SetModel(GLuint uniformModel);
    glm::mat4 GetTransformMatrix();

    void AddChild(Transform* newChild);
    Transform* RemoveChild(unsigned int childNum);
    void RemoveChildren();

    void DetachFromParent();
    void SetParent(Transform* newParent);

    glm::vec3 getPosition() { return position; }
    glm::quat getRotation() { return rotation; }
    glm::vec3 getScale() { return scale; }

    glm::vec3 getForward() { return forward; }
    glm::vec3 getRight() { return right; }
    glm::vec3 getUp() { return up; }

    void SetPosition(glm::vec3 newPos);
    void SetScale(glm::vec3 newScale);
    void SetRotation(glm::quat newRot);


    void Translate(glm::vec3 translation);
    void Translate(AXIS axis, float distance);
    
    void Rotate(float angle, AXIS axis);
    glm::vec3 GetAxisVector(AXIS axis);

    void PrintDirections();

    ~Transform();

private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    glm::mat4 model;

    std::vector<Transform*> children;
    Transform* parent = nullptr;

};
