#include "Point.h"

CPoint::CPoint(const double x, const double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

void CPoint::SetX(double x)
{
	m_x = x;
}

void CPoint::SetY(double y)
{
	m_y = y;
}