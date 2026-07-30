#ifndef GYRO_TRACE_RUNNER_H
#define GYRO_TRACE_RUNNER_H

#include "Motor.h"
#include "DistanceCalculator.h"
#include "PIDCalculate.h"
#include "TrapezoidCalculate.h"
#include "IMU.h"
#include "Clock.h"

using namespace spikeapi;

class ScenarioRunner
{
public:
    ScenarioRunner(
            Motor& leftMotor,
            Motor& rightMotor,
            DistanceCalculator& distanceCalculator,
            PIDCalculate& pidCalculate,
            TrapezoidCalculate& trapezoidCalculate);

    //前後退走行
    void move(bool direction, int distance);

    //旋回
    void turn(float targetHeading);

private:
    Motor& mLeftMotor;
    Motor& mRightMotor;
    DistanceCalculator& mDistanceCalculator;
    PIDCalculate& mPIDCalculate;
    TrapezoidCalculate& mTrapezoidCalculate;
    IMU mImu;
    Clock mClock;
    int mBaseSpeed;
};
#endif