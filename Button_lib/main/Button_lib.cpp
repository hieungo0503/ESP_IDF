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
    btn_debounce BTN_1(GPIO_NUM_34,50);
    btn_debounce BTN_2(GPIO_NUM_35,50); 
    while (true)
    {
        BTN_1.loop();
        BTN_2.loop();
        if(BTN_1.isPressed())
            ESP_LOGI(TAG," BTN1 Press");
        
        if(BTN_2.isPressed())
            ESP_LOGI(TAG," BTN2 Press");
        
        vTaskDelay(10/portTICK_RATE_MS);
        
    }
    
}
