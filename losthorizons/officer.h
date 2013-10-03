#ifndef _OFFICER_H_
#define _OFFICER_H_

#include <string>

enum E_OFFICER_TYPE
{
	OFFICER_HELMSMAN,
	OFFICER_FIRECONTROL,
	OFFICER_ENGINEERING,
	OFFICER_NAVIGATION
};

//the player is allowed to hire officers, with each officer having different roles
class Officer
{
public:
	Officer(const std::wstring &name, const E_OFFICER_TYPE type);
	~Officer();

protected:
	std::wstring name;
	unsigned currentExperience;
	unsigned experienceToLevel;
	E_OFFICER_TYPE type;
};

#endif
