#include "TrapezoidCalculator.h"

TrapezoidCalculator::TrapezoidCalculator()
    : mStartSpeed(30),
      mMaxSpeed(100),
      mEndSpeed(30),
      mAccelDistance(100.0f),
      mDecelDistance(200.0f)
{
}

void TrapezoidCalculator::setParameter(
    int startSpeed,
    int maxSpeed,
    int endSpeed,
    float accelDistance,
    float decelDistance)
{
    mStartSpeed = startSpeed;
    mMaxSpeed = maxSpeed;
    mEndSpeed = endSpeed;
    mAccelDistance = accelDistance;
    mDecelDistance = decelDistance;
}

int TrapezoidCalculator::getSpeed(
    float currentDistance,
    float totalDistance)
{
    float remainingDistance = totalDistance - currentDistance;

    // 加速区間
    if (currentDistance < mAccelDistance)
    {
        return mStartSpeed +
            (mMaxSpeed - mStartSpeed)
            * currentDistance / mAccelDistance;
    }

    // 減速区間
    if (remainingDistance < mDecelDistance)
    {
        return mEndSpeed +
            (mMaxSpeed - mEndSpeed)
            * remainingDistance / mDecelDistance;
    }

    // 定速区間
    return mMaxSpeed;
}