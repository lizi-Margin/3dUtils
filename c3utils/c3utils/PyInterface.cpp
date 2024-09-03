#pragma once

#include "external/pybind11/include/pybind11/pybind11.h"
#include "external/pybind11/include/pybind11/stl.h"
#include <sstream>
#include "vector3.h"
#include "vector2.h"
#include "Funcs.h"

namespace py = pybind11;

PYBIND11_MODULE(py_c3utils, m) {

	// Vector2 binding
	py::class_<c3utils::Vector2>(m, "Vector2")
		.def(py::init<float64_t, float64_t>())
		.def(py::init<const ::std::array<float64_t,2>&>())
		.def(py::init<const c3utils::Vector2&>())
		.def("prod", &c3utils::Vector2::prod, py::return_value_policy::reference)
		.def("add", &c3utils::Vector2::add, py::return_value_policy::reference)
		.def("get_list", &c3utils::Vector2::get_list)
		.def("get_prod", &c3utils::Vector2::get_prod)
		.def("get_dot", &c3utils::Vector2::get_dot)
		.def("get_module", &c3utils::Vector2::get_module, py::arg("non_zero") = false)
		.def("get_angle", &c3utils::Vector2::get_angle)
		.def("__repr__",
			[](const c3utils::Vector2& v) {
				std::stringstream ss;
				ss << v;
				return ss.str();
			});

	py::class_<c3utils::Vector3>(m, "Vector3")
		.def(py::init<float64_t, float64_t, float64_t>())
		.def(py::init<const std::array<float64_t,3>&>())
		.def(py::init<const c3utils::Vector3&>())
		.def("rotate_xyz_fix", &c3utils::Vector3::rotate_xyz_fix, py::return_value_policy::reference)
		.def("rev_rotate_xyz_fix", &c3utils::Vector3::rev_rotate_xyz_fix, py::return_value_policy::reference)
		.def("rotate_xyz_self", &c3utils::Vector3::rotate_xyz_self, py::return_value_policy::reference)
		.def("rev_rotate_xyz_self", &c3utils::Vector3::rev_rotate_xyz_self, py::return_value_policy::reference)
		.def("rotate_zyx_self", &c3utils::Vector3::rotate_zyx_self, py::return_value_policy::reference)
		.def("rev_rotate_zyx_self", &c3utils::Vector3::rev_rotate_zyx_self, py::return_value_policy::reference)
		.def("get_angle", &c3utils::Vector3::get_angle,
			py::arg("other"), py::arg("pid_set_zero") = -1, py::arg("pid_sign_dim") = -1)
		.def("prod", &c3utils::Vector3::prod, py::return_value_policy::reference)
		.def("get_prod", &c3utils::Vector3::get_prod)
		.def("get_dot", &c3utils::Vector3::get_dot)
		.def("add", &c3utils::Vector3::add, py::return_value_policy::reference)
		.def("get_module", &c3utils::Vector3::get_module, py::arg("non_zero") = false)
		.def("get_list", &c3utils::Vector3::get_list)
		.def("__repr__",
			[](const c3utils::Vector3& v) {
				std::stringstream ss;
				ss << v;
				return ss.str();
			}
		);
	m.def("norm", &c3utils::norm, py::arg("x"), py::arg("lower_side") = -1.0, py::arg("upper_side") = 1.0);
	m.def("meters_to_feet", &c3utils::meters_to_feet, py::arg("meters"));
	m.def("feet_to_meters", &c3utils::feet_to_meters, py::arg("feet"));
	m.def("no_neg", &c3utils::no_neg, py::arg("num"));
	m.def("make_vector3", &c3utils::make_vector3, py::arg("vector2"), py::arg("z") = 0.0);
	m.def("copy", &c3utils::copy, py::arg("vector3"));
	m.def("abs", &c3utils::abs, py::arg("num"));
	m.def("pwr", &c3utils::pwr, py::arg("num"));

}
