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



namespace c3utils {
	constexpr auto pi = EIGEN_PI;
	typedef double float64_t;
}

//#define FOR_PYTHON
