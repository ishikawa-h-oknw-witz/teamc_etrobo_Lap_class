#ifndef GYRO_TRACE_RUNNER_H
#define GYRO_TRACE_RUNNER_H

#include "Motor.h"
#include "DistanceCalculator.h"
#include "PIDCalculator.h"
#include "TrapezoidCalculator.h"
#include "IMU.h"
#include "Clock.h"

using namespace spikeapi;

class GyroTraceRunner
{
public:
    GyroTraceRunner(
            Motor& leftMotor,
            Motor& rightMotor,
            DistanceCalculator& distanceCalculator,
            PIDCalculator& pidCalculate,
            TrapezoidCalculator& trapezoidCalculate);

    //前後退走行
    void move(bool direction, int distance);

    //旋回
    void turn(float targetHeading);

private:
    Motor& mLeftMotor;
    Motor& mRightMotor;
    DistanceCalculator& mDistanceCalculator;
    PIDCalculator& mPIDCalculator;
    TrapezoidCalculator& mTrapezoidCalculator;
    IMU mImu;
    Clock mClock;
    int mBaseSpeed;
};
#endif