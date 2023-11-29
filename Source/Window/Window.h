#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window
{
public:
    Window( int windowWidth, int windowHeight, const char* windowTitle, GLFWmonitor* windowMonitor,
            GLFWwindow* windowShare );
    ~Window();

    // Window setting getters
    GLFWwindow* GetWindow() const;
    int GetWindowWidth() const;
    int GetWindowHeight() const;
    const char* GetWindowTitle() const;
    GLFWmonitor* GetWindowMonitor() const;
    GLFWwindow* GetWindowShare() const;
    void GetWindowInfo() const;
    bool WindowShouldClose() const;

    // Window resize callback to adjust viewport size
    static void FrameBufferSizeCallBack( GLFWwindow* window, int width, int height );

    // Input processor
    void ProcessInput() const;
    void EventProcessor() const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    const char* m_title;
    GLFWmonitor* m_monitor;
    GLFWwindow* m_share;

    void InitializeGLFW();
    void CreateWindow( int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share );
    void InitializeGLAD();
    void SetupCallbacks();
};
