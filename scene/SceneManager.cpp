#include "SceneManager.h"
#include "Logger.h"

enum class JudgeType
{
    Distance,
    Angle,
    Color
};

enum class RunnerType
{
    LineTrace,
    GyroTrace_move,
    GyroTrace_turn
};

struct Section
{
    int speed;
    float kp;
    float ki;
    float kd;

    JudgeType judgeType;
    RunnerType runnerType;

    int targetDistance;
    //float targetAngle;
    //Color targetColor;
};

// {速度, Kp, Ki, Kd, 判定種類, 走行種類, 目標距離, 目標角度, 目標色}
Section sections[] = {
    {100, 0.2, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 500}, // 直線1
    { 80, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 150}, // カーブ1-1
    { 70, 0.5, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 100}, // カーブ1-2
    { 80, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 150}, // カーブ1-3
    {100, 0.3, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 400}, // 直線2
    { 80, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 150}, // カーブ2-1
    { 70, 0.5, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 100}, // カーブ2-2
    { 80, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 100}, // カーブ2-3
    {100, 0.3, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 300}, // 直線3
    { 60, 0.5, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 400}, // カーブ3
    {100, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 900}, // 蛇行1
    { 80, 0.5, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 900}, // 蛇行1
    {100, 0.4, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 1500}  // 直線4
};

//コンストラクタ
SceneManager::SceneManager(
    LineTraceRunner& lineTraceRunner,
    GyroTraceRunner& gyroTraceRunner,
    PIDCalculator& pidCalculator,
    TrapezoidCalculator& trapezoidCalculator,
    TargetDistanceDetector& targetDistanceDetector,
    DistanceCalculator& distanceCalculator)
    : mLineTraceRunner(lineTraceRunner),
      mGyroTraceRunner(gyroTraceRunner),
      mPIDCalculator(pidCalculator),
      mTrapezoidCalculator(trapezoidCalculator),
      mTargetDistanceDetector(targetDistanceDetector),
      mDistanceCalculator(distanceCalculator),
      mSceneId(0),
      mEventDetector(nullptr)
{
}

int SceneManager::getSceneID()
{
    return mSceneId;
}

void SceneManager::setSceneID(int sceneId)
{
    mSceneId = sceneId;
}

bool SceneManager::SceneExecute()
{
    setParameter(mSceneId);
    const Section& section = sections[mSceneId];

    mDistanceCalculator.reset();
    
    while(!mEventDetector->judge())
    {
        // 走行実行
        switch (section.runnerType)
        {
        case RunnerType::LineTrace:
            mLineTraceRunner.run();
            break;

        /*
        case RunnerType::GyroTrace_move:
            mGyroTraceRunner.move();
            break;

        case RunnerType::GyroTrace_turn:
            mGyroTraceRunner.turn();
            break;
        */
        default:
            break;
        }
        //tslp_tsk(10 * 1000);
    }

    // シーン終了
    return true;
}

void SceneManager::setParameter(int sceneId)
{
    const Section& section = sections[sceneId];

    // ライントレース
    mLineTraceRunner.setBaseSpeed(section.speed);

    // ジャイロトレース(ラリーで必要)

    // PID
    mPIDCalculator.setGain(
        section.kp,
        section.ki,
        section.kd);

    switch (section.judgeType)
    {
    case JudgeType::Distance:
        // シーン終了距離
        mTargetDistanceDetector.setTargetDistance(section.targetDistance);
        mEventDetector = &mTargetDistanceDetector;
        break;
        
    default:
        break;
    }
    // 台形制御(ラリーで必要)
}