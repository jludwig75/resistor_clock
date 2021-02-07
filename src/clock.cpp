#include "clock.h"


Clock::Clock()
    :
    m_ntp(m_udp)
{
}

void Clock::start()
{
    Serial.println("Setting up clock display...");
    m_ntp.begin();
    Serial.println("Setup up clock display");
}

void Clock::on_loop()
{
    m_ntp.update();
}


Clock::SimpleTime Clock::time() const
{
    // ARGH!! If you're going to write a C or C++ library, learn enough
    // C or C++ to understand const correctness and use it!
    auto hour = static_cast<int8_t>(const_cast<Clock*>(this)->m_ntp.getHours());
    auto minute = static_cast<int8_t>(const_cast<Clock*>(this)->m_ntp.getMinutes());
    auto second = static_cast<int8_t>(const_cast<Clock*>(this)->m_ntp.getSeconds());
    return { hour, minute, second };
}
