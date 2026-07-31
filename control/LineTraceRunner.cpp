#include "LineTraceRunner.h"

// コンストラクタ
LineTraceRunner::LineTraceRunner(
    Motor& leftMotor,
    Motor& rightMotor,
    ColorSensor& colorSensor,
    PIDCalculator& pidCalculate)
    : mLeftMotor(leftMotor),
      mRightMotor(rightMotor),
      mColorSensor(colorSensor),
      mPIDCalculator(pidCalculate),
      mTargetReflection(50),
      mBaseSpeed(60)
{
}

void LineTraceRunner::setBaseSpeed(int speed)
{
    mBaseSpeed = speed;
}

void LineTraceRunner::run()
{
    int turn = 0;

    // 反射光取得
    int reflection =
        mColorSensor.getReflection();

    // 偏差計算
    int error =
        mTargetReflection - reflection;

    // PID制御依頼
    turn = mPIDCalculator.calculate(error);

    // モータ出力
    mLeftMotor.setPower(
        mBaseSpeed - turn);
 
    mRightMotor.setPower(
        mBaseSpeed + turn);

    tslp_tsk(10*1000);   // 約10ms周期
}