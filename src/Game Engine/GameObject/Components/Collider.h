#pragma once

#include <glm/glm.hpp>

#include "../BaseComponent.h";

class Collider :
    public BaseComponent {

public:
    Collider();

    virtual void Initialize() {};
    virtual void Start() {};

    virtual void Update() {};
    virtual void Render() {};
    virtual void Render(Shader* shader) {};

    virtual TYPES GetType() { return TYPES::BOX_COLLIDER; };

    virtual glm::vec2 GetRange(AXIS axis) { return glm::vec2(1, 1); };
    virtual void UpdateRanges() {};

    virtual void CreateBBLines() {};
    virtual void RenderBB() {};

    ~Collider();

private:

};