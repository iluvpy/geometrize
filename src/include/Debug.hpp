#pragma once
#include <iostream>

#define DEBUG_LOG(x) \
    std::cout << #x << ": " <<  x << " file: " << __FILE__ << ":" << __LINE__ << std::endl