#pragma once

#include <cmath>
#include "external/Eigen/Dense"
#include "Vector3.h"
#include "Vector2.h"
#include "Def.h"

typedef double_t float64_t;

namespace c3utils {
    inline float64_t norm(float64_t x, float64_t lower_side = -1.0, float64_t upper_side = 1.0) noexcept {
        if (lower_side > upper_side) PRINT_WARNING("'lower_side' should be smaller than 'upper_side'!");
        if (x > upper_side) x = upper_side;
        if (x < lower_side) x = lower_side;
        return x;
    }

    constexpr inline float64_t meters_to_feet(float64_t meters) noexcept {
        return meters * 3.28084;
    }

    constexpr inline float64_t feet_to_meters(float64_t feet) noexcept {
        return feet / 3.28084;
    }

    inline float64_t no_neg(float64_t num) noexcept {
        if (num < 0.) num = 0.;
        return num;
    }

    inline Vector3 make_vector3(const Vector2& vector2, float64_t z = 0.) noexcept {
        return Vector3(static_cast<float64_t>(vector2.vec(0)), static_cast<float64_t>(vector2.vec(1)), z);
    }

    inline Vector3 copy(const Vector3& vector3) noexcept {
        return Vector3(vector3);
    }

    inline float64_t abs(float64_t num) noexcept {
        return ::std::abs(num);
    }

    inline float64_t pwr(float64_t num) noexcept {
        return num * num;
    }


    std::vector<float64_t> 
    NEU_to_self
    (const std::vector<float64_t>& neu, float64_t roll, float64_t pitch, float64_t yaw) {
        if (neu.size() != 3) throw std::invalid_argument("NEU vector must have 3 elements");

		Vector3 intent_vector(neu[0], neu[1], -neu[2]);
		intent_vector.rev_rotate_zyx_self(roll, pitch, yaw);
		intent_vector.vec[2] = -intent_vector.vec[2]; 

		return intent_vector.get_list();
    }

    ::std::vector<float64_t> 
    get_NED_from_NEU
    (::std::vector<float64_t>& neu, const ::std::vector<float64_t>& mid = ::std::vector<float64_t>{ 0, 0, 5000 }) {
        if (neu.size() != 3 || mid.size()!= 3) throw std::invalid_argument("NEU vector must have 3 elements");

        // TODO: customized 'mid'
		if (mid[0] != 0. || mid[1] != 0. || mid[2] != 5000.) {
		    throw std::runtime_error("Not implemented for mid other than [0, 0, 5000]");
		}

        std::vector<float64_t> ned(neu);
        ned[2] = -(neu[2] - mid[2]);
		return ned;
	}

}
