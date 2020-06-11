#pragma once
#include "Point.h"
#include "SolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(uint32_t outlineColor, uint32_t fillColor, CPoint& center, float radius);
	~CCircle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	float GetRadius() const;
	void Draw(ICanvas& canvas) const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

private:
	CPoint m_center;
	float m_radius;
	uint32_t m_outlineColor, m_fillColor;
};
