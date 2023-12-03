// Basic render pipeline for rendering a scene using forward rendering
#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "RendererContext.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../Window/Window.h"
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"
#include "../Model/Model.h"
#include "..\Light\LightComponents.h"

class Renderer
{
public:
    Renderer( Window* window );
    ~Renderer();

    enum class MeshTag
    {
        Object,
        UI
    };

    // Renderer
    void SetupContext();
    void Render();

    // Context
    void EnableDepthTest( bool enable = true ) const;

    // Camera
    Camera* GetCamera( const std::string& cameraName );
    void CreateCamera( const std::string& cameraName, Window* window, glm::vec3 position, glm::vec3 orientation,
                       glm::vec3 up, float FOVdeg, float nearPlane, float farPlane );

    // Model
    Model* GetModel( const std::string& modelName );
    void ImportModel( const std::string& modelName, const std::string& filePath );

    // Mesh
    Mesh* GetMesh( const std::string& meshName );
    void SetMeshName( const std::string& meshName, const std::string& newName );
    void CreateMesh( const std::string& meshName, MeshTag tag, std::vector<VertexAttributes>& vertices,
                     std::vector<GLuint>& indices );
    void CreateMeshFromModel( Model& model, MeshTag tag );
    void SetMeshRenderContext( const std::string& meshName, GLenum mode, Shader& shader, Camera& camera );

    // Shader
    Shader* GetShader( const std::string& shaderName );
    void CreateShader( const std::string& shaderName, const std::string& filePath );
    void RecompileShader();

    // Texture
    Texture* GetTexture( const std::string& textureName );
    void ImportTexture( const std::string& textureName, const std::string& filePath );

    // Light
    DirectionalLight* GetDirectionalLight( const std::string& lightName ) const;
    void CreateDirectionalLight( glm::vec3 position, glm::vec3 color, float intensity );
    void SetDirectionalLightContext() const;

    // UI
    Mesh* GetUI( const std::string& UIName );
    void SetUIRenderContext( const std::string& UIName, GLenum mode, Shader& shader, Camera& camera );

    // Misc
    void GetMaxVertexAttributesSupported() const;

private:
    // Window
    Window* m_window;

    // Camera
    std::unordered_map<std::string, Camera*> m_cameras;

    // Models
    std::unordered_map<std::string, Model*> m_models;

    // Meshes
    std::unordered_map<std::string, Mesh*> m_meshes;

    // Shaders
    std::unordered_map<std::string, Shader*> m_shaders;
    bool m_canRecompileShader = true;

    // Textures
    std::unordered_map<std::string, Texture*> m_textures;

    // UI
    std::unordered_map<std::string, Mesh*> m_UIs;

    // Directional Light
    DirectionalLight* m_directionalLight;

    // Render Context
    bool m_depthTest;

    // Context
    bool m_enterRenderLoop;
    void SetupRendererContext() const;
    void UpdateRendererContext();

    // Render commands
    void Clear( GLfloat r = 0.5f, GLfloat g = 0.5f, GLfloat b = 0.5f, GLfloat a = 0.5f ) const;
    void Draw( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices ) const;
    void DrawMeshes();
    void DrawUIs();
};
