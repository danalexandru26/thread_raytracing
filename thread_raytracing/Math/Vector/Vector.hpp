#pragma once
#include<iostream>

namespace math
{
	template<typename T>
	struct vec3
	{
	public:
		vec3();
		vec3(T x, T y, T z);
		vec3(T scalar);

		vec3(const vec3& other);
		vec3& operator=(vec3 other);

		vec3 operator-() const;

		vec3& operator+=(const vec3<T>& rhs);

		vec3& operator/= (T scalar);

		vec3& operator*=(T scalar);
		template<typename Q>
		vec3& operator*=(Q scalar);

		bool near_zero() const;

		T x();
		T y();
		T z();

		T length() const;
		T length_squared() const;
	private:
		void swap(vec3& lhs, vec3& rhs);
	public:
		T data[3];
	};

	template<typename T>
	bool operator==(const vec3<T>& lhs, const vec3<T>& rhs);
	template<typename T>
	bool operator!=(const vec3<T>& lhs, const vec3<T>& rhs);

	template<typename T>
	vec3<T> operator+(const vec3<T>& lhs, const vec3<T>& rhs);
	
	template<typename T>
	vec3<T> operator-(const vec3<T>& lhs, const vec3<T>& rhs);

	template<typename T>
	vec3<T> operator*(const vec3<T>& lhs, const vec3<T>& rhs);
	template<typename T>
	vec3<T> operator*(T scalar, const vec3<T>& rhs);
	template<typename T>
	vec3<T> operator*(const vec3<T>& lhs, T scalar);

	template<typename T>
	vec3<T> operator/(const vec3<T>& lhs, const vec3<T>& rhs);
	template<typename T>
	vec3<T> operator/(const vec3<T>& lhs, T scalar);
	template<typename T>
	vec3<T> operator/(T scalar, const vec3<T>& rhs);

	template<typename T>
	T dot(const vec3<T>& lhs, const vec3<T>& rhs);

	template<typename T>
	vec3<T> unit(const vec3<T>& lhs);

	template<typename T>
	vec3<T> reflect(const vec3<T>& v, const vec3<T> n);
}
#include"Vector.inl"
