//
//  input.cpp
//  Engine
//
//  Created by Filipe Marques on 11/02/2020.
//  Copyright © 2020 Filipe Marques. All rights reserved.
//

#include "input.hpp"
#include "../rendering/window.hpp"

#include <SDL2/SDL.h>
#include <cstring>

using namespace Core;

Input::Input(Renderer::Window* window) :
m_mouseX(0),
m_mouseY(0),
m_window(window)
{
    memset(m_inputs, 0, NUM_KEYS * sizeof(bool));
    memset(m_downKeys, 0, NUM_KEYS * sizeof(bool));
    memset(m_upKeys, 0, NUM_KEYS * sizeof(bool));
    
    memset(m_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
    memset(m_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
    memset(m_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
}

void Input::SetCursor(bool visible) const
{
    if(visible)
        SDL_ShowCursor(1);
    else
        SDL_ShowCursor(0);
}

void Input::SetMousePosition(const glm::vec2& pos) const
{
    SDL_WarpMouseInWindow(m_window->GetSDLWindow(), (int)pos.x, (int)pos.y);
}
