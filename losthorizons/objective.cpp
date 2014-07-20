#include "stdafx.h"
#include "objective.h"
#include <iostream>

Objective::Objective(const std::wstring &desciption, const vector3df& position) : 
	description(description), position(position), state(OBJECTIVE_STATE_INPROGRESS)
{

}

Objective::Objective(const vector3df& position) : 
	description(L""), position(position), state(OBJECTIVE_STATE_INPROGRESS)
{
}

Objective::~Objective()
{
}

bool Objective::run()
{
	return false;
}

const vector3df& Objective::getPosition() const
{
	return position;
}

const E_OBJECTIVE_TYPE Objective::getObjectiveType() const
{
	return type;
}


