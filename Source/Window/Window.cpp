#include <iostream>
#include <stdexcept>
#include "Window.h"

Window::Window( int windowWidth, int windowHeight, const char* windowTitle, GLFWmonitor* windowMonitor,
                GLFWwindow* windowShare ) : m_width(windowWidth), m_height(windowHeight), m_title(windowTitle), m_monitor(windowMonitor), m_share(windowShare)
{
    InitializeGLFW();
    CreateWindow(m_width, m_height, m_title, m_monitor, m_share);
    InitializeGLAD();
    SetupCallbacks();
    
    
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

GLFWwindow* Window::GetWindow() const
{
    return m_window;
}

int Window::GetWindowWidth() const
{
    return m_width;
}

int Window::GetWindowHeight() const
{
    return m_height;
}

const char* Window::GetWindowTitle() const
{
    return m_title;
}

GLFWmonitor* Window::GetWindowMonitor() const
{
    return m_monitor;
}

GLFWwindow* Window::GetWindowShare() const
{
    return m_share;
}

void Window::GetWindowInfo() const
{
    std::cout << "Window width: " << GetWindowWidth() << std::endl;
    std::cout << "Window height: " << GetWindowHeight() << std::endl;
    std::cout << "Window title: " << GetWindowTitle() << std::endl;
}

bool Window::WindowShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

// Window resize callback to adjust viewport size
void Window::FrameBufferSizeCallBack( GLFWwindow* window, int newWidth, int newHeight )
{
    glViewport(0, 0, newWidth, newHeight);
    // Update the window size in the Window class instance
    Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win)
    {
        win->m_width = newWidth;
        win->m_height = newHeight;
    }
}

void Window::ProcessInput() const
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}

void Window::EventProcessor() const
{
    glfwPollEvents();
}

void Window::InitializeGLFW()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
}

void Window::CreateWindow( int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share )
{
    m_window = glfwCreateWindow(width, height, title, monitor, share);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }
    glfwMakeContextCurrent(m_window);
    // Set the user pointer to 'this' instance of the Window class
    glfwSetWindowUserPointer(m_window, this);
}

void Window::InitializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD!");
    }
}

void Window::SetupCallbacks()
{
    glfwSetFramebufferSizeCallback(m_window, Window::FrameBufferSizeCallBack);
}


