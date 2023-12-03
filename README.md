# Eureka Render

> ## Version 0.1 12/2/2023
> <a href="https://lucid.app/lucidchart/2efba941-fefb-42e8-b17b-c8bb65f38530/edit?invitationId=inv_a0385ab1-d2db-4790-9811-766200246513" target="_blank"><strong><ins>Program Structure on LucidChart</ins></strong></a>
>
> ![Version 0.1 Overview](ReadmeFiles%2FV0_1_Overview.png)
> - **Current feature:**
>   - Forward rendering
>   - UI rendering with orthographic projection
>   - Render pipeline written in separate file, making it easy to switch pipelines
>   - Directional light only (without shadow)
>   - Support external assets including models and textures(2D only)
>   - Class abstraction, create and modify scene objects with very few lines, VAO, VBO, EBO will be set automatically
>   - Support include shader library in GLSL shaders
>   - Vertex and Fragment shader written in one single file
>   - Run time shader recompile
>   - Frame buffer correctly response to window resize
>   - Smooth camera movement and rotation
> - **TODO feature:**
>   - Multiple light source
>   - Deferred rendering
>   - Buffer visualization
>   - Post process effects
>   - PBR
>   - Skybox
>   - More render pipeline
>   - GUI
>   - TBD
