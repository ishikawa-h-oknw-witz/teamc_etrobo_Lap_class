#pragma once
        
#include "LineTraceRunner.h"
#include "GyroTraceRunner.h"
#include "PIDCalculator.h"
#include "TrapezoidCalculator.h"
#include "IEventDetector.h"
#include "TargetDistanceDetector.h"
#include "DistanceCalculator.h"

class SceneManager
{
public:
    SceneManager(
        LineTraceRunner& lineTraceRunner,
        GyroTraceRunner& gyroTraceRunner,
        PIDCalculator& pidCalculator,
        TrapezoidCalculator& trapezoidCalculator,
        TargetDistanceDetector& targetDistanceDetector,
        DistanceCalculator& distanceCalculator);

    int getSceneID();
    void setSceneID(int sceneid);
    bool SceneExecute();
    void setParameter(int sceneId);

private:
    LineTraceRunner& mLineTraceRunner;
    GyroTraceRunner& mGyroTraceRunner;
    PIDCalculator& mPIDCalculator;
    TrapezoidCalculator& mTrapezoidCalculator;
    TargetDistanceDetector& mTargetDistanceDetector;
    DistanceCalculator& mDistanceCalculator;

    int mSceneId;
    IEventDetector* mEventDetector;
};