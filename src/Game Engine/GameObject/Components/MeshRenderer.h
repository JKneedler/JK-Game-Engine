#pragma once

class MeshRenderer;

#include "../../Material.h"
#include "../GameObject.h"
#include "../../Mesh.h"

class MeshRenderer :
    public BaseComponent {

public:
    MeshRenderer();
    MeshRenderer(Mesh* myMesh, Material* myMaterial);

    void Initialize();
    void Start();

    void Update();
    void Render();
    void Render(Shader* shader);

    Material* getMaterial() { return material; };

    TYPES GetType() { return MESH_RENDERER; };

    ~MeshRenderer();

private:
    Mesh* mesh;
    Material* material;

};

