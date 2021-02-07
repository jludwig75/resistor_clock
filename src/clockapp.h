#pragma once

#include "clock.h"
#include "clockdisplay.h"


class ClockApp
{
public:
    void setup();
    void setMessage(const String& message);
    void start();
    void on_loop();
private:
    Clock m_clock;
    ClockDisplay m_display;
};