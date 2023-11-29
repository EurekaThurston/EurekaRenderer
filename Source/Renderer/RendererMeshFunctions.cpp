#include "Renderer.h"
#include "../Misc/LifeSaving.h"

Mesh* Renderer::GetMesh( const std::string& meshName )
{
    if (m_meshes.find(meshName) == m_meshes.end())
    {
        DividingLine();
        std::cout << "Mesh not found: " << meshName << std::endl;
        DividingLine();
        return nullptr;
    }
    return m_meshes[meshName];
}

void Renderer::SetMeshName( const std::string& meshName, const std::string& newName )
{
    if (m_meshes.find(meshName) == m_meshes.end())
    {
        DividingLine();
        std::cout << "Mesh not found: " << meshName << std::endl;
        DividingLine();
        return;
    }
    m_meshes[newName] = m_meshes[meshName];
    m_meshes.erase(meshName);
    DividingLine();
    std::cout << "Mesh name changed: " << meshName << " to " << newName << std::endl;
    DividingLine();
}

void Renderer::CreateMesh( const std::string& meshName, std::vector<VertexAttributes>& vertices,
                           std::vector<GLuint>& indices )
{
    m_meshes[meshName] = new Mesh(meshName, vertices, indices);
}

void Renderer::CreateMeshFromModel( Model& model )
{
    const std::vector<MeshData>& meshDataArray = model.GetMeshData();
    for (const auto& meshData : meshDataArray)
    {
        std::vector<VertexAttributes> vertices;
        std::vector<GLuint> indices;
        for (const auto& vertex : meshData.vertices)
        {
            vertices.push_back(vertex);
        }
        for (const auto& index : meshData.indices)
        {
            indices.push_back(index);
        }
        CreateMesh(meshData.name, vertices, indices);
        DividingLine();
        std::cout << "Mesh created: " << meshData.name << ", from Model: " << model.GetModelName() << std::endl;
    }
}

void Renderer::SetMeshRenderContext( const std::string& meshName, GLenum mode, Shader& shader, Camera& camera )
{
    m_meshes[meshName]->SetRenderContext(mode, shader, camera);
    DividingLine();
    std::cout << "Mesh render context set: " << meshName << std::endl;
    std::cout << "Mode: " << mode << std::endl;
    std::cout << "Shader: " << shader.GetFilePath() << std::endl;
    std::cout << "Camera: " << camera.GetName() << std::endl;
    DividingLine();
}

void Renderer::DrawMeshes()
{
    for (auto& meshEntry : m_meshes)
    {
        Mesh* mesh = meshEntry.second;
        if (mesh)
        {
            mesh->Draw();
            if (mesh->m_renderContext.consoleLog)
            {
                DividingLine();
                std::cout << "Mesh drawn: " << meshEntry.first << std::endl;
                std::cout << "Mode: " << mesh->m_renderContext.mode << std::endl;
                std::cout << "Shader: " << mesh->m_renderContext.shader->GetFilePath() << std::endl;
                std::cout << "Camera: " << mesh->m_renderContext.camera->GetName() << std::endl;
                DividingLine();
                mesh->m_renderContext.consoleLog = false;
            }
        }
    }
}
