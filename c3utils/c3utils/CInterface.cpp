#pragma once 

#include "Def.h"

extern "C" {

	typedef struct Vector2 {
		double x;
		double y;
        void* c3u_vec;
	} Vector2;

	typedef struct Vector3 {
		double x;
		double y;
		double z;
        void* c3u_vec;
	} Vector3;

	Vector2* Vector2_create(double x, double y);
	Vector2* Vector2_create_from_list(const double* list, int size);
	Vector2* Vector2_copy(const Vector2* other);
	void Vector2_destroy(Vector2* vec);
	void Vector2_prod(Vector2* vec, double scalar);
	void Vector2_add(Vector2* vec, const Vector2* other);
	double* Vector2_get_list(const Vector2* vec);
	double Vector2_get_prod(const Vector2* vec);
	double Vector2_get_dot(const Vector2* vec, const Vector2* other);
	double Vector2_get_module(const Vector2* vec, int non_zero);
	double Vector2_get_angle(const Vector2* vec);

	Vector3* Vector3_create(double x, double y, double z);
	Vector3* Vector3_create_from_list(const double* list, int size);
	Vector3* Vector3_copy(const Vector3* other);
	void Vector3_destroy(Vector3* vec);
	void Vector3_rotate_xyz_fix(Vector3* vec, double roll, double pitch, double yaw);
	void Vector3_rev_rotate_xyz_fix(Vector3* vec, double roll, double pitch, double yaw);
	void Vector3_rotate_xyz_self(Vector3* vec, double roll, double pitch, double yaw);
	void Vector3_rev_rotate_xyz_self(Vector3* vec, double roll, double pitch, double yaw);
	void Vector3_rotate_zyx_self(Vector3* vec, double roll, double pitch, double yaw);
	void Vector3_rev_rotate_zyx_self(Vector3* vec, double roll, double pitch, double yaw);
	double Vector3_get_angle(const Vector3* vec, const Vector3* other, int pid_set_zero, int pid_sign_dim);
	void Vector3_prod(Vector3* vec, double scalar);
	double Vector3_get_prod(const Vector3* vec);
	double Vector3_get_dot(const Vector3* vec, const Vector3* other);
	void Vector3_add(Vector3* vec, const Vector3* other);
	double Vector3_get_module(const Vector3* vec, int non_zero);
	double* Vector3_get_list(const Vector3* vec);

	double norm(double x, double lower_side, double upper_side);
	double meters_to_feet(double meters);
	double feet_to_meters(double feet);
	double no_neg(double num);
	Vector3* make_vector3(const Vector2* vector2, double z);
	Vector3* copy_vector3(const Vector3* vector3);
	double abs_val(double num);
	double pwr(double num);

}

