// Car.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "car.h"
#include <iostream>
#include <string>

void PrintCarInfo(const Car& car)
{
	std::cout << "______\nEngine: " << (car.DoesEngineTurnedOn() ? "on" : "off") << ";\n";
	std::cout << "Gear: " << car.GetGear() << ";\n";
	std::cout << "Speed: " << car.GetSpeed() << ";\n";
	std::cout << "Move: " << car.GetMoveState() << ";\n";
}

bool GetNumberFromCin(int& number)
{
	try
	{
		std::string num;
		std::cin >> num;
		number = std::stoi(num);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

void TurnEngineOn(Car& car)
{
	if (car.TurnOnEngine())
	{
		std::cout << "Engine turned on." << std::endl;
	}
	else
	{
		std::cout << "Engine has been already turned on." << std::endl;
	}
}

void TurnEngineOff(Car& car)
{
	if (car.TurnOffEngine())
	{
		std::cout << "Engine turned off" << std::endl;
	}
	else
	{
		std::cout << "Engine can not be switched off" << std::endl;
	}
}

void SetSpeed(Car& car)
{
	int num;
	if (!GetNumberFromCin(num))
	{
		std::cout << "Can not read number from that string." << std::endl;
	}
	if (car.SetSpeed(num))
	{
		std::cout << "Speed was set." << std::endl;
	}
	else
	{
		std::cout << "Can not set this speed." << std::endl;
	}
}

void SetGear(Car& car)
{
	int num;
	if (!GetNumberFromCin(num))
	{
		std::cout << "Can not read number from that string." << std::endl;
	}
	if (car.SetGear(num))
	{
		std::cout << "Get was set." << std::endl;
	}
	else
	{
		std::cout << "Can not set this gear." << std::endl;
	}
}
int main()
{
	Car car;
	std::string inStr;
	while (std::cin >> inStr)
	{
		if (inStr == "Info")
		{
			PrintCarInfo(car);
			continue;
		}
		if (inStr == "EngineOn")
		{
			TurnEngineOn(car);
			continue;
		}
		if (inStr == "EngineOff")
		{
			TurnEngineOff(car);
			continue;
		}
		if (inStr == "SetGear")
		{
			SetGear(car);
			continue;
		}
		if (inStr == "SetSpeed")
		{
			SetSpeed(car);
			continue;
		}
		if (inStr == "exit")
		{
			break;
		}
		std::cout << "Unknown command.\n" 
			      << "Use the commands: Info, EngineOn, EngineOff, SetGear, SetSpeed, exit." << std::endl;
	}
	return 0;
}
