#include "VectorFunctions.h"

CVector3D Normalize(const CVector3D& v)
{
	CVector3D vCopy = v;
	vCopy.Normalize();
	return vCopy;
}

CVector3D CrossProduct(const CVector3D& v1, const CVector3D& v2)
{
	const auto xCross = v1.y * v2.z - v2.y * v1.z;
	const auto yCross = -(v1.x * v2.z - v2.x * v1.z);
	const auto zCross = v1.x * v2.y - v2.x * v1.y;

	return CVector3D(xCross, yCross, zCross);
}

double DotProduct(const CVector3D& v1, const CVector3D& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}