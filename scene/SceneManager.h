#pragma once

class SceneManager
{
public:
    SceneManager(
        LineTraceRunner& linetraceRunner,
        GyroTraceRunner& gyrotraceRunner,
        PIDCalculate& pidCalculate,
        TrapezoidCalculator& trapezoidCalculator);

    void setParameter(int scene_id);

private:
    LineTraceRunner& mLineTraceRunner;
    GyroTraceRunner& mGyroTraceRunner;
    PIDCalculate& mPIDCalculate;
    TrapezoidCalculator& mTrapezoidCalculator;
};