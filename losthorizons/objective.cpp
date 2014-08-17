#include "stdafx.h"
#include "objective.h"
#include <iostream>


const int OBJECTIVE_CHECK_TIMER = 500;

Objective::Objective(const std::wstring &desciption, const vector3df& position) : 
	description(description), position(position), state(OBJECTIVE_STATE_INPROGRESS), timeKeeping(0)
{

}

Objective::Objective(const vector3df& position) : 
	description(L""), position(position), state(OBJECTIVE_STATE_INPROGRESS), timeKeeping(0)
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

const std::wstring& Objective::getDescription() const
{
	return description;
}


