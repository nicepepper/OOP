#pragma once
#include "Point.h"
#include "SolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(uint32_t outlineColor, uint32_t fillColor, const CPoint& p1, const CPoint& p2, const CPoint& p3);
	~CTriangle() = default;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

private:
	uint32_t m_outlineColor, m_fillColor;
	CPoint m_p1, m_p2, m_p3;
};
