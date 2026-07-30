#include "DistanceDetector.h"
#include <stdlib.h>

DistanceDetector::DistanceDetector(
    Motor& leftMotor,
    Motor& rightMotor)
    : mLeftMotor(leftMotor),
      mRightMotor(rightMotor)
{
}

void DistanceDetector::reset()
{
    mLeftMotor.resetCount();
    mRightMotor.resetCount();
}

float DistanceDetector::getDistance()
{
    int leftAngle =
        abs(mLeftMotor.getCount());

    int rightAngle =
        abs(mRightMotor.getCount());

    float averageAngle =
        (leftAngle + rightAngle) / 2.0f;

    float distance =
        averageAngle / 360.0f
        * 3.14159f
        * TIRE_DIAMETER;

    return distance;
}