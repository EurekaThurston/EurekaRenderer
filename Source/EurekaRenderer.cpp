#include <iostream>
#include <fstream>
#include "Window/Window.h"
#include "Renderer/Renderer.h"

int main()
{
    {
        Window window(1920, 1080, "Eureka Renderer", NULL, NULL);
        Renderer renderer;
        renderer.SetupContext();
        
        // Render loop
        while (!window.WindowShouldClose())
        {
            // Input & event processor  
            window.ProcessInput();
            window.EventProcessor();

            // Rendering commands here
            renderer.Render(window.GetWindow());
            
        }
    }   // Window destructor called here
    return 0;
}
