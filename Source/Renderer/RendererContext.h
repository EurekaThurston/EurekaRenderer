#pragma once

class RendererContext
{
public:
    static RendererContext& GetInstance()
    {
        static RendererContext instance;
        return instance;
    }

    double lastFrameTime;
    double currentFrameTime;
    float deltaTime;
    unsigned int fps;

private:
    RendererContext() {}
    RendererContext(RendererContext const&);
    void operator=(RendererContext const&);
    
};
