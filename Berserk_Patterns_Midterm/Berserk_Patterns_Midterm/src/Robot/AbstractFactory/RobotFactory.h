#pragma once

#include "iRobotFactory.h"

//A derived class that is used to create instance of robot objects of type robotbase
class RobotFactory : public iRobotFactory
{
public:
	RobotBase* CreateRobot() override;
};

