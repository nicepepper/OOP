#include "LineSegment.h"
#include "Uint32ToHex.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CLineSegment::CLineSegment(const uint32_t outlineColor, const CPoint& p1, const CPoint& p2)
	: m_outlineColor(outlineColor)
	, m_p1(p1)
	, m_p2(p2)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	double vecX, vecY;
	vecX = m_p2.GetX() - m_p1.GetX();
	vecY = m_p2.GetY() - m_p1.GetY();
	return std::sqrt(std::pow(vecX, 2) + std::pow(vecY, 2));
}

std::string CLineSegment::ToString() const
{
	using namespace std;
	std::ostringstream stream;
	stream << "line ";
	stream << fixed << showpoint << setprecision(2) << m_p1.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p1.GetY() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p2.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p2.GetY() << " ";
	stream << Uint32ToHexString(GetOutlineColor());
	return stream.str();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_p1;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_p2;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_p1, m_p2, GetOutlineColor());
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}