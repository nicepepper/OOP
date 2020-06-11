#pragma once
#include "Canvas.h"

class ICanvasDrawable
{
public:
	ICanvasDrawable() = default;

	virtual ~ICanvasDrawable() = default;
	virtual void Draw(ICanvas& canvas) const = 0;
};
