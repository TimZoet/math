#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <iostream>

namespace math
{
    inline void print_isa()
    {
        std::cout << "This library was compiled with the following flags:\n";

#ifdef __SSE4_1__
        std::cout << "    SSE4_1\n";
#endif

#ifdef __SSE4_2__
        std::cout << "    SSE4_2\n";
#endif

#ifdef __AVX__
        std::cout << "    AVX\n";
#endif

#ifdef __AVX2__
        std::cout << "    AVX2\n";
#endif

#ifdef __FMA__
        std::cout << "    FMA\n";
#endif

        std::cout << std::endl;
    }
}
