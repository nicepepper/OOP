#pragma once

class CPoint
{
public:
	CPoint(double x, double y);
	~CPoint() = default;

	double GetX() const;
	double GetY() const;
	void SetX(double x);
	void SetY(double y);

private:
	double m_x, m_y;
};
