
#include <iostream>
#include "PositionServoMotor.h"

int main(void)
{
    PositionServoMotor refPositionServoMotor ;
//    refPositionServoMotor.PositionControl();
    refPositionServoMotor.PositionControlAngle();

    std::cout << "This is new Code" << std::endl;        
    return 0;
}

