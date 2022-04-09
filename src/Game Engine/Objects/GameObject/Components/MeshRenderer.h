#pragma once

class MeshRenderer;

#include "../../../Material.h"
#include "../GameObject.h"
#include "../../../Mesh.h"

class MeshRenderer :
    public BaseComponent {

public:
    MeshRenderer();
    MeshRenderer(std::vector<Mesh*> myMeshes, std::vector<Material*> myMaterials);

    void Initialize();
    void Start();

    void Update();
    void Render();
    void Render(Shader* shader);

    TYPES GetType() { return MESH_RENDERER; };

    ~MeshRenderer();

private:
    std::vector<Mesh*> meshes;
    std::vector<Material*> materials;

};

