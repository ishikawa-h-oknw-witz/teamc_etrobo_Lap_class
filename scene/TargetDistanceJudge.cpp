#include "TargetDistanceJudge.h"

TargetDistanceJudge::TargetDistanceJudge(
    DistanceCalculator& calculator)
    : mDistanceCalculator(calculator),
      mTargetDistance(0)
{
}

void TargetDistanceJudge::setTargetDistance(int distance)
{
    mTargetDistance = distance;
}

bool TargetDistanceJudge::judge()
{
    return mDistanceCalculator.getDistance() >= mTargetDistance;
}