#pragma once
#include "Canvas.h"
#include <SFML/Graphics.hpp>
#include "Shape.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(unsigned int windowWidth, unsigned int windowHeight, const std::string& name);
	~CCanvas();

	void DrawShapes(std::vector<std::shared_ptr<IShape>>& shapes);
	void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint>& points, uint32_t fillColor) override;
	void DrawCircle(const CPoint& center, float radius, uint32_t lineColor) override;
	void FillCircle(const CPoint& center, float radius, uint32_t fillColor) override;
	void Redraw(std::vector<std::shared_ptr<IShape>>& shapes);

private:
	sf::RenderWindow m_window;
	unsigned int m_windowWidth, m_windowHeight;
	std::string m_windowName;
};
