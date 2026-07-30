#pragma once

#include "ISceneJudge.h"
#include "DistanceDetector.h"

class TargetDistanceJudge : public ISceneJudge
{
public:
    TargetDistanceJudge(DistanceDetector& distancedetector);

    void setTargetDistance(int distance);

    bool judge() override;

private:
    DistanceDetector& mDistanceDetector;
    int mTargetDistance;
};