#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "c3utils.h"

int main() {
    // 测试旋转
    std::cout << "Testing 3D transformations..." << std::endl;
    c3u::Vector3 v1(1.0, 0.0, 0.0);
    std::cout << "Initial Vector: " << v1 << std::endl;

    // 旋转 180 度 (PI) 绕 Z 轴
    v1.rotate_xyz_fix(0, 0, EIGEN_PI);
    std::cout << "Rotated 180 degrees around Z-axis: " << v1 << std::endl;

    // 反向旋转 180 度 (PI) 绕 Z 轴
    v1.rev_rotate_xyz_fix(0, 0, EIGEN_PI);
    std::cout << "Reversed rotated 180 degrees around Z-axis: " << v1 << std::endl;

    // 测试 get_angle 方法
    std::cout << "\nTesting get_angle() method..." << std::endl;
    c3u::Vector3 v2(0.0, 1.0, 0.0);
    std::cout << "Vector1: " << v1 << std::endl;
    std::cout << "Vector2: " << v2 << std::endl;

    float64_t angle = v1.get_angle(v2);
    std::cout << "Angle between Vector1 and Vector2: " << angle << " radians" << std::endl;

    // 测试其他旋转方法
    std::cout << "\nTesting other rotation methods..." << std::endl;
    c3u::Vector3 v3(1.0, 0.0, 0.0);
    v3.rotate_zyx_self(EIGEN_PI / 2, EIGEN_PI / 2, EIGEN_PI / 2);
    std::cout << "Rotated 90 degrees around each axis (ZYX): " << v3 << std::endl;

    v3.rev_rotate_zyx_self(EIGEN_PI / 2, EIGEN_PI / 2, EIGEN_PI / 2);
    std::cout << "Reversed rotated 90 degrees around each axis (ZYX): " << v3 << std::endl;

    v3.rotate_xyz_self(EIGEN_PI / 2, EIGEN_PI / 2, EIGEN_PI / 2);
    std::cout << "Rotated 90 degrees around each axis (XYZ): " << v3 << std::endl;

    v3.rev_rotate_xyz_self(EIGEN_PI / 2, EIGEN_PI / 2, EIGEN_PI / 2);
    std::cout << "Reversed rotated 90 degrees around each axis (XYZ): " << v3 << std::endl;

    system("pause");
    return 0;
}
