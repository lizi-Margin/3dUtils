#pragma once

#include "external/Eigen/Dense"
#include <array>
#include <string>
#include <stdexcept>
#include "def.h"
#include "io.h"

namespace c3utils {
    constexpr const char VECTOR_LEFT_BRACKET[] = "[ ";
    constexpr const char VECTOR_RIGHT_BRACKET[] = " ]";
    constexpr auto VECTOR_LEFT_BRACKET_LEN = cstrlen(VECTOR_LEFT_BRACKET);
    constexpr auto VECTOR_RIGHT_BRACKET_LEN = cstrlen(VECTOR_RIGHT_BRACKET);


    class Vector3 {
    protected:
        Eigen::Vector3d vec;
         explicit Vector3(const Eigen::Vector3d& vec) noexcept : vec(vec) {}

    public:
        Vector3(float64_t x, float64_t y, float64_t z) noexcept
            : vec(x, y, z) {}

        explicit Vector3(const std::array<float64_t,3>& arr3) noexcept
        {
            vec = Eigen::Vector3d(arr3[0], arr3[1], arr3[2]);
        }

        Vector3(const Vector3& copy_target) noexcept
            :vec(copy_target.vec){}

#ifndef FOR_PYTHON
        Vector3& rotate_xyz_fix(std::array<float64_t, 3>& rotate_ang_arr_xyz) noexcept 
        {
            return rotate_xyz_fix(rotate_ang_arr_xyz[0],rotate_ang_arr_xyz[1],rotate_ang_arr_xyz[2] );
        }
#endif

        Vector3& rotate_xyz_fix(float64_t ax, float64_t ay, float64_t az) noexcept
        {
            Eigen::Matrix3d mx, my, mz;
            mx = Eigen::AngleAxisd(ax, Eigen::Vector3d::UnitX()).toRotationMatrix();
            my = Eigen::AngleAxisd(ay, Eigen::Vector3d::UnitY()).toRotationMatrix();
            mz = Eigen::AngleAxisd(az, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            vec = mz * my * mx * vec;
            return *this;
        }

        Vector3& rev_rotate_xyz_fix(float64_t ax, float64_t ay, float64_t az) noexcept
        {
            Eigen::Matrix3d mx, my, mz;
            mx = Eigen::AngleAxisd(-ax, Eigen::Vector3d::UnitX()).toRotationMatrix();
            my = Eigen::AngleAxisd(-ay, Eigen::Vector3d::UnitY()).toRotationMatrix();
            mz = Eigen::AngleAxisd(-az, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            vec = mx * my * mz * vec;
            return *this;
        }



        Vector3& rotate_xyz_self(float64_t ax, float64_t ay, float64_t az) noexcept
        {
            Eigen::Matrix3d mx, my, mz;
            mx = Eigen::AngleAxisd(ax, Eigen::Vector3d::UnitX()).toRotationMatrix();
            my = Eigen::AngleAxisd(ay, Eigen::Vector3d::UnitY()).toRotationMatrix();
            mz = Eigen::AngleAxisd(az, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            vec = mx * my * mz * vec;
            return *this;
        }
        Vector3& rev_rotate_xyz_self(float64_t ax, float64_t ay, float64_t az) noexcept
        {
            Eigen::Matrix3d mx, my, mz;
            mx = Eigen::AngleAxisd(-ax, Eigen::Vector3d::UnitX()).toRotationMatrix();
            my = Eigen::AngleAxisd(-ay, Eigen::Vector3d::UnitY()).toRotationMatrix();
            mz = Eigen::AngleAxisd(-az, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            vec = mz * my * mx * vec;
            return *this;
        }


        Vector3& rotate_zyx_self(float64_t ax, float64_t ay, float64_t az) noexcept
        {
            Eigen::Matrix3d mx, my, mz;
            mx = Eigen::AngleAxisd(ax, Eigen::Vector3d::UnitX()).toRotationMatrix();
            my = Eigen::AngleAxisd(ay, Eigen::Vector3d::UnitY()).toRotationMatrix();
            mz = Eigen::AngleAxisd(az, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            vec = mz * my * mx * vec;
            return *this;
        }
        Vector3& rev_rotate_zyx_self(float64_t ax, float64_t ay, float64_t az) noexcept
        {
            Eigen::Matrix3d mz, my, mx;
            mx = Eigen::AngleAxisd(-ax, Eigen::Vector3d::UnitX()).toRotationMatrix();
            my = Eigen::AngleAxisd(-ay, Eigen::Vector3d::UnitY()).toRotationMatrix();
            mz = Eigen::AngleAxisd(-az, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            vec = mx * my * mz * vec;
            return *this;
        }
        

        std::array<float64_t, 3> get_rotate_angle_fix()const noexcept 
        {
            float64_t vx = this->vec[0];
            float64_t vy = this->vec[1];
            float64_t vz = this->vec[2];

            float64_t alpha = std::atan2(vy, vx);
            float64_t beta = std::atan2(-vz, std::sqrt(vx*vx + vy*vy));
            float64_t gamma = 0;

			return { gamma, beta, alpha };
        }


        float64_t get_angle(const Vector3& other, int pid_set_zero = -1, int pid_sign_dim = -1) const
        {
            if (pid_set_zero == -1) {
                float64_t dot_product = this->get_dot(other);
                float64_t modules_product = this->get_module(true) * other.get_module(true);
                float64_t ang = dot_product / modules_product;
                if (ang > 1.) ang = 1.;
                if (ang < -1.) ang = -1.;
                return std::acos(ang);
            }

            Vector3 temp(other);
            int set_zero_dim;
            int sign_dim = 1;
            switch (pid_set_zero) {
            case 0:
                set_zero_dim = 0;
                sign_dim = 1;
                break;
            case 1:
                set_zero_dim = 1;
                sign_dim = 2;
                break;
            case 2:
                set_zero_dim = 2;
                sign_dim = 0;
                break;
            default:
                throw std::invalid_argument(lprint_(this, "Invalid pid_set_zero value"));
                return std::numeric_limits<float64_t>::quiet_NaN();
            }

            if (pid_sign_dim != -1) {
                if (0 <= pid_sign_dim && pid_sign_dim < 3) {
                    sign_dim = pid_sign_dim;
                }
                else {
                    throw std::invalid_argument(lprint_(this, "Invalid pid_sign_dim value"));
                    return std::numeric_limits<float64_t>::quiet_NaN();
                }
            }

            temp.vec(set_zero_dim) = 0;

            float64_t dot_product = this->get_prod(temp);
            float64_t modules_product = this->get_module(true) * temp.get_module(true);
            float64_t ang = dot_product / modules_product;
            if (ang > 1) ang = 1;
            if (ang < -1) ang = -1;

            float64_t angle = std::acos(ang);
            if (temp.vec(sign_dim) < 0) {
                angle = -angle;
            }

            return angle;
        }


        Vector3& prod(float64_t x) noexcept
        {
            vec *= x;
            return *this;
        }

        float64_t get_prod(const Vector3& other) const noexcept
        {
            return this->get_dot(other);
        }
        float64_t get_dot(const Vector3& other) const noexcept
        {
            return vec.dot(other.vec);
        }

        Vector3& add(const Vector3& other) noexcept
        {
            vec += other.vec;
            return *this;
        }

        float64_t get_module(bool non_zero = false) const noexcept
        {
            float64_t mo = vec.squaredNorm();
            if (non_zero && mo == 0) mo = ::std::numeric_limits<float64_t>::min();
            return std::sqrt(mo);
        }

        std::array<float64_t,3> get_list() const noexcept
        {
            return { vec[0], vec[1], vec[2] };
        }

        inline std::string str() const noexcept
        {
            std::string buff; buff.reserve(VECTOR_LEFT_BRACKET_LEN + 2 + 2 + VECTOR_RIGHT_BRACKET_LEN + 18);
            buff.append(VECTOR_LEFT_BRACKET)
                .append(round_str(vec[0]))
                .append(", ")
                .append(round_str(vec[1]))
                .append(", ")
                .append(round_str(vec[2]))
                .append(VECTOR_RIGHT_BRACKET);
            return buff;
        }

        inline std::string repr() const noexcept
        {
            std::string buff; buff.reserve(VECTOR_LEFT_BRACKET_LEN + 2 + 2 + VECTOR_RIGHT_BRACKET_LEN + 18);
            buff.append(round_str(vec[0]))
                .append(", ")
                .append(round_str(vec[1]))
                .append(", ")
                .append(round_str(vec[2]));
            return lprint_(this, buff);
        }

        //legacy
        inline std::string get_string() const noexcept {
            return this->str();
        }


		float64_t& operator[](size_t index) {
			if (index == 0) return vec[0];
			if (index == 1) return vec[1];
			if (index == 2) return vec[2];
			throw std::out_of_range(lprint_(this, "Index out of range"));
		}

		const float64_t& operator[](size_t index) const {
			if (index == 0) return vec[0];
			if (index == 1) return vec[1];
			if (index == 2) return vec[2];
			throw std::out_of_range(lprint_(this, "Index out of range"));
		}

		Vector3 operator+(const Vector3& other) const noexcept {
			return Vector3(vec + other.vec);
		}

		Vector3 operator-(const Vector3& other) const noexcept {
			return Vector3(vec - other.vec);
		}

        bool operator==(const Vector3& other) const noexcept {
            if (vec == other.vec) return true;
            
            const float64_t abs_precision = 1e-9;
            return vec.isApprox(other.vec, abs_precision);
        }

    };

	inline std::ostream& operator<<(std::ostream& os, const Vector3& v) noexcept 
    {
		os << v.str();
		return os;
	}







    class Vector2 {
    protected:
        ::Eigen::Vector2d vec;
        explicit Vector2(const Eigen::Vector2d& vec) noexcept : vec(vec) {}

    public:
        Vector2() noexcept
            : vec(0., 0.)
        {
            lprintw(this, "Initial parameters expected");
        }

        Vector2(float64_t x, float64_t y) noexcept
            : vec(x, y) {}

        explicit Vector2(const std::array<float64_t, 2>& arr2) noexcept
            : vec(arr2[0], arr2[1]) {}

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


        ::std::array<float64_t, 2> get_list() const noexcept
        {
            return ::std::array<float64_t, 2>{ this->vec[0], this->vec[1] };
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
        os << VECTOR_LEFT_BRACKET << v[0] << ", " << v[1] << VECTOR_RIGHT_BRACKET;
        return os;
    }

}
