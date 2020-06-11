#include "../GeometricFigures/GeometricFigures.h"
#include "../GeometricFigures/ParseLineAndCreateShape.h"

#define BOOST_TEST_MODULE GeometryTests
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

bool CheckPointEqual(const CPoint& p1, const CPoint& p2)
{
	return ((p1.GetX() == p2.GetX()) && (p1.GetY() == p2.GetY()));
}

BOOST_AUTO_TEST_SUITE(Circle)

	BOOST_AUTO_TEST_CASE(CheckCirclePerimeterAndArea)
	{
		CPoint point(100, 100);

		CCircle circle(0, 0, point, 35.55f);

		BOOST_TEST(circle.GetArea() == 3970.3526, tt::tolerance(0.001));

		BOOST_TEST(circle.GetPerimeter() == 223.3672, tt::tolerance(0.001));
	}

	BOOST_AUTO_TEST_CASE(CircleReturnsHisRadius)
	{
		CPoint point(100, 100);

		CCircle circle(0, 0, point, 35.55f);

		BOOST_CHECK_EQUAL(circle.GetRadius(), 35.55f);
	}

	BOOST_AUTO_TEST_CASE(CircleReturnsHisCenter)
	{
		CPoint point(100, 100);

		CCircle circle(0, 0, point, 35.55f);

		BOOST_CHECK(CheckPointEqual(point, circle.GetCenter()));
	}

	BOOST_AUTO_TEST_CASE(CircleClassThrowsWhenRadiusNegative)
	{
		CPoint point(100, 100);

		BOOST_CHECK_THROW(CCircle circle(0, 0, point, -35.55f), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(CheckCircleToStringMethod)
	{
		CPoint point(100, 100);

		CCircle circle(0, 0, point, 35.55f);

		BOOST_CHECK(circle.ToString() == "circle 100.00 100.00 35.55 0 0");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle)

	BOOST_AUTO_TEST_CASE(CheckTrianglePerimeterAndArea)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 400);
		CPoint p3(100, 320);
		CTriangle tri(0, 0, p1, p2, p3);

		BOOST_TEST(tri.GetArea() == 33000.000, tt::tolerance(0.001));
		BOOST_TEST(tri.GetPerimeter() == 954.73, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(TriangleReturnsZeroAreaWhenPointsAreInTheSameLine)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 400);
		CPoint p3(320, 320);
		CTriangle tri(0, 0, p1, p2, p3);

		BOOST_TEST(tri.GetArea() == 0.000, tt::tolerance(0.001));
		BOOST_TEST(tri.GetPerimeter() == 848.53, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(TriangleReturnsValidVertexes)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 400);
		CPoint p3(320, 320);
		CTriangle tri(0, 0, p1, p2, p3);

		BOOST_CHECK(CheckPointEqual(p1, tri.GetVertex1()));
		BOOST_CHECK(CheckPointEqual(p2, tri.GetVertex2()));
		BOOST_CHECK(CheckPointEqual(p3, tri.GetVertex3()));
	}

	BOOST_AUTO_TEST_CASE(CheckTriangleToStringMethod)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 400);
		CPoint p3(100, 320);
		CTriangle tri(4278255615, 4278255615, p1, p2, p3);

		BOOST_CHECK(tri.ToString() == "triangle 100.00 100.00 400.00 400.00 100.00 320.00 ff00ffff ff00ffff");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle)

	BOOST_AUTO_TEST_CASE(CreateRectangleAndCheckItsParams)
	{
		CPoint p1(100, 100);
		CPoint p2(140, 70);
		CRectangle rect(0, 0, p1, p2);

		BOOST_TEST(rect.GetArea() == 1200.0, tt::tolerance(0.001));
		BOOST_TEST(rect.GetPerimeter() == 140.0, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(CreateRectangleWithReversedConersAndCheckItsAreaAndPerimeter)
	{
		CPoint p1(140, 70);
		CPoint p2(100, 100);
		CRectangle rect(0, 0, p1, p2);

		BOOST_TEST(rect.GetArea() == 1200.0, tt::tolerance(0.001));
		BOOST_TEST(rect.GetPerimeter() == 140.0, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(RectMustReturnZeroArea)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 100);
		CRectangle rect(0, 0, p1, p2);

		BOOST_TEST(rect.GetArea() == 0.0, tt::tolerance(0.001));
		BOOST_TEST(rect.GetPerimeter() == 600.0, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(CheckRectangleToStringMethod)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 100);
		CRectangle rect(1431655765, 1431655765, p1, p2);

		BOOST_CHECK(rect.ToString() == "rectangle 100.00 100.00 400.00 100.00 55555555 55555555");
	}

	BOOST_AUTO_TEST_CASE(RectReturnsHisVertexes)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 100);
		CRectangle rect(1431655765, 1431655765, p1, p2);

		BOOST_CHECK(CheckPointEqual(p1, rect.GetLeftTop()));
		BOOST_CHECK(CheckPointEqual(p2, rect.GetRightBottom()));
	}

	BOOST_AUTO_TEST_CASE(RectReturnsHisWidthAndHeight)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 400);
		CRectangle rect(0, 0, p1, p2);

		BOOST_CHECK_EQUAL(rect.GetWidth(), 300);

		BOOST_CHECK_EQUAL(rect.GetHeight(), 300);
	}

	BOOST_AUTO_TEST_CASE(RectReturnsHisWidthAndHeightWhenPointsReversed)
	{
		CPoint p1(400, 400);
		CPoint p2(100, 100);
		CRectangle rect(0, 0, p1, p2);

		BOOST_CHECK_EQUAL(rect.GetWidth(), 300);

		BOOST_CHECK_EQUAL(rect.GetHeight(), 300);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Line)

	BOOST_AUTO_TEST_CASE(CreateLineAndValidateIt)
	{
		CPoint p1(100, 100);
		CPoint p2(400, 100);
		CLineSegment line(0, p1, p2);

		BOOST_TEST(line.GetArea() == 0.0, tt::tolerance(0.001));
		BOOST_TEST(line.GetPerimeter() == 300.0, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(CreateDotLineAndCheckItsParams)
	{
		CPoint p1(100, 100);
		CLineSegment line(0, p1, p1);

		BOOST_TEST(line.GetArea() == 0.0, tt::tolerance(0.001));
		BOOST_TEST(line.GetPerimeter() == 0.0, tt::tolerance(0.5));
	}

	BOOST_AUTO_TEST_CASE(CheckLineToStringMethod)
	{
		CPoint p1(100, 100);
		CLineSegment line(0, p1, p1);

		BOOST_CHECK(line.ToString() == "line 100.00 100.00 100.00 100.00 0");
	}

	BOOST_AUTO_TEST_CASE(LineReturnsItsVertexes)
	{
		CPoint p1(100, 100);
		CPoint p2(1000, 199);

		CLineSegment line(0, p1, p2);

		BOOST_CHECK(CheckPointEqual(p1, line.GetStartPoint()));
		BOOST_CHECK(CheckPointEqual(p2, line.GetEndPoint()));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestParseLineAndShapesModule)

	BOOST_AUTO_TEST_CASE(TestLinesThatCanBeParsed)
	{
		std::vector<std::string> validLines = {
			"rectangle 0 0 10 10 fff aaa",
			"triangle 0.123 0.321 10.123 10.123 10.123 10.0 fff aaa",
			"circle 0 0 150 ffffffff aaaffff",
			"line 0 0 150 89 fcecec aaaffff"
		};

		for (auto& line : validLines)
		{
			auto shape = CreateShape(line);
			if (!shape)
			{
				BOOST_FAIL("CreateShape() do not recognize valid string" + line);
			}
		}
	}

	BOOST_AUTO_TEST_CASE(TestLinesThatCannotBeParsed)
	{
		std::vector<std::string> invalidLines = {
			"rectangle 0 0 10 10 fff fffffffff",
			"triangle aaa 0.321 10.123 10.123 10.123 10.0 fff aaa",
			"circle 0 0 150 ffffffff aaaffff",
			"line 0 0 150 89 aaaffffaa",
			"circle 1 0 150 #ffffffff #aaaffff",
		};

		for (auto& line : invalidLines)
		{
			if (auto shape = CreateShape(line))
			{
				BOOST_FAIL("CreateShape() recognize invalid string " + line);
			}
		}
	}

BOOST_AUTO_TEST_SUITE_END()
