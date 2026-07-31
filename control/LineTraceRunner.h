#ifndef LINE_TRACE_RUNNNER_H
#define LINE_TRACE_RUNNNER_H

#include "ColorSensor.h"
#include "PIDCalculator.h"
#include "Motor.h"
#include "kernel.h"

using namespace spikeapi;

class LineTraceRunner
{
public:
    LineTraceRunner(
        Motor& leftMotor,
        Motor& rightMotor,
        ColorSensor& colorSensor,
        PIDCalculator& pidController);

    void setBaseSpeed(int speed);

    void run();

private:
    Motor& mLeftMotor;

    Motor& mRightMotor;

    ColorSensor& mColorSensor;

    PIDCalculator& mPIDCalculator;

    int mTargetReflection;

    int mBaseSpeed;
};

#endif