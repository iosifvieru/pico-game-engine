#ifndef _BASIC_RENDERER_H_
#define _BASIC_RENDERER_H_

#include "Engine/Renderer/Renderer.h"

class BasicRenderer : public Renderer {
public:
    BasicRenderer(Display& display);

    void Render() override;
};

#endif