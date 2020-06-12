#include "CalcuatorIdentifier.h"

CalcuatorIdentifier::CalcuatorIdentifier(IdentifierType type)
	: m_type(type)
{
}

CalcuatorIdentifier::~CalcuatorIdentifier()
{
}

IdentifierType CalcuatorIdentifier::GetType()
{
	return m_type;
}
