#pragma once
#include <iostream>

#ifdef NDEBUG
#define ON_DEBUG(x) x
#else

#define ON_DEBUG(x)
#endif