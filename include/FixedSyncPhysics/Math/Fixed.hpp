#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>

class Fixed_q16_16
{
private:
	int32_t value;
	static constexpr int SHIFT = 16;
	static constexpr int64_t ONE = 1LL << SHIFT;

	// コンストラクタオーバーロード解決用のタグ
	struct RawTag {};

	constexpr Fixed_q16_16(int32_t v, RawTag) :value(v){}

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

	// コピーコンストラクタ
	explicit constexpr Fixed_q16_16(const Fixed_q16_16& other):value(other.value){}

	/// <summary>
	/// 内部数値を取得します
	/// </summary>
	/// <returns>内部数値</returns>
	constexpr int32_t RawValue() const { return value; }

	/// <summary>
	/// 小数部分を取得します
	/// </summary>
	/// <returns>小数部分のfloat</returns>
	constexpr float GetFractionalValue() const {
		int32_t fraction = value & 0xFFFF;
		return static_cast<float>(fraction) / static_cast<float>(1 << SHIFT);
	}

	/// <summary>
	/// 整数部分を取得します
	/// </summary>
	/// <returns>整数部分のint</returns>
	constexpr int GetIntegerValue() const { return value >> SHIFT; }

	/// <summary>
	/// 内部数値から直接インスタンスを生成する関数
	/// </summary>
	/// <param name="other">内部数値</param>
	/// <returns>生成した固定小数点クラス</returns>
	static constexpr Fixed_q16_16 FromRaw(int32_t other) {
		return Fixed_q16_16(other, RawTag{});
	}

	// 演算子オーバーロード
	// 加算
	Fixed_q16_16 operator+(const Fixed_q16_16& other) const { return Fixed_q16_16::FromRaw(value + other.value); }

	// 減算
	Fixed_q16_16 operator-(const Fixed_q16_16& other) const { return Fixed_q16_16::FromRaw(value - other.value); }

	// 乗算
	Fixed_q16_16 operator*(const Fixed_q16_16& other) const {
		// オーバーロードを防ぐため、計算時にint64_tにキャストする
		int64_t result = static_cast<int64_t>(value) * static_cast<int64_t>(other.value);
		return Fixed_q16_16::FromRaw(static_cast<int32_t>(result >> SHIFT));
	}

	// 除算
	Fixed_q16_16 operator/(const Fixed_q16_16& other) const {
		// 0割りチェック
		assert(other.value != 0 && "Division by zero");

		// 乗算と同様、オーバーロードを防ぐため、計算時にint64_tにキャストする
		int64_t result = static_cast<int64_t>(value << SHIFT) / other.value;
		return Fixed_q16_16::FromRaw(static_cast<int32_t>(result));
	}
};

