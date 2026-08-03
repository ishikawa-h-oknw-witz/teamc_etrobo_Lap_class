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
<<<<<<< HEAD
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 600}, // 区間1
    { 80, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 300}, // 区間2
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 300}, // 区間3
    { 80, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 400}, // 区間4
    {100, 0.5, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 400}, // 区間5
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 500}, // 区間6
    { 70, 0.5, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 2300}, // 区間7
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 1000}  // 区間8
=======
    { 40, 0.6, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace,  600}, // 区間1
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace,  900}, // 区間2
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 1400}, // 区間3
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 1700}, // 区間4
    {100, 0.5, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 2100}, // 区間5
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 2600}, // 区間6
    { 70, 0.5, 0.0, 0.4, JudgeType::Distance, RunnerType::LineTrace, 4400}, // 区間7
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, RunnerType::LineTrace, 5400}  // 区間8
>>>>>>> 3a0d35c97e8724e698416aa2a7978cc75d99ec30
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
        tslp_tsk(10 * 1000);
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