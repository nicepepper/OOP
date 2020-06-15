#include "Vector3D.h"
#include <cfloat>
#include <cmath>

CVector3D::CVector3D()
	: x(0)
	, y(0)
	, z(0)
{
}

CVector3D::CVector3D(const double x, const double y, const double z)
	: x(x)
	, y(y)
	, z(z)
{
}

CVector3D::CVector3D(const CVector3D&& v) noexcept
	: x(v.x)
	, y(v.y)
	, z(v.z)
{
}

double CVector3D::GetLength() const
{
	using namespace std;

	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void CVector3D::Normalize()
{
	const auto len = GetLength();

	if (len == 0)
	{
		return;
	}

	x = x / len;
	y = y / len;
	z = z / len;
}

CVector3D CVector3D::operator+(const CVector3D& v) const
{
	return CVector3D(x + v.x, y + v.y, z + v.z);
}

CVector3D CVector3D::operator-(const CVector3D& v) const
{
	return CVector3D(x - v.x, y - v.y, z - v.z);
}

CVector3D& CVector3D::operator-=(const CVector3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

CVector3D& CVector3D::operator+=(const CVector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

CVector3D CVector3D::operator-() const
{
	return CVector3D(-x, -y, -z);
}

CVector3D CVector3D::operator+() const
{
	return CVector3D(x, y, z);
}

CVector3D CVector3D::operator/(const double scalar) const
{
	if (scalar == 0)
	{
		throw std::logic_error("Division by zero");
	}

	return CVector3D(x / scalar, y / scalar, z / scalar);
}

CVector3D CVector3D::operator*(const double scalar) const
{
	return CVector3D(x * scalar, y * scalar, z * scalar);
}

CVector3D& CVector3D::operator*=(const double scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

CVector3D& CVector3D::operator/=(const double scalar)
{
	if (scalar == 0)
	{
		throw std::logic_error("Division by zero");
	}

	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

bool CVector3D::operator==(const CVector3D& v) const
{
	const auto isXEqual = std::abs(x - v.x) < DBL_EPSILON;
	const auto isYEqual = std::abs(y - v.y) < DBL_EPSILON;
	const auto isZEqual = std::abs(z - v.z) < DBL_EPSILON;

	return (isXEqual && isYEqual && isZEqual);
}

bool CVector3D::operator!=(const CVector3D& v) const
{
	return !(*this == v);
}

CVector3D& CVector3D::operator=(CVector3D&& v) noexcept
{
	if (this != &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& out, const CVector3D& v)
{
	out << v.x << ' ' << v.y << ' ' << v.z;

	return out;
}

std::istream& operator>>(std::istream& in, CVector3D& v)
{
	in >> v.x >> v.y >> v.z;

	return in;
}
