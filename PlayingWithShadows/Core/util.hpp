//
//  util.hpp
//  Engine
//
//  Created by Filipe Marques on 11/02/2020.
//  Copyright © 2020 Filipe Marques. All rights reserved.
//

#ifndef UTIL_H
#define UTIL_H

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define SNPRINTF _snprintf_s
#else
#define SNPRINTF snprintf
#endif

//#define ZERO_MEM(a) memset(a,0,sizeof(a))
//#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF

#include <vector>
#include <string>

namespace Core {
    namespace Util
    {
        void Sleep(int milliseconds);
        std::vector<std::string> Split(const std::string &s, char delim);
    };
}

#endif
