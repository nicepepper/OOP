#pragma once
#include "IdentifierType.h"

class CalcuatorIdentifier
{
public:
	CalcuatorIdentifier(IdentifierType type);
	virtual ~CalcuatorIdentifier();
	virtual IdentifierType GetType();
	
private:
	IdentifierType m_type;
};
