#pragma once

#include "../RobotBase.h"

class iRobotFactory
{
public:
	virtual RobotBase* CreateRobot() = 0;
};