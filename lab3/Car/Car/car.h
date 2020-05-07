#pragma once
#include <string>

class Car
{
public:
	Car();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	int GetGear() const;
	int GetSpeed() const;
	bool DoesEngineTurnedOn() const;
	std::string GetMoveState() const;

private:
	enum Move
	{
		STOP,
		BACKWARD,
		FORWARD
	};
	bool SetGearIfParamsValid(int minSpeed, int maxSpeed, int gear, Move currentMove);
	bool UpdateSpeedAndCarMoveIfSpeedInRange(int minSpeed, int maxSpeed, int speed, Move move);
	bool m_engineTurnedOn;
	int m_speed;
	int m_gear;
	Move m_move;
};
