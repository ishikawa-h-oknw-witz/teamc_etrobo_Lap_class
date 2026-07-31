#pragma once

class IEventDetector
{
public:
    virtual ~IEventDetector() = default;

    virtual bool judge() = 0;
};