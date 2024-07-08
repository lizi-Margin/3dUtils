#pragma once

#include "external/Eigen/Dense"
#include <cmath>
#include <stdexcept>
#include <vector>
#include "Def.h"

typedef double float64_t;

namespace c3utils {
    class Vector2 {
    public:
        ::Eigen::Vector2d vec;

        Vector2(float64_t x, float64_t y) noexcept
            : vec(x, y) {}

        explicit Vector2(const std::vector<float64_t>& list2)
        {
            if (list2.size() != 2) {
                throw std::invalid_argument("Vector2 must be initialized with a list of 2 elements.");
            }
            vec = Eigen::Vector2d(list2[0], list2[1]);
        }

        explicit Vector2(const Vector2& copy_target) noexcept
            : vec(copy_target.vec) {}

        Vector2& prod(float64_t x) noexcept
        {
            this->vec *= x;
            return *this;
        }

        Vector2& add(const Vector2& other) noexcept
        {
            this->vec += other.vec;
            return *this;
        }


        std::vector<float64_t> get_list() const noexcept
        {
            return ::std::vector<float64_t>{ this->vec[0], this->vec[1] };
        }

        float64_t get_prod(const Vector2& other) const noexcept
        {
            return this->get_dot(other);
        }
        float64_t get_dot(const Vector2& other) const noexcept
        {
            return this->vec.dot(other.vec);
        }

        float64_t get_module(bool non_zero = false) const noexcept
        {
            float64_t mo = vec.squaredNorm();
            if (non_zero && mo == 0) mo = ::std::numeric_limits<float64_t>::min();
            return std::sqrt(mo);
        }

        float64_t get_angle(const Vector2& other) const noexcept
        {
            float64_t dot_product = this->get_prod(other);
            float64_t modules_product = this->get_module(true) * other.get_module(true);
            float64_t ang = dot_product / modules_product;
            if (ang > 1.) ang = 1.;
            if (ang < -1.) ang = -1.;
            return std::acos(ang);
        }
    };

	inline std::ostream& operator<<(std::ostream& os, const Vector2& v) {
		os << LEFT_BRACKETS << v.vec[0] << ", " << v.vec[1] << RIGHT_BRACKETS;
		return os;
	}

}
