#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/matrix_relational.hpp>

#include "Collider.h";
#include "../GameObject.h";
#include "../../Line.h"
#include "Camera.h"

class BoxCollider :
    public Collider {

public:
    BoxCollider();
    BoxCollider(glm::vec3 origin, glm::vec3 size);

    void Initialize() {};
    void Start() {};

    void Update() {};
    void Render() {};
    void Render(Shader* shader) {};

    TYPES GetType() { return BOX_COLLIDER; };

    void UpdateRanges();
    glm::vec2 GetRange(AXIS axis);
    void SetRanges();

    void CreateBBLines();
    void RenderBB();

    void PrintVec3(const char* name, glm::vec3 vector);

    void PrintVerts();

    ~BoxCollider();

private:

    glm::vec3 position;
    glm::vec3 scale;

    glm::mat4 prevObjectMatrix;

    glm::vec3 verts[8];

    std::vector<Line*> lines;

    glm::vec2 rangeX;
    glm::vec2 rangeY;
    glm::vec2 rangeZ;

};
