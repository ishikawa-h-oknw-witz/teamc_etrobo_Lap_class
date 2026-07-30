#include "ArmController.h"

//コンストラクタ
ArmController::ArmController(
    Motor& ArmMotor)
    : mArmMotor(ArmMotor)
{
}

void ArmController::setMaxAngle(int maxangle)
{
    if( maxangle > 90 )
    {
        mMaxAngle = 90;
    }
    else
    {
        mMaxAngle = maxangle;
    }
}

void ArmController::moveArm(int angle)
{

}

void ArmController::moveArmDown()
{

}

void ArmController::moveArmUp()
{

}