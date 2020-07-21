#include "ShapesCLI.h"
#include "CCanvas.h"
#include "ParseLineAndCreateShape.h"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <thread>
#include <vector>

void PrintResults(std::vector<std::shared_ptr<IShape>>& shapes, std::ostream& output)
{
	if (shapes.empty())
	{
		output << "There is no shapes were found" << std::endl;
		return;
	}

	double maxArea = 0;
	double minPerimeter = std::numeric_limits<double>::max();
	std::shared_ptr<IShape> maxAreaShape, minPerimeterShape;
	std::for_each(shapes.begin(), shapes.end(), [&](std::shared_ptr<IShape>& pointer) {
		if (pointer->GetArea() >= maxArea)
		{
			maxArea = pointer->GetArea();
			maxAreaShape = pointer;
		}

		if (pointer->GetPerimeter() <= minPerimeter)
		{
			minPerimeter = pointer->GetPerimeter();
			minPerimeterShape = pointer;
		}
	});

	output << "Max area: " << maxArea << ", Min perimeter: " << minPerimeter << std::endl;
	output << "Max area shape: " << maxAreaShape->ToString() << std::endl;
	output << "Min perimeter shape: " << minPerimeterShape->ToString() << std::endl;
}

void ShapesCLI(std::istream& input, std::ostream& output)
{
	std::vector<std::shared_ptr<IShape>> shapes;
	CCanvas canvas(800, 600, "Shapes window");
	std::string inStr;

	while (std::getline(input, inStr))
	{
		if (inStr == "stop")
		{
			break;
		}

		if (!inStr.empty())
		{
			if (auto ptr = CreateShape(inStr))
			{
				shapes.push_back(*ptr);
			}
			else
			{
				output << "Failed to recognize shape description in that string" << std::endl;
			}
		}
	}

	PrintResults(shapes, output);
	canvas.DrawShapes(shapes);
}
