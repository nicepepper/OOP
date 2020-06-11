#pragma once
#include "Point.h"
#include "Shape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(uint32_t outlineColor, const CPoint& p1, const CPoint& p2);
	~CLineSegment() = default;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;
	uint32_t GetOutlineColor() const override;

private:
	uint32_t m_outlineColor;
	CPoint m_p1, m_p2;
};
