#include "../Vector3D/Vector3D.h"
#include "../Vector3D/VectorFunctions.h"

#define BOOST_TEST_MODULE Vector3DTests
#include <boost/test/unit_test.hpp>
#include <sstream>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(Vector3D)

	BOOST_AUTO_TEST_CASE(VectorUnaryMinusOperator)
	{
		const CVector3D v1(-10, -15, -25);
		const CVector3D v2 = -v1;

		BOOST_CHECK((v2.x == 10) && (v2.y == 15) && (v2.z == 25));
	}

	BOOST_AUTO_TEST_CASE(VectorUnaryPlusOperator)
	{
		const CVector3D v1(-10, -15, -25);
		const CVector3D v2 = +v1;

		BOOST_CHECK((v2.x == -10) && (v2.y == -15) && (v2.z == -25));
	}

	BOOST_AUTO_TEST_CASE(VectorPlusOperator)
	{
		const CVector3D v2(10, 15, 25);
		const CVector3D v1(-10, -15, -25);

		const auto v3 = v2 + v1;

		BOOST_CHECK((v3.x == 0) && (v3.y == 0) && (v3.z == 0));
	}

	BOOST_AUTO_TEST_CASE(VectorPlusOperatorFloatingNumbers)
	{
		const CVector3D v2(14.23f, 11.7f, 12.05f);
		const CVector3D v1(19.11, -32.92, 71.2);

		const auto v3 = v2 + v1;

		BOOST_TEST(v3.x == 33.34, tt::tolerance(0.01));
		BOOST_TEST(v3.y == -21.22, tt::tolerance(0.01));
		BOOST_TEST(v3.z == 83.25, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorMinusOperator)
	{
		const CVector3D v1(-10, -15, -25);
		const CVector3D v2(-10, -15, -25);

		const auto v3 = v2 - v1;

		BOOST_CHECK((v3.x == 0) && (v3.y == 0) && (v3.z == 0));
	}

	BOOST_AUTO_TEST_CASE(VectorMinusOperatorFloatingNumbers)
	{
		const CVector3D v2(14.23f, 11.7f, 12.05f);
		const CVector3D v1(19.11, -32.92, 71.2);

		const auto v3 = v2 - v1;

		BOOST_TEST(v3.x == -4.88, tt::tolerance(0.01));
		BOOST_TEST(v3.y == 44.62, tt::tolerance(0.01));
		BOOST_TEST(v3.z == -59.15, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorEqualPlusOperator)
	{
		CVector3D v2(10, 15, 25);
		const CVector3D v1(-10, -15, -25);

		v2 += v1;

		BOOST_CHECK((v2.x == 0) && (v2.y == 0) && (v2.z == 0));
	}

	BOOST_AUTO_TEST_CASE(VectorEqualPlusOperatorFloatingNumbers)
	{
		CVector3D v2(14.23f, 11.7f, 12.05f);
		const CVector3D v1(19.11, -32.92, 71.2);

		v2 += v1;

		BOOST_TEST(v2.x == 33.34, tt::tolerance(0.01));
		BOOST_TEST(v2.y == -21.22, tt::tolerance(0.01));
		BOOST_TEST(v2.z == 83.25, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorEqualMinusOperator)
	{
		const CVector3D v1(-10, -15, -25);
		CVector3D v2(-10, -15, -25);

		v2 -= v1;

		BOOST_CHECK((v2.x == 0) && (v2.y == 0) && (v2.z == 0));
	}

	BOOST_AUTO_TEST_CASE(VectorEqualMinusOperatorFloatingNumbers)
	{
		const CVector3D v1(19.11, -32.92, 71.2);
		CVector3D v2(14.23f, 11.7f, 12.05f);

		v2 -= v1;

		BOOST_TEST(v2.x == -4.88, tt::tolerance(0.01));
		BOOST_TEST(v2.y == 44.62, tt::tolerance(0.01));
		BOOST_TEST(v2.z == -59.15, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorMultOperator)
	{
		const CVector3D v1(-10, -15, -25);

		const auto v2 = v1 * 10;

		BOOST_TEST(v2.x == -100, tt::tolerance(0.01));
		BOOST_TEST(v2.y == -150, tt::tolerance(0.01));
		BOOST_TEST(v2.z == -250, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorMultEqualOperator)
	{
		CVector3D v1(-10, -15, -25);

		v1 *= 10;

		BOOST_TEST(v1.x == -100, tt::tolerance(0.01));
		BOOST_TEST(v1.y == -150, tt::tolerance(0.01));
		BOOST_TEST(v1.z == -250, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorDivOperator)
	{
		const CVector3D v1(-10, -15, -25);

		const auto v2 = v1 / 10;

		BOOST_TEST(v2.x == -1, tt::tolerance(0.01));
		BOOST_TEST(v2.y == -1.5, tt::tolerance(0.01));
		BOOST_TEST(v2.z == -2.5, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorDivEqualOperator)
	{
		CVector3D v1(-10, -15, -25);

		v1 /= 10;

		BOOST_TEST(v1.x == -1, tt::tolerance(0.01));
		BOOST_TEST(v1.y == -1.5, tt::tolerance(0.01));
		BOOST_TEST(v1.z == -2.5, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorDivOperatorThrowsWhenScalarIsZero)
	{
		const CVector3D v1(-10, -15, -25);

		BOOST_CHECK_THROW(v1 / 0, std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(VectorDivEqualOperatorThrowsWhenScalarIsZero)
	{
		CVector3D v1(-10, -15, -25);

		BOOST_CHECK_THROW(v1 /= 0, std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(VectorIsEqualOperator)
	{
		const CVector3D v1(-10.123, -15.92, -25.001);
		const CVector3D v2(-10.123, -15.92, -25.001);

		BOOST_CHECK(v1 == v2);
	}

	BOOST_AUTO_TEST_CASE(VectorNotEqualOperator)
	{
		const CVector3D v1(-10, -15, -25);
		const CVector3D v2(-10.123, -15.92, -25.001);

		BOOST_CHECK(v1 != v2);
	}

	BOOST_AUTO_TEST_CASE(VectorReturnsLength)
	{
		const CVector3D v1(-10, -15, -25);
		BOOST_TEST(v1.GetLength() == 30.82f, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorReturnsLengthFloatingNumber)
	{
		const CVector3D v1(-10.123, -15.92, -25.001);
		BOOST_TEST(v1.GetLength() == 31.32f, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorNormalization)
	{
		CVector3D v1(-10, -15, -25);

		v1.Normalize();

		BOOST_TEST(v1.x == -0.324, tt::tolerance(0.01));
		BOOST_TEST(v1.y == -0.486, tt::tolerance(0.01));
		BOOST_TEST(v1.z == -0.811, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(NormalizationOfNullVector)
	{
		CVector3D v1(0, 0, 0);

		v1.Normalize();

		BOOST_TEST(v1.x == 0, tt::tolerance(0.01));
		BOOST_TEST(v1.y == 0, tt::tolerance(0.01));
		BOOST_TEST(v1.z == 0, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorCrossFunction)
	{
		const CVector3D v1(-10, -15, -25);
		const CVector3D v2(14, 2, 1);

		const CVector3D cross = CrossProduct(v1, v2);

		BOOST_TEST(cross.x == 35, tt::tolerance(0.01));
		BOOST_TEST(cross.y == -340, tt::tolerance(0.01));
		BOOST_TEST(cross.z == 190, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorDotFunction)
	{
		const CVector3D v1(-10, -15, -25);
		const CVector3D v2(14, 2, 1);

		const auto dot = DotProduct(v1, v2);

		BOOST_TEST(dot == -195, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorNormalizeFunction)
	{
		CVector3D v1(-10, -15, -25);

		const auto norm = Normalize(v1);

		v1.Normalize();

		BOOST_CHECK(v1 == norm);
	}

	BOOST_AUTO_TEST_CASE(VectorReadStreamOperator)
	{
		CVector3D v;

		std::istringstream stream("0.123 5.12 9.20");

		stream >> v;

		BOOST_TEST(v.x == 0.123, tt::tolerance(0.01));
		BOOST_TEST(v.y == 5.12, tt::tolerance(0.01));
		BOOST_TEST(v.z == 9.20, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(VectorWriteStreamOperator)
	{
		const std::string result = "10 5 1";
		const CVector3D v(10, 5, 1);

		std::ostringstream stream;
		stream << v;

		BOOST_CHECK(stream.str() == result);
	}

BOOST_AUTO_TEST_SUITE_END()