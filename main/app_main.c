#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_netif.h"

#include <esp_wifi.h>
#include <esp_event.h>

#include "esp_http_server.h"
#include "driver/uart.h"

#include "appconfig.h"

static const char *TAG = "main";

static void uart_config()
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};

    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 2 * 1024, 0, 0, NULL, 0);
    
}




void app_main(void)
{

    uart_config();
    uint32_t *data = (uint32_t *)malloc(BUF_SIZE);
    // Read data from the UART
    int len = uart_read_bytes(UART_NUM_1, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);
    // Write data back to the UART
    uart_write_bytes(UART_NUM_1, (const char *)data, len);
}
