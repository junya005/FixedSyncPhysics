#pragma once

#include <gtest/gtest.h>
#include <FixedSyncPhysics/Math/Fixed.hpp>
#include <cstdint>
#include <iostream>

TEST(Fixed_q16_16, ValueCheck) {
	// 整数部を1とした数字で初期化
	Fixed_q16_16 testFixed1 = Fixed_q16_16(1);

	// コンストラクタで初期化時に左に16SHIFT、0000 0001 0000 0000となり、
	// 16bitの最大値+1であるはずなので、65536と比較
	EXPECT_EQ(65536, testFixed1.RawValue());

	Fixed_q16_16 testFixed2 = Fixed_q16_16(0.5);
	// 半分の0.5は右に1シフトした数字であるため、0000 0000 1000 0000となり、
	// 65536の半分であるはずなので、32768と比較
	EXPECT_EQ(32768, testFixed2.RawValue());
};

