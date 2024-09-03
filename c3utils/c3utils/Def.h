#pragma once

#include <cmath>
#include <iostream>
#include "external/Eigen/Dense"

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define DLL_EXPORT __declspec(dllexport)
#  define DLL_IMPORT __declspec(dllimport)
#else
#  define DLL_EXPORT __attribute__((visibility("default")))
#  define DLL_IMPORT __attribute__((visibility("default")))
#endif

#define PRINT_WARNING(msg) { std::cerr << "Warning: " << msg << std::endl; }

namespace c3utils {
	constexpr auto LEFT_BRACKETS = "[ ";
	constexpr auto RIGHT_BRACKETS = " ]";

	constexpr auto pi = EIGEN_PI;

	typedef double_t float64_t;
}
