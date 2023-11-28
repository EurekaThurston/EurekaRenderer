#include "Renderer.h"

Model* Renderer::GetModel( const std::string& modelName )
{
    return m_models[modelName];
}

void Renderer::ImportModel( const std::string& modelName, const std::string& filePath )
{
    m_models[modelName] = new Model(modelName, filePath);
}
