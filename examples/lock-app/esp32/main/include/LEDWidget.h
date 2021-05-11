#pragma once
#include <stdint.h>
#include "driver/gpio.h"

#ifndef LED_WIDGET_H
#define LED_WIDGET_H

class LEDWidget
{
public:
    void        Init(gpio_num_t ledNum);
    void        Set(bool state);
    void        Invert(void);
    void        Blink(uint32_t changeRateMS);
    void        Blink(uint32_t onTimeMS, uint32_t offTimeMS);
    void        Animate();

private:
    int64_t  mLastChangeTimeUS;
    uint32_t mBlinkOnTimeMS;
    uint32_t mBlinkOffTimeMS;
    gpio_num_t      mGPIONum;
    bool     mState;

    void DoSet(bool state);
};

#endif // LED_WIDGET_H
