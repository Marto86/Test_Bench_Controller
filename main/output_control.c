// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// #include "driver/gpio.h"
// #include "appconfig.h"


// static led_indicator_handle_t power_led_handle = NULL;


// void initialize_board_leds(void)
// {
//     led_indicator_config_t config_power = {
//         .off_level = 0,
//         .mode = LED_GPIO_MODE,
//     };
//     power_led_handle = power_indicator_create(LED_RELAY, &config_power); 
// }