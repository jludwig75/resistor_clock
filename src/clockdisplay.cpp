#include "clockdisplay.h"

#include <SPI.h>


#define BACK_GROUND_COLOR   0x18E3

#define WIDTH   20
#define MARGIN  6
#define CELL    (2 * MARGIN + WIDTH)


ClockDisplay::ClockDisplay()
    :
    m_lastDisplayTime{}
{
}

void ClockDisplay::setup()
{
    Serial.println("Initializing display...");
    m_tft.init();
    m_tft.setRotation(3);
}

void forEachLine(const String& message, std::function<void(const String&)> onLine)
{
    unsigned int start = 0;
    while (start < message.length())
    {
        auto nextNewLine = message.indexOf('\n', start);
        if (nextNewLine == -1)
        {
            onLine(message.substring(start));
            break;
        }
        else
        {
            onLine(message.substring(start, nextNewLine));
            start = nextNewLine + 1;
        }
    }
}

void ClockDisplay::setMessage(const String& message)
{
    m_tft.fillScreen(TFT_BLACK);
    m_tft.setTextDatum(TL_DATUM);
    m_tft.setTextColor(TFT_WHITE, TFT_BLACK);      // White characters on black background
    int32_t lineNumber = 0;
    forEachLine(message, [this, &lineNumber](const String& line) {
        m_tft.drawString(line, 20, 20 + lineNumber * 25, 2);
        lineNumber++;
    });
}

void ClockDisplay::start()
{
    Serial.println("Setting up clock display...");
    m_tft.fillScreen(BACK_GROUND_COLOR);
    int32_t x = MARGIN;
    // m_tft.fillRect(x     , 10, WIDTH, 115, TFT_BROWN);
    x += CELL;
    // m_tft.fillRect(x, 10, WIDTH, 115, TFT_RED);

    x += CELL - 4;
    m_tft.fillRect(x + 4, 53, WIDTH - 8, 10, TFT_DARKGREY);
    m_tft.fillRect(x + 4, 72, WIDTH - 8, 10, TFT_DARKGREY);

    x += CELL - 4;
    // m_tft.fillRect(x, 10, WIDTH, 115, TFT_GREEN);
    x += CELL;
    // m_tft.fillRect(x, 10, WIDTH, 115, TFT_ORANGE);

    x += CELL - 4;
    m_tft.fillRect(x + 4, 53, WIDTH - 8, 10, TFT_DARKGREY);
    m_tft.fillRect(x + 4, 72, WIDTH - 8, 10, TFT_DARKGREY);

    x += CELL - 4;
    // m_tft.fillRect(x, 10, WIDTH, 115, TFT_YELLOW);
    x += CELL;
    // m_tft.fillRect(x, 10, WIDTH, 115, TFT_PURPLE);

    Serial.println("Setup up clock display");
}

namespace
{

int32_t color_map[10] = { TFT_BLACK, TFT_BROWN, TFT_RED, TFT_ORANGE, TFT_YELLOW, TFT_GREEN, TFT_BLUE, TFT_PURPLE, TFT_DARKGREY, TFT_WHITE } ;

}

void ClockDisplay::setTime(const Clock::SimpleTime& time)
{
    if (time != m_lastDisplayTime)
    {
        int32_t x = MARGIN;
        m_tft.fillRect(x     , 10, WIDTH, 115, color_map[time.hour / 10]);
        x += CELL;
        m_tft.fillRect(x, 10, WIDTH, 115, color_map[time.hour % 10]);

        x += CELL - 4;
        // m_tft.fillRect(x + 4, 53, WIDTH - 8, 10, TFT_DARKGREY);
        // m_tft.fillRect(x + 4, 72, WIDTH - 8, 10, TFT_DARKGREY);

        x += CELL - 4;
        m_tft.fillRect(x, 10, WIDTH, 115, color_map[time.minute / 10]);
        x += CELL;
        m_tft.fillRect(x, 10, WIDTH, 115, color_map[time.minute % 10]);

        x += CELL - 4;
        // m_tft.fillRect(x + 4, 53, WIDTH - 8, 10, TFT_DARKGREY);
        // m_tft.fillRect(x + 4, 72, WIDTH - 8, 10, TFT_DARKGREY);

        x += CELL - 4;
        m_tft.fillRect(x, 10, WIDTH, 115, color_map[time.second / 10]);
        x += CELL;
        m_tft.fillRect(x, 10, WIDTH, 115, color_map[time.second % 10]);

        m_lastDisplayTime = time;
    }
}
