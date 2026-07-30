#pragma once

class ISceneJudge
{
public:
    virtual ~ISceneJudge() = default;

    virtual bool judge() = 0;
};