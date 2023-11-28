#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "assimp/mesh.h"
#include <glm/glm.hpp>


// Structure to store vertex data
struct VertexAttributes
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec4 Color;
    glm::vec4 Tangent;
};

// Structure to represent a mesh
struct MeshData
{
    std::vector<VertexAttributes> vertices;
    std::vector<unsigned int> indices;
    std::string name;
};

class Model
{
public:
    Model( const std::string& modelName, const std::string& filePath );

    std::string GetModelName();
    const std::vector<MeshData>& GetMeshData();

private:
    std::string m_modelName;
    std::vector<MeshData> m_meshData;

    void LoadModel( const std::string& filePath );
    void ProcessNode( aiNode* node, const aiScene* scene );
    MeshData ProcessMesh( aiMesh* mesh, const aiScene* scene );
};
