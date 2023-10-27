#pragma once

#include "../RobotBase.h"

//A interface which can be inherited to create a base of robot class
class iRobotFactory
{
public:
	virtual RobotBase* CreateRobot() = 0;
};