#pragma once

#include <cstdint>
#include <iostream>

class Fixed_q16_16
{
private:
	int32_t value;
	static constexpr int SHIFT = 16;
	static constexpr int64_t ONE = 1LL << SHIFT;

public:
	// デフォルトコンストラクタ
	explicit constexpr Fixed_q16_16() : value(0) {}

	// 引数指定コンストラクタ群
	// intは整数値であるため、そのままシフト
	explicit constexpr Fixed_q16_16(int v) : value(v << SHIFT) {}

	// floatやdoubleは小数を含むため、整数部までシフトした数字を掛けた後に丸める
	// この手法はコンストラクタによる初期化時のみで、シミュレーション時には使用しない
	explicit constexpr Fixed_q16_16(float v) : value(static_cast<int32_t>(v* (1 << SHIFT))) {}
	explicit constexpr Fixed_q16_16(double v) : value(static_cast<int32_t> (v* (1 << SHIFT))) {}

	// getter
	constexpr int32_t RawValue() const { return value; }
};

