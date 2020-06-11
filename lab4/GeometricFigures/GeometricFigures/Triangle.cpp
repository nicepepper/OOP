#include "Triangle.h"
#include "Uint32ToHex.h"
#include <iomanip>
#include <sstream>

CTriangle::CTriangle(const uint32_t outlineColor, const uint32_t fillColor, const CPoint& p1, const CPoint& p2, const CPoint& p3)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
{
}

CPoint CTriangle::GetVertex1() const
{
	return m_p1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_p2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_p3;
}

double CTriangle::GetArea() const
{
	return ((m_p2.GetX() - m_p1.GetX()) * (m_p3.GetY() - m_p1.GetY()) - (m_p3.GetX() - m_p1.GetX()) * (m_p2.GetY() - m_p1.GetY())) / 2;
}

double CTriangle::GetPerimeter() const
{
	double len1 = std::sqrt(std::pow(m_p2.GetX() - m_p1.GetX(), 2) + std::pow(m_p2.GetY() - m_p1.GetY(), 2));
	double len2 = std::sqrt(std::pow(m_p3.GetX() - m_p1.GetX(), 2) + std::pow(m_p3.GetY() - m_p1.GetY(), 2));
	double len3 = std::sqrt(std::pow(m_p3.GetX() - m_p2.GetX(), 2) + std::pow(m_p3.GetY() - m_p2.GetY(), 2));
	return len1 + len2 + len3;
}

std::string CTriangle::ToString() const
{
	using namespace std;
	std::ostringstream stream;

	stream << "triangle ";
	stream << fixed << showpoint << setprecision(2) << m_p1.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p1.GetY() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p2.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p2.GetY() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p3.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_p3.GetY() << " ";
	stream << Uint32ToHexString(GetFillColor()) << " " << Uint32ToHexString(GetOutlineColor());
	return stream.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = { m_p1, m_p2, m_p3 };

	canvas.FillPolygon(points, GetFillColor());
	canvas.DrawLine(m_p1, m_p2, GetOutlineColor());
	canvas.DrawLine(m_p2, m_p3, GetOutlineColor());
	canvas.DrawLine(m_p3, m_p1, GetOutlineColor());
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}