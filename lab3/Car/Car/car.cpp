#include "Car.h"

Car::Car()
	: m_engineTurnedOn(false)
	, m_speed(0)
	, m_gear(0)
	, m_move(STOP)
{
}

bool Car::TurnOnEngine()
{
	if (m_engineTurnedOn)
	{
		return false;
	}
	m_engineTurnedOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	bool couldBeTurnedOff = ((m_gear == 0) && (m_speed == 0) && m_engineTurnedOn);
	if (couldBeTurnedOff)
	{
		m_engineTurnedOn = false;
		return true;
	}
	return false;
}

bool Car::SetGearIfParamsValid(int minSpeed, int maxSpeed, int gear, Move currentMove)
{
	bool areCarParamsValid = (currentMove == m_move) && (minSpeed <= m_speed) && (m_speed <= maxSpeed);

	if (areCarParamsValid)
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{
	if (!m_engineTurnedOn)
	{
		if (gear == 0)
		{
			m_gear = 0;
			return true;
		}
		return false;
	}

	switch (gear)
	{
	case -1:
		return SetGearIfParamsValid(0, 0, -1, STOP);
	case 0:
		m_gear = 0;
		return true;
	case 1:
		return SetGearIfParamsValid(1, 30, 1, FORWARD) || SetGearIfParamsValid(0, 0, 1, STOP);
	case 2:
		return SetGearIfParamsValid(20, 50, 2, FORWARD);
	case 3:
		return SetGearIfParamsValid(30, 60, 3, FORWARD);
	case 4:
		return SetGearIfParamsValid(40, 90, 4, FORWARD);
	case 5:
		return SetGearIfParamsValid(50, 150, 5, FORWARD);
	default:
		return false;
	}
}

bool Car::UpdateSpeedAndCarMoveIfSpeedInRange(int minSpeed, int maxSpeed, int speed, Move move)
{
	bool isSpeedInRange = (minSpeed <= speed) && (speed <= maxSpeed);
	if (isSpeedInRange)
	{
		m_speed = speed;
		m_move = move;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_engineTurnedOn)
	{
		if (speed == 0)
		{
			m_speed = 0;
			return true;
		}
		return false;
	}

	switch (m_gear)
	{
	case -1:
		return UpdateSpeedAndCarMoveIfSpeedInRange(1, 20, speed, BACKWARD) || UpdateSpeedAndCarMoveIfSpeedInRange(0, 0, speed, STOP);
	case 0:

		if (UpdateSpeedAndCarMoveIfSpeedInRange(0, 0, speed, STOP))
		{
			return true;
		}

		if (m_move == FORWARD)
		{
			return UpdateSpeedAndCarMoveIfSpeedInRange(1, m_speed, speed, FORWARD);
		}
		else
		{
			return UpdateSpeedAndCarMoveIfSpeedInRange(1, m_speed, speed, BACKWARD);
		}

	case 1:
		return UpdateSpeedAndCarMoveIfSpeedInRange(0, 0, speed, STOP) || UpdateSpeedAndCarMoveIfSpeedInRange(1, 30, speed, FORWARD);
	case 2:
		return UpdateSpeedAndCarMoveIfSpeedInRange(20, 50, speed, FORWARD);
	case 3:
		return UpdateSpeedAndCarMoveIfSpeedInRange(30, 60, speed, FORWARD);
	case 4:
		return UpdateSpeedAndCarMoveIfSpeedInRange(40, 90, speed, FORWARD);
	case 5:
		return UpdateSpeedAndCarMoveIfSpeedInRange(50, 150, speed, FORWARD);
	default:
		return false;
	}
}

bool Car::DoesEngineTurnedOn() const
{
	return m_engineTurnedOn;
}

int Car::GetGear() const
{
	return m_gear;
}

int Car::GetSpeed() const
{
	return m_speed;
}

std::string Car::GetMoveState() const
{
	switch (m_move)
	{
	case Car::STOP:
		return "STOP";
	case Car::BACKWARD:
		return "BACKWARD";
	case Car::FORWARD:
		return "FORWARD";
	default:
		return "UNDEFINED";
	}
}