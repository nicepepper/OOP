#include "Rectangle.h"
#include "Uint32ToHex.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CRectangle::CRectangle(const uint32_t outlineColor, const uint32_t fillColor, const CPoint& topLeft, const CPoint& rightBottom)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_leftTopPoint(topLeft)
	, m_rightBottomPoint(rightBottom)
{
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomPoint;
}

double CRectangle::GetWidth() const
{
	return std::abs(m_leftTopPoint.GetX() - m_rightBottomPoint.GetX());
}

double CRectangle::GetHeight() const
{
	return std::abs(m_leftTopPoint.GetY() - m_rightBottomPoint.GetY());
}

double CRectangle::GetArea() const
{
	return GetHeight() * GetWidth();
}

double CRectangle::GetPerimeter() const
{
	return (GetHeight() + GetWidth()) * 2;
}

std::string CRectangle::ToString() const
{
	using namespace std;
	std::ostringstream stream;
	stream << "rectangle ";
	stream << fixed << showpoint << setprecision(2) << m_leftTopPoint.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_leftTopPoint.GetY() << " ";
	stream << fixed << showpoint << setprecision(2) << m_rightBottomPoint.GetX() << " ";
	stream << fixed << showpoint << setprecision(2) << m_rightBottomPoint.GetY() << " ";
	stream << Uint32ToHexString(GetFillColor()) << " " << Uint32ToHexString(GetOutlineColor());
	return stream.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{

	CPoint rightTop = CPoint(m_rightBottomPoint.GetX(), m_leftTopPoint.GetY());
	CPoint bottomLeft = CPoint(m_leftTopPoint.GetX(), m_rightBottomPoint.GetY());
	std::vector<CPoint> vector = { m_leftTopPoint, rightTop, m_rightBottomPoint, bottomLeft };
	canvas.FillPolygon(vector, GetFillColor());
	canvas.DrawLine(m_leftTopPoint, rightTop, GetOutlineColor());
	canvas.DrawLine(rightTop, m_rightBottomPoint, GetOutlineColor());
	canvas.DrawLine(m_rightBottomPoint, bottomLeft, GetOutlineColor());
	canvas.DrawLine(bottomLeft, m_leftTopPoint, GetOutlineColor());
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}