#pragma once
#include "Shape.h"

class ISolidShape : public IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;
	virtual uint32_t GetFillColor() const = 0;
};
