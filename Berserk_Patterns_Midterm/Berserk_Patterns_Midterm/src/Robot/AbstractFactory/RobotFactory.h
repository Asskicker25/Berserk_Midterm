#pragma once

#include "iRobotFactory.h"

class RobotFactory : public iRobotFactory
{
public:
	RobotBase* CreateRobot() override;
};

