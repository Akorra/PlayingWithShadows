//
//  profilling.hpp
//  Engine
//
//  Created by Filipe Marques on 11/02/2020.
//  Copyright © 2020 Filipe Marques. All rights reserved.
//

#ifndef PROFILING_HPP_INCLUDED
#define PROFILING_HPP_INCLUDED

#include <string>
#include <chrono>

#define PROFILING_DISABLE_MESH_DRAWING 0
#define PROFILING_DISABLE_SHADING 0
#define PROFILING_SET_1x1_VIEWPORT 0
#define PROFILING_SET_2x2_TEXTURE 0

namespace Core {
    class ProfileTimer
    {
    public:
        ProfileTimer() :
        m_numInvocations(0),
        m_totalTime(0.0),
        m_startTime()
        {}
        
        void StartInvocation();
        void StopInvocation();
        
        double DisplayAndReset(const std::string& message, double divisor = 0, int displayedMessageLength = 40);
        double GetTimeAndReset(double divisor = 0);
    protected:
    private:
        bool   m_isInvoked;
        int    m_numInvocations;
        double m_totalTime;
        
        std::chrono::steady_clock::time_point m_startTime;
    };
}

#endif // PROFILING_HPP_INCLUDED
