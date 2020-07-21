#include "Circle.h"
#include "Uint32ToHex.h"
#include <iomanip>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(const uint32_t outlineColor, const uint32_t fillColor,const CPoint& center, const float radius)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Negative circle radius");
	}
}

double CCircle::GetArea() const
{
	return M_PI * std::pow(double(m_radius), 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * double(m_radius);
}

std::string CCircle::ToString() const
{
	std::ostringstream stream;
	stream << "circle ";
	stream << std::fixed << std::showpoint << std::setprecision(2) << m_center.GetX() << " ";
	stream << std::fixed << std::showpoint << std::setprecision(2) << m_center.GetY() << " ";
	stream << m_radius << " ";
	stream << Uint32ToHexString(GetFillColor()) << " " << Uint32ToHexString(GetOutlineColor());
	return stream.str();
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

float CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
	canvas.FillCircle(m_center, m_radius, GetFillColor());
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}
