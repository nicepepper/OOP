// Car-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../Car/car.h"

#define BOOST_TEST_MODULE CarTests
#include <boost/test/unit_test.hpp>

void CompareCarParametersWithExpected(const Car& car, const int gear, const int speed, const bool engine, const std::string& moveState)
{
	BOOST_CHECK_EQUAL(car.GetGear(), gear);
	BOOST_CHECK_EQUAL(car.GetSpeed(), speed);
	BOOST_CHECK_EQUAL(car.DoesEngineTurnedOn(), engine);
	BOOST_CHECK_EQUAL(car.GetMoveState(), moveState);
}

BOOST_AUTO_TEST_SUITE(CarClassTests)

	BOOST_AUTO_TEST_CASE(turn_on_and_off)
	{
		Car car;
		BOOST_CHECK(car.SetGear(1) == false);
		BOOST_CHECK(car.SetSpeed(10) == false);
		CompareCarParametersWithExpected(car, 0, 0, false, "STOP");
		BOOST_CHECK(car.TurnOnEngine());
		CompareCarParametersWithExpected(car, 0, 0, true, "STOP");
		BOOST_CHECK(car.TurnOffEngine());
		CompareCarParametersWithExpected(car, 0, 0, false, "STOP");
	}

	BOOST_AUTO_TEST_CASE(check_initial_state)
	{
		Car car;
		CompareCarParametersWithExpected(car, 0, 0, false, "STOP");
	}

	BOOST_AUTO_TEST_CASE(car_cannot_set_backward_gear_when_dont_stop)
	{
		Car car;
		BOOST_CHECK(car.TurnOnEngine());

		BOOST_CHECK(car.SetGear(-1));
		BOOST_CHECK(car.SetSpeed(10));
		BOOST_CHECK(car.SetGear(0));
		BOOST_CHECK(car.SetGear(-1) == false);

		CompareCarParametersWithExpected(car, 0, 10, true, "BACKWARD");
	}

	BOOST_AUTO_TEST_CASE(car_can_set_one_zero_backward_gears_when_stop)
	{
		Car car;
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.SetGear(1));
		CompareCarParametersWithExpected(car, 1, 0, true, "STOP");

		BOOST_CHECK(car.SetGear(0));
		CompareCarParametersWithExpected(car, 0, 0, true, "STOP");

		BOOST_CHECK(car.SetGear(-1));
		CompareCarParametersWithExpected(car, -1, 0, true, "STOP");

		BOOST_CHECK(car.SetGear(0));
		CompareCarParametersWithExpected(car, 0, 0, true, "STOP");

		BOOST_CHECK(car.TurnOffEngine());
		CompareCarParametersWithExpected(car, 0, 0, false, "STOP");
	}

	BOOST_AUTO_TEST_CASE(check_car_move_states)
	{
		Car car;

		BOOST_CHECK(car.TurnOnEngine());
		CompareCarParametersWithExpected(car, 0, 0, true, "STOP");

		BOOST_CHECK(car.SetGear(-1));
		CompareCarParametersWithExpected(car, -1, 0, true, "STOP");

		BOOST_CHECK(car.SetSpeed(20));
		CompareCarParametersWithExpected(car, -1, 20, true, "BACKWARD");

		BOOST_CHECK(car.SetSpeed(0));
		CompareCarParametersWithExpected(car, -1, 0, true, "STOP");

		BOOST_CHECK(car.SetGear(1));
		CompareCarParametersWithExpected(car, 1, 0, true, "STOP");

		BOOST_CHECK(car.SetSpeed(20));
		CompareCarParametersWithExpected(car, 1, 20, true, "FORWARD");
	}

	BOOST_AUTO_TEST_CASE(car_cant_set_forward_gear_when_car_moves_backward)
	{
		Car car;

		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.SetGear(-1));
		BOOST_CHECK(car.SetSpeed(20));
		BOOST_CHECK(car.SetGear(1) == false);

		CompareCarParametersWithExpected(car, -1, 20, true, "BACKWARD");
	}

	BOOST_AUTO_TEST_CASE(turnon_and_turnoff)
	{
		Car car;

		BOOST_CHECK(car.TurnOnEngine());
		CompareCarParametersWithExpected(car, 0, 0, true, "STOP");

		BOOST_CHECK(car.TurnOffEngine());
		CompareCarParametersWithExpected(car, 0, 0, false, "STOP");
	}

	BOOST_AUTO_TEST_CASE(car_cannot_turnoff_when_works)
	{
		Car car;

		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.SetGear(-1));
		BOOST_CHECK(car.SetSpeed(20));
		BOOST_CHECK(car.SetSpeed(0));
		BOOST_CHECK(car.TurnOffEngine() == false);

		CompareCarParametersWithExpected(car, -1, 0, true, "STOP");
	}

	BOOST_AUTO_TEST_CASE(car_can_set_gears_and_update_speed_when_dont_work)
	{
		Car car;

		BOOST_CHECK(car.SetSpeed(0));
		BOOST_CHECK(car.SetGear(0));

		BOOST_CHECK(car.SetGear(-1) == false);
		BOOST_CHECK(car.SetSpeed(20) == false);
		BOOST_CHECK(car.SetGear(1) == false);

		CompareCarParametersWithExpected(car, 0, 0, false, "STOP");
	}

	BOOST_AUTO_TEST_CASE(car_cannot_set_speed_when_moves_backward_and_have_zero_gear)
	{
		Car car;
		BOOST_CHECK(car.TurnOnEngine());

		BOOST_CHECK(car.SetGear(-1));
		CompareCarParametersWithExpected(car, -1, 0, true, "STOP");

		BOOST_CHECK(car.SetSpeed(10));
		BOOST_CHECK(car.SetGear(0));

		BOOST_CHECK(car.SetSpeed(15) == false);
		BOOST_CHECK(car.SetGear(-1) == false);

		CompareCarParametersWithExpected(car, 0, 10, true, "BACKWARD");

		BOOST_CHECK(car.GetGear() == 0);
		BOOST_CHECK(car.SetSpeed(0));

		BOOST_CHECK(car.TurnOffEngine());
	}

	BOOST_AUTO_TEST_CASE(accelerate_car_and_then_slow_it)
	{
		Car car;
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.SetGear(1));
		BOOST_CHECK(car.SetSpeed(20));
		BOOST_CHECK(car.SetGear(2));
		BOOST_CHECK(car.SetSpeed(30));
		BOOST_CHECK(car.SetGear(3));
		BOOST_CHECK(car.SetSpeed(50));
		BOOST_CHECK(car.SetGear(4));
		BOOST_CHECK(car.SetSpeed(70));
		BOOST_CHECK(car.SetGear(5));
		BOOST_CHECK(car.SetSpeed(150));
		CompareCarParametersWithExpected(car, 5, 150, true, "FORWARD");

		BOOST_CHECK(car.SetSpeed(70));
		BOOST_CHECK(car.SetGear(4));
		BOOST_CHECK(car.SetSpeed(60));
		BOOST_CHECK(car.SetGear(3));
		BOOST_CHECK(car.SetSpeed(60));
		BOOST_CHECK(car.SetGear(0));
		BOOST_CHECK(car.SetSpeed(0));
		CompareCarParametersWithExpected(car, 0, 0, true, "STOP");

		BOOST_CHECK(car.TurnOffEngine());
	}

BOOST_AUTO_TEST_SUITE_END()