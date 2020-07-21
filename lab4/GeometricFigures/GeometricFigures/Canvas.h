#pragma once
#include "Point.h"
#include <vector>

class ICanvas
{
public:
	ICanvas() = default;

	virtual void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) = 0;
	virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(const CPoint& center, float radius, uint32_t lineColor) = 0;
	virtual void FillCircle(const CPoint& center, float radius, uint32_t fillColor) = 0;

	virtual ~ICanvas() = default;
};
