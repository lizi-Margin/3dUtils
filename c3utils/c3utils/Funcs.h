#pragma once

#include "external/Eigen/Dense"
#include <string>
#include <cmath>
#include <array>

#include "Vector3.h"
#include "Vector2.h"
#include "Def.h"

namespace c3utils {
	
	/*
	
		Basic utilities.

	*/
	constexpr inline float64_t nm_to_meter(float64_t nm) {
		return nm * 1852.0;
	}
	constexpr inline float64_t meter_to_nm(float64_t nm) {
		return nm / 1852.0;
	}

	constexpr inline float64_t mps_to_kn(float64_t mps)noexcept{
		return mps * 1.9438452;
	}
	constexpr inline float64_t kn_to_mps(float64_t kn)noexcept{
		//return kn / 1.9438452;
		return kn *  0.5144442;
	}

	constexpr auto K_C0 = 273.15;
	constexpr inline float64_t K_to_C(float64_t K)noexcept {
		return K - K_C0;
	}
	constexpr inline float64_t C_to_K(float64_t C)noexcept{
		return C + K_C0;
	}

	inline float64_t estimate_temperature_C(float64_t altitude) noexcept {
		const float64_t T0 = 288.15;
		const float64_t L = 0.0065;
		const float64_t tropopause_altitude = 11000.0;
		float64_t ret = 216.65;

		if (altitude <= tropopause_altitude) {
			ret = T0 - L * altitude;
		}
		else if (altitude <= 20000.0) {
			ret = 216.65;
		}

		return K_to_C(ret);
	}

	inline float64_t mach_to_mps(float64_t mach, float64_t temperature_C) noexcept {
        const double gamma = 1.4;
        const double R = 287.05;
        double temperature_K = C_to_K(temperature_C);
        double local_ss = std::sqrt(gamma * R * temperature_K);
        return mach * local_ss;
	}

	inline float64_t get_mps(float64_t mach,float64_t alt) { return mach_to_mps(mach, estimate_temperature_C(alt)); }

    constexpr inline float64_t meters_to_feet(float64_t meters) noexcept 
	{
        return meters * 3.28084;
    }

    constexpr inline float64_t feet_to_meters(float64_t feet) noexcept 
	{
        return feet / 3.28084;
    }


    inline float64_t abs(float64_t num) noexcept 
	{
        return ::std::abs(num);
    }

    constexpr inline float64_t pwr(float64_t num) noexcept 
	{
        return num * num;
    }

	inline float64_t sin(float64_t num) noexcept 
	{
		return ::std::sin(num);
	}

	inline float64_t cos(float64_t num) noexcept 
	{
		return ::std::cos(num);
	}

    inline float64_t 
	norm(float64_t x, float64_t lower_side = -1.0, float64_t upper_side = 1.0) noexcept 
	{
        if (lower_side > upper_side) PRINT_WARNING("'lower_side' should be smaller than 'upper_side'!");
        if (x > upper_side) x = upper_side;
        if (x < lower_side) x = lower_side;
        return x;
    }

    constexpr inline float64_t no_neg(float64_t num) noexcept 
	{
        return num<0. ? 0. : num;
    }







	/*
	
		Utilities for Vector3/2.
	
	*/

    inline Vector3 
	make_vector3(const Vector2& vector2, float64_t z = 0.) noexcept 
	{
		return Vector3(
			static_cast<float64_t>(vector2[0]),
			static_cast<float64_t>(vector2[1]),
			z
		);
    }

    inline Vector2
	make_vector2(const Vector3& vector3) noexcept 
	{
		return Vector2(
			(vector3[0]),
			(vector3[1])
		);
    }

    inline Vector3 copy(const Vector3& vector3) noexcept 
	{
        return Vector3(vector3);
    }






	/*
	
		3D transformation utilities.
	
	*/

	Vector3
    NEU_to_self
    (
		const Vector3& neu_vec, 
		float64_t roll, float64_t pitch, float64_t yaw   )  noexcept
	{
		Vector3 intent_vector(neu_vec[0], neu_vec[1], -neu_vec[2]);
		intent_vector.rev_rotate_zyx_self(roll, pitch, yaw);
		intent_vector[2] = -intent_vector[2]; 

		return intent_vector;
    }

	:: std::array<float64_t, 3>
    NEU_to_self
    (
		const ::std::array<float64_t,3>& neu_to, 
		const ::std::array<float64_t,3>& neu_from ,
		float64_t roll, float64_t pitch, float64_t yaw  ) noexcept 
	{
		auto neu_vec = Vector3(
			neu_to[0] - neu_from[0],
			neu_to[1] - neu_from[1],
			neu_to[2] - neu_from[2]
		);
		return NEU_to_self(neu_vec, roll, pitch, yaw).get_list();	
    }
	Vector3	
    NEU_to_self
    (
		const Vector3& neu_to, 
		const Vector3& neu_from ,
		float64_t roll, float64_t pitch, float64_t yaw  ) noexcept 
	{
		auto neu_vec = Vector3(
			neu_to[0] - neu_from[0],
			neu_to[1] - neu_from[1],
			neu_to[2] - neu_from[2]
		);
		return NEU_to_self(neu_vec, roll, pitch, yaw);	
    }



    ::std::array<float64_t,3> 
    NEU_to_NED
    (
		const ::std::array<float64_t,3>& neu_to, 	
		const ::std::array<float64_t,3>& neu_from = ::std::array<float64_t,3>{ 0, 0,10000. }   ) 
	{
        // TODO: customized 'mid'
		if (neu_from[0] != 0. || neu_from[1] != 0. || neu_from[2] != 10000.) {
		    throw std::runtime_error("Not implemented for mid other than [0, 0, 10000.]");
		}

        std::array<float64_t,3> ned(neu_to);
        ned[2] = -(neu_to[2] - neu_from[2]);
		return ned;
	}
	Vector3
    NEU_to_NED
    (
		const Vector3& neu_to, 	
		const Vector3& neu_from = Vector3{ 0, 0,10000. }   ) 
	{
		return Vector3(NEU_to_NED(neu_to.get_list(), neu_from.get_list()));
	}


	::std::array<float64_t,3> 
	LLA_to_ECEF(const ::std::array<float64_t,3>& lla_to) noexcept 
	// lla_from = {0., 0., 0.}, center of ECEF
	{
		float64_t b = 6356752.3142;
		float64_t f = 1 / 298.257223565;
		float64_t e2 = f * (2 - f);
		float64_t a = 6378137.0;
		float64_t N = a / sqrt(1 - e2 * sin(lla_to[1]) * sin(lla_to[1]));

		::std::array<float64_t,3> ECEF;
		ECEF[0] = (N + lla_to[2]) * cos(lla_to[1]) * cos(lla_to[0]);
		ECEF[1] = (N + lla_to[2]) * cos(lla_to[1]) * sin(lla_to[0]);
		ECEF[2] = (N * (1 - e2) + lla_to[2]) * sin(lla_to[1]);
		return ECEF;
	}

	::std::array<float64_t,3> 
	LLA_to_NWU
	(
		const ::std::array<float64_t,3>& lla_to,
		const ::std::array<float64_t,3>& lla_from    ) noexcept 
	{

		float64_t Delt[3];
		float64_t M[3][3];
		float64_t ENU[3];

		::std::array<float64_t,3> AECF = LLA_to_ECEF(lla_from);
		::std::array<float64_t,3> BECF = LLA_to_ECEF(lla_to);

		Delt[0] = BECF[0] - AECF[0];
		Delt[1] = BECF[1] - AECF[1];
		Delt[2] = BECF[2] - AECF[2];

		M[0][0] = -sin(lla_from[0]);
		M[0][1] = cos(lla_from[0]);
		M[0][2] = 0;
		M[1][0] = -sin(lla_from[1]) * cos(lla_from[0]);
		M[1][1] = -sin(lla_from[1]) * sin(lla_from[0]);
		M[1][2] = cos(lla_from[1]);
		M[2][0] = cos(lla_from[1]) * cos(lla_from[0]);
		M[2][1] = cos(lla_from[1]) * sin(lla_from[0]);
		M[2][2] = sin(lla_from[1]);

		ENU[0] = M[0][0] * Delt[0] + M[0][1] * Delt[1] + M[0][2] * Delt[2];
		ENU[1] = M[1][0] * Delt[0] + M[1][1] * Delt[1] + M[1][2] * Delt[2];
		ENU[2] = M[2][0] * Delt[0] + M[2][1] * Delt[1] + M[2][2] * Delt[2];

		::std::array<float64_t, 3> NWU;
		NWU[0] = ENU[1];
		NWU[1] = -ENU[0];
		NWU[2] = ENU[2];
		return NWU;
	}

	Vector3
	LLA_to_NWU
	(
		Vector3& lla_to,
		Vector3& lla_from    ) noexcept 
	{
		return Vector3(LLA_to_NWU(lla_to.get_list(),lla_from.get_list()));
	}

}
