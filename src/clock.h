#pragma once

#include <stdint.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


class Clock
{
public:
    struct SimpleTime
    {
        int8_t hour;
        int8_t minute;
        int8_t second;
        bool operator!=(const SimpleTime& other) const
        {
            return other.hour != hour || other.minute == minute || other.second != second;
        }
    };
    Clock();
    void start();
    void on_loop();
    SimpleTime time() const;
private:
    WiFiUDP m_udp;
    NTPClient m_ntp;
};