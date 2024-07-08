#pragma once

#include <iostream>

constexpr auto LEFT_BRACKETS = "[ ";
constexpr auto RIGHT_BRACKETS = " ]";

#define PRINT_WARNING(msg) { std::cerr << "Warning: " << msg << std::endl; }
