// MIT License

// Copyright (c) 2021 Jonathan Ludwig

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
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
