#include "Renderer.h"

Model* Renderer::GetModel(const std::string& modelName)
{
    return m_models[modelName];
}
void Renderer::AddModel(const std::string& modelName, const std::string& filePath)
{
    m_models[modelName] = new Model(filePath);
}
