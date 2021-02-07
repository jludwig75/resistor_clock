#include "clockapp.h"


#define TZ_ADJUST   7


void ClockApp::setup()
{
    m_display.setup();
}

void ClockApp::setMessage(const String& message)
{
    m_display.setMessage(message);
}

void ClockApp::start()
{
    m_clock.start();
    m_display.start();
}


void ClockApp::on_loop()
{
    m_clock.on_loop();

    auto time = m_clock.time();
    time.hour -= TZ_ADJUST;
    if (time.hour < 0)
    {
        time.hour += 24;
    }
    m_display.setTime(time);
}
