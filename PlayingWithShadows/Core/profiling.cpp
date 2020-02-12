//
//  profilling.cpp
//  Engine
//
//  Created by Filipe Marques on 11/02/2020.
//  Copyright © 2020 Filipe Marques. All rights reserved.
//

#include "profilling.hpp"

#include <cassert>
#include <iostream>

using namespace Core;

void ProfileTimer::StartInvocation()
{
    m_isInvoked = true;
    m_startTime = std::chrono::steady_clock::now();
}

void ProfileTimer::StopInvocation()
{
    if(!m_isInvoked){
        std::cout << "Error: StopInvocation called without matching start invocation" << std::endl;
        assert(m_isInvoked);
    }
    
    m_numInvocations++;
    m_totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_startTime).count();
    m_startTime = std::chrono::steady_clock::time_point();
    m_isInvoked = false;
}

double ProfileTimer::GetTimeAndReset(double divisor)
{
    divisor = (divisor == 0) ? m_numInvocations : divisor;
    double result = (m_totalTime == 0 && divisor == 0.0) ? 0.0 : (1000.0 * m_totalTime)/((double)divisor);
    m_totalTime = 0.0;
    m_numInvocations = 0;
    
    return result;
}

double ProfileTimer::DisplayAndReset(const std::string& message, double divisor, int displayedMessageLength)
{
    std::string whiteSpace = "";
    for(size_t i = message.length(); i < displayedMessageLength; i++)
    {
        whiteSpace += " ";
    }
    
    double time = GetTimeAndReset(divisor);
    std::cout << message << whiteSpace << time << " ms" << std::endl;
    return time;
}

