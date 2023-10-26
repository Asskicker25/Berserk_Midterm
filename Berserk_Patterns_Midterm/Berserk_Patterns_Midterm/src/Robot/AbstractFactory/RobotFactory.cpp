#include "RobotFactory.h"
#include "../Robot.h"

RobotBase* RobotFactory::CreateRobot()
{
	return new Robot();
}
