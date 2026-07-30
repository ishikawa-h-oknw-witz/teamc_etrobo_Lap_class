#pragma once

class SceneParameter
{
public:
    SceneParameter(
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