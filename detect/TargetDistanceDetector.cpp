#include "TargetDistanceDetector.h"

TargetDistanceDetector::TargetDistanceDetector(
    DistanceCalculate& distanceCalculate)
    : mDistanceCalculate(distanceCalculate),
      mTargetDistance(0)
{
}

void TargetDistanceDetector::setTargetDistance(int distance)
{
    mTargetDistance = distance;
}

bool TargetDistanceDetector::judge()
{
    return mDistanceCalculate.getDistance() >= mTargetDistance;
}