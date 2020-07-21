#include "CCanvas.h"
#include <SFML/System.hpp>
#include "Shape.h"
#include "ShapesCLI.h"
#include <iostream>

CCanvas::CCanvas(unsigned int windowWidth, unsigned int windowHeight, const std::string& name)
	: m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_windowName(name)
{
	m_window.setActive(false);
}

void CCanvas::DrawShapes(std::vector<std::shared_ptr<IShape>>& shapes)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), m_windowName, sf::Style::Default, settings);

	Redraw(shapes);
	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				break;
			}

			if (event.type == sf::Event::Resized)
			{
				Redraw(shapes);
			}
		}
	}
}

CCanvas::~CCanvas()
{
}

void CCanvas::Redraw(std::vector<std::shared_ptr<IShape>>& shapes)
{
	if (m_window.isOpen())
	{
		m_window.clear();
		for (auto& shape : shapes)
		{
			shape->Draw(*this);
		}
		m_window.display();
	}
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor)
{
	if (m_window.isOpen())
	{
		sf::VertexArray lines(sf::Lines, 2);

		lines[0].position = sf::Vector2f(float(from.GetX()), float(from.GetY()));
		lines[0].color = sf::Color(lineColor);

		lines[1].position = sf::Vector2f(float(to.GetX()), float(to.GetY()));
		lines[1].color = sf::Color(lineColor);

		m_window.draw(lines);
	}
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor)
{
	if (m_window.isOpen())
	{
		sf::ConvexShape polygon;
		polygon.setPointCount(points.size());
		for (size_t i = 0; i < points.size(); i++)
		{
			polygon.setPoint(i, sf::Vector2f(float(points[i].GetX()), float(points[i].GetY())));
		}
		polygon.setFillColor(sf::Color(fillColor));
		m_window.draw(polygon);
	}
}

void CCanvas::DrawCircle(const CPoint& center, float radius, uint32_t lineColor)
{
	if (m_window.isOpen())
	{
		sf::CircleShape shape(radius);
		shape.setOutlineColor(sf::Color(lineColor));
		shape.setOutlineThickness(1);
		shape.setPosition(float(center.GetX()) - radius, float(center.GetY()) - radius);
		m_window.draw(shape);
	}
}

void CCanvas::FillCircle(const CPoint& center, float radius, uint32_t fillColor)
{
	if (m_window.isOpen())
	{
		sf::CircleShape shape(radius);
		shape.setFillColor(sf::Color(fillColor));
		shape.setPosition(float(center.GetX()) - radius, float(center.GetY()) - radius);
		m_window.draw(shape);
	}
}
