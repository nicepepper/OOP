#pragma once
#include "CanvasDrawable.h"
#include <string>

class IShape : public ICanvasDrawable
{
public:
	IShape() = default;
	virtual ~IShape() = default;
	
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};