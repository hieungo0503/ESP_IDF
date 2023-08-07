#ifndef BTN_DEBOUNCE_H
#define BTN_DEBOUNCE_H

#include "esp_timer.h"
#include "driver/gpio.h"

typedef enum
{
    COUNT_FALLING,
    COUNT_RISING,
    COUNT_BOTH
}Mode_t;

class btn_debounce
{
private:
    gpio_num_t btn_pin;
    unsigned long debounceTime;
    unsigned long count;
    Mode_t countMode;

    bool previousSteadyState;  // the previous steady state from the input pin, used to detect pressed and released event
    bool lastSteadyState;      // the last steady state from the input pin
    bool lastFlickerableState; // the last flickerable state from the input pin

    unsigned long lastDebounceTime; // the last time the output pin was toggled

public:
    btn_debounce(gpio_num_t pin, unsigned long Time_debounce);
    ~btn_debounce();
    bool getState();
    bool getCurrentState();
    bool isPressed();
    bool isReleased();
    void setCountMode(Mode_t mode);
    unsigned long getCount(void);
    void resetCount(void);
    void loop(void);
};


#endif 