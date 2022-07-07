#pragma once
#include <iostream>

#define DEBUG_LOG(x) \
    std::cout << x << " line: " << " file: " << __FILE__ << ":" << __LINE__ << std::endl