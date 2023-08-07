#include <stdio.h>
#include "esp_timer.h"
#include <driver/gpio.h>
#include "btn_debounce.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


const char *TAG = "btn_TEST";
extern "C" {
   void app_main();
}

void app_main(void)
{
   btn_debounce *BTN1 = new btn_debounce(GPIO_NUM_33,50);
   btn_debounce *BTN2 = new btn_debounce(GPIO_NUM_18,50);
   

    while (true)
    {
        BTN1->loop();
        BTN2->loop();
        if(BTN1->isPressed())
            ESP_LOGI(TAG," BTN1 Press");
        
        if(BTN2->isPressed())
            ESP_LOGI(TAG," BTN2 Press");

        vTaskDelay(10/portTICK_RATE_MS);
        
    }
    
}
