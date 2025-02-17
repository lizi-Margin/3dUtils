#pragma once

#include "external/pybind11/include/pybind11/pybind11.h"
#include "external/pybind11/include/pybind11/stl.h"
#include <sstream>
#include "c3utils.h"

namespace py = pybind11;

PYBIND11_MODULE(py_c3utils, m) {

	// Vector2 binding
	py::class_<c3u::Vector2>(m, "Vector2")
		.def(py::init<c3u::float64_t, c3u::float64_t>())
		.def(py::init<const std::array<c3u::float64_t,2>&>())
		.def(py::init<const c3u::Vector2&>())
		.def("prod", &c3u::Vector2::prod, py::return_value_policy::reference)
		.def("add", &c3u::Vector2::add, py::return_value_policy::reference)
		.def("get_list", &c3u::Vector2::get_list)
		.def("get_prod", &c3u::Vector2::get_prod)
		.def("get_dot", &c3u::Vector2::get_dot)
		.def("get_module", &c3u::Vector2::get_module, py::arg("non_zero") = false)
		.def("get_angle", &c3u::Vector2::get_angle)
		.def("__str__",
			[](const c3u::Vector2& v) {
				std::stringstream ss;
				ss << "Vector2@c3utils(" << v << ")";
				return ss.str();
			}
		)
		.def("__repr__",
			[](const c3u::Vector2& v) {
				std::stringstream ss;
				ss << v;
				return ss.str();
			}
		);

	// Vector3 binding
	py::class_<c3u::Vector3>(m, "Vector3")
		.def(py::init<c3u::float64_t, c3u::float64_t, c3u::float64_t>())
		.def(py::init<const std::array<c3u::float64_t,3>&>())
		.def(py::init<const c3u::Vector3&>())
		.def("rotate_xyz_fix", &c3u::Vector3::rotate_xyz_fix, py::return_value_policy::reference)
		.def("rev_rotate_xyz_fix", &c3u::Vector3::rev_rotate_xyz_fix, py::return_value_policy::reference)
		.def("rotate_xyz_self", &c3u::Vector3::rotate_xyz_self, py::return_value_policy::reference)
		.def("rev_rotate_xyz_self", &c3u::Vector3::rev_rotate_xyz_self, py::return_value_policy::reference)
		.def("rotate_zyx_self", &c3u::Vector3::rotate_zyx_self, py::return_value_policy::reference)
		.def("rev_rotate_zyx_self", &c3u::Vector3::rev_rotate_zyx_self, py::return_value_policy::reference)
		.def("get_angle", &c3u::Vector3::get_angle,
			py::arg("other"), py::arg("pid_set_zero") = -1, py::arg("pid_sign_dim") = -1)
		.def("prod", &c3u::Vector3::prod, py::return_value_policy::reference)
		.def("get_prod", &c3u::Vector3::get_prod)
		.def("get_dot", &c3u::Vector3::get_dot)
		.def("add", &c3u::Vector3::add, py::return_value_policy::reference)
		.def("get_module", &c3u::Vector3::get_module, py::arg("non_zero") = false)
		.def("get_list", &c3u::Vector3::get_list)
		.def("__getitem__", 
			[](const c3u::Vector3& v, size_t index) {
				if (index > 2) {
					throw py::index_error("Vector3: Index out of range.");
				}
				return v[index];
			}
		)
		.def("__setitem__", 
			[](c3u::Vector3& v, size_t index, c3u::float64_t value) {
				if (index > 2) {
					throw py::index_error("Vector3: Index out of range.");
				}
				v[index] = value;
			}
		)
		.def("__add__", 
			[](const c3u::Vector3& a, const c3u::Vector3& b) {
				return a + b;
			}
		)
		.def("__sub__", 
			[](const c3u::Vector3& a, const c3u::Vector3& b) {
				return a - b;
			}
		)
		.def("__eq__", 
			[](const c3u::Vector3& a, const c3u::Vector3& b) {
				return a == b;
			}
		)
		.def("__len__",
			[](const c3u::Vector3&) {
				return 3;
			}
		)
		.def("__str__",
			[](const c3u::Vector3& v) {
				return v.get_string();
			}
		)
		.def("__repr__",
			[](const c3u::Vector3& v) {
				return "Vector3@c3utils(" + v.get_string() + ")";
			}
		);
		//.def("__iter__", 
		//	[](const c3u::Vector3& v) {
		//		return py::make_iterator(v.vec.begin(), v.vec.end());
		//	}, 
		//	py::keep_alive<0, 1>()
		//);

	// Functions binding
	m.def("norm", &c3u::norm, py::arg("x"), py::arg("lower_side") = -1.0, py::arg("upper_side") = 1.0);
	m.def("meters_to_feet", &c3u::meters_to_feet, py::arg("meters"));
	m.def("feet_to_meters", &c3u::feet_to_meters, py::arg("feet"));
	m.def("no_neg", &c3u::no_neg, py::arg("num"));
	m.def("make_vector3", &c3u::make_vector3, py::arg("vector2"), py::arg("z") = 0.0);
	m.def("copy", &c3u::copy, py::arg("vector3"));
	m.def("abs", &c3u::abs, py::arg("num"));
	m.def("pwr", &c3u::pwr, py::arg("num"));

}
