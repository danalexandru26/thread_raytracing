namespace math
{
	template<typename T>
	vec3<T>::vec3()
		:data{}
	{}

	template<typename T>
	vec3<T>::vec3(T x, T y, T z)
		: data{x, y, z}
	{}

	template<typename T>
	vec3<T>::vec3(T scalar)
		: data{scalar, scalar, scalar}
	{}

	template<typename T>
	vec3<T>::vec3(const vec3& other)
	{
		data[0] = other.data[0];
		data[1] = other.data[1];
		data[2] = other.data[2];
	}

	template<typename T>
	vec3<T>& vec3<T>::operator= (vec3 other)
	{
		swap(*this, other);

		return *this;
	}

	template<typename T>
	void vec3<T>::swap(vec3& lhs, vec3& rhs)
	{
		using std::swap;

		swap(lhs.data, rhs.data);
	}

	template<typename T>
	vec3<T> vec3<T>::operator-() const
	{
		return vec3(-data[0], -data[1], -data[2]);
	}

	template<typename T>
	vec3<T>& vec3<T>::operator+=(const vec3<T>& rhs)
	{
		data[0] += rhs.data[0];
		data[1] += rhs.data[1];
		data[2] += rhs.data[2];

		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::operator /= (T scalar)
	{
		data[0] /= scalar;
		data[1] /= scalar;
		data[2] /= scalar;

		return *this;
	}


	template<typename T>
	vec3<T>& vec3<T>::operator*=(T scalar)
	{
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		
		return *this;
	}

	template<typename T>
	template<typename Q>
	vec3<T>& vec3<T>::operator*=(Q scalar)
	{
		data[0] *= static_cast<T>(scalar);
		data[1] *= static_cast<T>(scalar);
		data[2] *= static_cast<T>(scalar);
	
		return *this;
	}

	template<typename T>
	T vec3<T>::length() const
	{
		return std::sqrt(length_squared());
	}

	template<typename T>
	T vec3<T>::length_squared() const
	{
		return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
	}

	template<typename T>
	bool vec3<T>::near_zero() const {
		auto s = 1e-8;
		return (fabs(data[0]) < s) && (fabs(data[1]) < s) && (fabs(data[2]) < s);
	}


	template<typename T>
	bool operator==(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return lhs.data[0] == rhs.data[0] && lhs.data[1] == rhs.data[1] && lhs.data[2] == rhs.data[2];

	}
	
	template<typename T>
	bool operator!=(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	vec3<T> operator+(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return vec3<T>(lhs.data[0] + rhs.data[0], lhs.data[1] + rhs.data[1], lhs.data[2] + rhs.data[2]);
	}

	template<typename T>
	vec3<T> operator-(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return vec3<T>(lhs.data[0] - rhs.data[0], lhs.data[1] - rhs.data[1], lhs.data[2] - rhs.data[2]);
	}

	template<typename T>
	vec3<T> operator*(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return vec3<T>(lhs.data[0] * rhs.data[0], lhs.data[1] * rhs.data[1], lhs.data[2] * rhs.data[2]);
	}

	template<typename T>
	vec3<T> operator*(T scalar, const vec3<T>& rhs)
	{
		return vec3<T>(rhs.data[0] * scalar, rhs.data[1] * scalar, rhs.data[2] * scalar);
	}

	template<typename T>
	vec3<T> operator*(const vec3<T>& lhs, T scalar)
	{
		return scalar * lhs;
	}
	
	template<typename T>
	vec3<T> operator/(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return vec3<T>(lhs.data[0] / rhs.data[0], lhs.data[1] / rhs.data[1], lhs.data[2] / rhs.data[2]);
	}

	template<typename T>
	vec3<T> operator/(const vec3<T>& lhs, T scalar)
	{
		return vec3<T>(lhs.data[0] / scalar, lhs.data[1] / scalar, lhs.data[2] / scalar);
	}

	template<typename T>
	vec3<T> operator/(T scalar, const vec3<T>& rhs)
	{
		return rhs / scalar;
	}

	template<typename T>
	T vec3<T>::x()
	{
		return data[0];
	}

	template<typename T>
	T vec3<T>::y()
	{
		return data[1];
	}

	template<typename T>
	T vec3<T>::z()
	{
		return data[2];
	}

	template<typename T>
	T dot(const vec3<T>& lhs, const vec3<T>& rhs)
	{
		return lhs.data[0] * rhs.data[0] + lhs.data[1] * rhs.data[1] + lhs.data[2] * rhs.data[2];
	}

	template<typename T>
	vec3<T> unit(const vec3<T>& lhs)
	{
		return lhs / lhs.length();
	}


	template<typename T>
	vec3<T> reflect(const vec3<T>& v, const vec3<T> n) {
		return v - 2 * dot(v, n) * n;
	}
}