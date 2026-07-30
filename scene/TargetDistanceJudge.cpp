#include "TargetDistanceJudge.h"

TargetDistanceJudge::TargetDistanceJudge(
    DistanceDetector& distancedetector)
    : mDistanceDetector(distancedetector),
      mTargetDistance(0)
{
}

void TargetDistanceJudge::setTargetDistance(int distance)
{
    mTargetDistance = distance;
}

bool TargetDistanceJudge::judge()
{
    return mDistanceDetector.getDistance() >= mTargetDistance;
}