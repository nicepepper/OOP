#pragma once
#include <istream>

class CVector3D
{
public:
	CVector3D();
	CVector3D(double x, double y, double z);
	CVector3D(const CVector3D& v) = default;
	CVector3D(const CVector3D&& v) noexcept;
	~CVector3D() = default;

	double GetLength() const;
	void Normalize();

	CVector3D& operator=(const CVector3D& v) = default;
	CVector3D& operator=(CVector3D&&) noexcept;
	
	CVector3D operator-() const;
	CVector3D operator+() const;
	CVector3D operator+(const CVector3D& v) const;
	CVector3D operator-(const CVector3D& v) const;
	
	CVector3D& operator-=(const CVector3D& v);
	CVector3D& operator+=(const CVector3D& v);
	
	CVector3D operator/(double scalar) const;
	CVector3D operator*(double scalar) const;
	CVector3D& operator*=(double scalar);
	CVector3D& operator/=(double scalar);

	bool operator==(const CVector3D& v) const;
	bool operator!=(const CVector3D& v) const;

	friend std::ostream& operator<<(std::ostream& out, const CVector3D& v);
	friend std::istream& operator>>(std::istream& in, CVector3D& v);

	double x, y, z;
};