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
