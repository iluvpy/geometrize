#pragma once
#include <iostream>

#ifdef NDEBUG
#define DEBUG_LOG(x) \
    std::cout << #x << ": " <<  x << " file: " << __FILE__ << ":" << __LINE__ << std::endl
#else

#define DEBUG_LOG(x)
#endif