#pragma once

#include "AudibleAlarm.h"


class MockAudibleAlarm : public AudibleAlarm
{
public:
    virtual void sound() { alarmed = true; }
    virtual void silence() { alarmed = false; }

public:
    bool alarmed = false;
};
