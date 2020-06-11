#include "ParseLineAndCreateShape.h"
#include <iostream>
#include <sstream>

std::shared_ptr<CCircle> CreateCircle(double x, double y, float radius, uint32_t outline, uint32_t fill)
{
	CPoint center(x, y);
	return std::make_shared<CCircle>(outline, fill, center, radius);
}

std::shared_ptr<CTriangle> CreateTriangle(double x1, double y1, double x2, double y2, double x3, double y3, uint32_t outline, uint32_t fill)
{
	CPoint p1(x1, y1);
	CPoint p2(x2, y2);
	CPoint p3(x3, y3);
	return std::make_shared<CTriangle>(outline, fill, p1, p2, p3);
}

std::shared_ptr<CRectangle> CreateRectangle(double x1, double y1, double x2, double y2, uint32_t outline, uint32_t fill)
{
	CPoint topLeft(x1, y1);
	CPoint bottomRight(x2, y2);
	return std::make_shared<CRectangle>(outline, fill, topLeft, bottomRight);
}

std::shared_ptr<CLineSegment> CreateLine(double x1, double y1, double x2, double y2, uint32_t outline)
{
	CPoint start(x1, y1);
	CPoint end(x2, y2);
	return std::make_shared<CLineSegment>(outline, start, end);
}

uint32_t ReadColor(std::istringstream& stream)
{
	unsigned int color;
	stream >> std::hex >> color;
	return uint32_t(color);
}

std::shared_ptr<CCircle> ReadCircleParamsAndCreateShape(std::istringstream& stream)
{
	float x1, y1;
	float radius;
	stream >> x1 >> y1 >> radius;
	uint32_t outlineColor = ReadColor(stream);
	uint32_t fill = ReadColor(stream);
	return CreateCircle(x1, y1, radius, outlineColor, fill);
}

std::shared_ptr<CTriangle> ReadTriangleParamsAndCreateShape(std::istringstream& stream)
{
	float x1, x2, x3, y1, y2, y3;
	stream >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	uint32_t outlineColor = ReadColor(stream);
	uint32_t fill = ReadColor(stream);
	return CreateTriangle(x1, y1, x2, y2, x3, y3, outlineColor, fill);
}

std::shared_ptr<CRectangle> ReadRectangleParamsAndCreateShape(std::istringstream& stream)
{
	float x1, y1, x2, y2;
	stream >> x1 >> y1 >> x2 >> y2;
	uint32_t outlineColor = ReadColor(stream);
	uint32_t fill = ReadColor(stream);
	return CreateRectangle(x1, y1, x2, y2, outlineColor, fill);
}

std::shared_ptr<CLineSegment> ReadLineParamsAndCreateShape(std::istringstream& stream)
{
	float x1, x2, y1, y2;
	stream >> x1 >> y1 >> x2 >> y2;
	uint32_t outlineColor = ReadColor(stream);
	return CreateLine(x1, y1, x2, y2, outlineColor);
}

std::optional<std::shared_ptr<IShape>> CreateShape(const std::string& shapeDescription)
{
	std::istringstream stream(shapeDescription);
	stream.exceptions(std::ios::failbit);
	std::string line;
	try
	{
		if (stream >> line)
		{
			if (line == "line")
			{
				return ReadLineParamsAndCreateShape(stream);
			}

			if (line == "triangle")
			{
				return ReadTriangleParamsAndCreateShape(stream);
			}

			if (line == "rectangle")
			{
				return ReadRectangleParamsAndCreateShape(stream);
			}

			if (line == "circle")
			{
				return ReadCircleParamsAndCreateShape(stream);
			}
		}

		return std::nullopt;
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}
}