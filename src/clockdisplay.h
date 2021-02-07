#pragma once

#include <stdint.h>
#include <WString.h>
#include <TFT_eSPI.h>

#include "clock.h"


class ClockDisplay
{
public:
    ClockDisplay();
    void setup();
    void setMessage(const String& message);
    void start();
    void setTime(const Clock::SimpleTime& time);
private:
    TFT_eSPI m_tft;
    Clock::SimpleTime m_lastDisplayTime;
};