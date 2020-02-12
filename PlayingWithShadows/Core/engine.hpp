//
//  engine.hpp
//  Core::Engine
//
//  Created by Filipe Marques on 11/02/2020.
//  Copyright © 2020 Filipe Marques. All rights reserved.
//

#ifndef COREENGINE_H
#define COREENGINE_H

#include "window.hpp"
//#include "../rendering/Engine.h"
#include <string>

class Game;

//This is the central part of the game engine. It's purpose is to manage interaction
//between the various sub-engines (such as the rendering and physics engines) and the game itself.
namespace Core {
    class Engine
    {
    public:
        Engine(double frameRate, Renderer::Window* window); //, Renderer::Engine* renderEngine,  Game* game);
        
        void Start();
        void Stop();
        
        //inline Renderer::Engine* GetRenderEngine() { return m_renderEngine; }
        
    private:
        bool                m_isRunning;    //Whether or not the engine is running
        double              m_frameTime;    //How long, in seconds, one frame should take
        Renderer::Window*   m_window;       //Used to display the game
        //Renderer::Engine*   m_renderEngine; //Used to render the game. Stored as pointer so the user can pass in a derived class
        //Game*               m_game;         //The game itself. Stored as pointer so the user can pass in a derived class.
    };
}

#endif
