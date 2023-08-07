
#include "btn_debounce.h"

btn_debounce::btn_debounce(gpio_num_t pin, unsigned long Time_debounce)
{
    btn_pin = pin;
    debounceTime = Time_debounce;
	count = 0;
	countMode = COUNT_FALLING;
    
    gpio_config_t io_conf;
	io_conf.pin_bit_mask = 1ULL<< btn_pin;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
	io_conf.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&io_conf);

	previousSteadyState = gpio_get_level(pin);
	lastSteadyState = previousSteadyState;
	lastFlickerableState = previousSteadyState;

	lastDebounceTime = 0;
}

btn_debounce::~btn_debounce()
{
}

int btn_debounce:: getState()
{
    return lastSteadyState;
}
int btn_debounce::getCurrentState(){
	return gpio_get_level(btn_pin);
}

bool btn_debounce::isPressed(void) {
	if(previousSteadyState == 1 && lastSteadyState == 0)
		return true;
	else
		return false;
}

bool btn_debounce::isReleased(void) {
	if(previousSteadyState == 0 && lastSteadyState == 1)
		return true;
	else
		return false;
}

void btn_debounce::setCountMode(Mode_t mode) {
	countMode = mode;
}

unsigned long btn_debounce::getCount(void) {
	return count;
}

void btn_debounce::resetCount(void) {
	count = 0;
}
void btn_debounce:: loop()
{
    int currentState = gpio_get_level(btn_pin);
	unsigned long currentTime = esp_timer_get_time()/1000;

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH), and you've waited long enough
	// since the last press to ignore any noise:

	// If the switch/button changed, due to noise or pressing:
	if (currentState != lastFlickerableState) {
		// reset the debouncing timer
		lastDebounceTime = currentTime;
		// save the the last flickerable state
		lastFlickerableState = currentState;
	}

	if ((currentTime - lastDebounceTime) >= debounceTime) {
		// whatever the reading is at, it's been there for longer than the debounce
		// delay, so take it as the actual current state:

		// save the the steady state
		previousSteadyState = lastSteadyState;
		lastSteadyState = currentState;
	}

	if(previousSteadyState != lastSteadyState){
		if(countMode == COUNT_BOTH)
			count++;
		else if(countMode == COUNT_FALLING){
			if(previousSteadyState == 1 && lastSteadyState == 0)
				count++;
		}
		else if(countMode == COUNT_RISING){
			if(previousSteadyState == 0 && lastSteadyState == 1)
				count++;
		}
	}
}