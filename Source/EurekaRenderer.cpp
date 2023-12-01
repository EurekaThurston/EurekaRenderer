#include <iostream>
#include <fstream>
#include "Window/Window.h"
#include "Renderer/Renderer.h"

int main()
{
    {
        Window window(1920, 1080, "Eureka Renderer", NULL, NULL);
        Renderer renderer(&window);
        // glfwSetWindowUserPointer(window.GetWindow(), &renderer);
        // glfwSetKeyCallback(window.GetWindow(), Window::KeyCallback);

        // Render loop
        while (!window.WindowShouldClose())
        {
            // Input & event processor  
            window.ProcessInput();
            window.EventProcessor();
            renderer.Render();
        }
    } // Window destructor called here
    return 0;
}
