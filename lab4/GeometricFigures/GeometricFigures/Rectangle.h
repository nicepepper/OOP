#pragma once
#include "Point.h"
#include "SolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(uint32_t outlineColor, uint32_t fillColor, const CPoint& topLeft, const CPoint& rightBottom);
	~CRectangle() = default;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

private:
	uint32_t m_outlineColor, m_fillColor;
	CPoint m_leftTopPoint, m_rightBottomPoint;
};
