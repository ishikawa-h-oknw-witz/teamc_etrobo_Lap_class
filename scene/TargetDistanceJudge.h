#pragma once

#include "ISceneJudge.h"
#include "DistanceCalculator.h"

class TargetDistanceJudge : public ISceneJudge
{
public:
    TargetDistanceJudge(DistanceCalculator& calculator);

    void setTargetDistance(int distance);

    bool judge() override;

private:
    DistanceCalculator& mDistanceCalculator;
    int mTargetDistance;
};