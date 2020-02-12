//
//  engine.cpp
//  Engine
//
//  Created by Filipe Marques on 11/02/2020.
//  Copyright © 2020 Filipe Marques. All rights reserved.
//

#include "engine.hpp"

#include <chrono>
#include <stdio.h>

#include "profilling.hpp"
//#include "../rendering/window.hpp"
#include "input.hpp"
#include "util.hpp"

//#include "game.hpp"

using namespace Core;

Engine::Engine(double frameRate, Renderer::Window *window) : //, Renderer::Engine* renderEngine, Game* game) :
m_isRunning(false),
m_frameTime(1.0/frameRate),
m_window(window)
//m_renderEngine(renderEngine),
//m_game(game)
{
    //We're telling the game about this engine so it can send the engine any information it needs
    //to the various subsystems.
    //m_game->SetEngine(this);
    
    //Game is initialized here because this is the point where all rendering systems
    //are initialized, and so creating meshes/textures/etc. will not fail due
    //to missing context.
    //m_game->Init(*m_window);
}

void Engine::Start() {
    if(m_isRunning)
        return;
    
    m_isRunning = true;
    
    auto    last_tp         = std::chrono::steady_clock::now(); //Current time at the start of the last frame
    double  frame_cntr      = 0;                                //Total passed time since last frame counter display
    double  unprocessed_t   = 0;                                //Amount of passed time that the engine hasn't accounted for
    double  n_frames        = 0;                                //Number of frames rendered since last
    
    ProfileTimer slp_tmr;   //sleep timer
    ProfileTimer sBfr_tmr;  //swap buffer timer
    ProfileTimer wUpdt_tmr; //window update timer
    while(m_isRunning)
    {
        bool render = false;    //Whether or not the game needs to render.
        
        auto    strt_t = std::chrono::steady_clock::now(); //Current time at the start of the frame.
        double  elapsed_t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - strt_t).count();
        
        unprocessed_t   += elapsed_t;
        frame_cntr      += elapsed_t;
        
        //The engine displays profiling statistics after every second because it needs to display them at some point.
        //The choice of once per second is arbitrary, and can be changed as needed.
        if(frame_cntr >= 1000.0)
        {
            double total_measured_t = 0.0;
            double total_t          = ((1000.0*frame_cntr)/n_frames);
            
            //total_measured_t += m_game->DisplayInputTime((double)frames);
            //total_measured_t += m_game->DisplayUpdateTime((double)frames);
            //total_measured_t += m_renderingEngine->DisplayRenderTime((double)frames);
            
            total_measured_t += slp_tmr.DisplayAndReset("Sleep Time: ", n_frames);
            
            total_measured_t += wUpdt_tmr.DisplayAndReset("Window Update Time: ", n_frames);
            
            total_measured_t += sBfr_tmr.DisplayAndReset("Buffer Swap Time: ", n_frames);
            
            
            //total_measured_t += m_renderingEngine->DisplayWindowSyncTime((double)frames);
            printf("Other Time:                             %f ms\n", (total_t - total_measured_t));
            printf("Total Time:                             %f ms\n\n", total_t);
            
            n_frames    = 0;
            frame_cntr  = 0;
            
        }
        
        //The engine works on a fixed update system, where each update is 1/frameRate seconds of time.
        //Because of this, there can be a situation where there is, for instance, a fixed update of 16ms,
        //but 20ms of actual time has passed. To ensure all time is accounted for, all passed time is
        //stored in unprocessedTime, and then the engine processes as much time as it can. Any
        //unaccounted time can then be processed later, since it will remain stored in unprocessedTime.
        while(unprocessed_t > m_frameTime)
        {
            wUpdt_tmr.StartInvocation();
            m_window->Update();
            
            if(m_window->IsCloseRequested())
            {
                Stop();
            }
            
            wUpdt_tmr.StopInvocation();
            
            //Input must be processed here because the window may have found new
            //input events from the OS when it updated. Since inputs can trigger
            //new game actions, the game also needs to be updated immediately
            //afterwards.
            //m_game->ProcessInput(m_window->GetInput(), (float)m_frameTime);
            //m_game->Update((float)m_frameTime);
            
            //Since any updates can put onscreen objects in a new place, the flag
            //must be set to rerender the scene.
            render = true;
            
            unprocessed_t -= m_frameTime;
        }
        
        if(render)
        {
            //m_game->Render(m_renderingEngine);
            
            //The newly rendered image will be in the window's backbuffer,
            //so the buffers must be swapped to display the new image.
            sBfr_tmr.StartInvocation();
            m_window->SwapBuffers();
            sBfr_tmr.StopInvocation();
            n_frames += 1.0;
        }
        else
        {
            //If no rendering is needed, sleep for some time so the OS
            //can use the processor for other tasks.
            slp_tmr.StartInvocation();
            Util::Sleep(1);
            slp_tmr.StopInvocation();
        }
    }
}

void Engine::Stop() {
    m_isRunning = false;
}
