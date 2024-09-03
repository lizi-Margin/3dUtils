#pragma once

#include "external/Eigen/Dense"
#include <array>
#include <vector>
#include <stdexcept>

#include "Def.h"

namespace c3utils {
    class Vector2 {
    protected:
        ::Eigen::Vector2d vec;
        explicit Vector2(const Eigen::Vector2d& vec) noexcept : vec(vec) {}

    public:
        Vector2() noexcept
            : vec(0., 0.) 
        {
            PRINT_WARNING("Initial parameters expected");
        }

        Vector2(float64_t x, float64_t y) noexcept
            : vec(x, y) {}

        explicit Vector2(const std::array<float64_t,2>& arr2) noexcept
            : vec(arr2[0], arr2[1]){}

        //explicit 
        Vector2(const Vector2& copy_target) noexcept
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


        ::std::array<float64_t,2> get_list() const noexcept
        {
            return ::std::array<float64_t,2>{ this->vec[0], this->vec[1] };
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

		float64_t& operator[](size_t index) {
			if (index == 0) return this->vec(0);
			if (index == 1) return this->vec(1);
			throw std::out_of_range("Index out of range");
		}

		const float64_t& operator[](size_t index) const {
			if (index == 0) return this->vec(0);
			if (index == 1) return this->vec(1);
			throw std::out_of_range("Index out of range");
		}

		Vector2 operator+(const Vector2& other) const {
			return Vector2(vec + other.vec);
		}

		Vector2 operator-(const Vector2& other) const {
			return Vector2(vec - other.vec);
		}


    };

	inline std::ostream& operator<<(std::ostream& os, const Vector2& v) 
    {
		os << LEFT_BRACKETS << v[0] << ", " << v[1] << RIGHT_BRACKETS;
		return os;
	}

   // namespace python {
   //     class PyVector2 : public ::c3utils::Vector2{
   //         public:

			//PyVector2() noexcept
			//	: c3utils::Vector2(0., 0.) {}

			//PyVector2(float64_t x, float64_t y) noexcept
			//	: c3utils::Vector2(x, y) {}

   //         PyVector2(const std::array<float64_t, 2>& arr2) = delete;

			//explicit PyVector2(const std::vector<float64_t>& list2)
			//{
   //             if (list2.size() != 2) throw ::std::invalid_argument("Vector2: 2 elements initial vector expected");
			//	this->vec = Eigen::Vector2d(list2[0], list2[1]);
			//}

			//explicit PyVector2(const Vector2& copy_target) noexcept
			//	: c3utils::Vector2(copy_target) {}

			//::std::vector<float64_t> get_list() const noexcept
			//{
			//	return ::std::vector<float64_t>{ this->vec[0], this->vec[1] };
			//}


   //     };
   // }

}
