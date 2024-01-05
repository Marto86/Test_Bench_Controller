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
#include "sdkconfig.h"
#include "output_control.h"
#include "driver/ledc.h"
#include <esp_wifi.h>
#include <esp_event.h>

#include "esp_http_server.h"
#include "driver/uart.h"

#include "appconfig.h"

static const char *TAG = "main";

int num = 0;

static void ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY, // Set output frequency at 4 kHz
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_IO,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

// void uart_write_task(void *pvParameters)
// {
//     const char *data = "Hello, ESP32-S3!\n";
//     while (1)
//     {
//         uart_write_bytes(UART_NUM, data, strlen(data));
//         vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
//     }
// }

void uart_read_task(void *pvParameters)
{
    uint8_t *data = (uint8_t *)malloc(BUF_SIZE);

    while (1)
    {
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);
        if (len > 0)
        {
            data[len] = 0; // Null-terminate the received data

            typedef union
            {
                char str[32];
                int num;
            } ExpectedData;

            ExpectedData expected_data;

            // You can assign either a string or an integer to expected_data
            expected_data.num = 42; // Example integer
            // strncpy(expected_data.str, "This_is_string_from_PROVEtech", sizeof(expected_data.str));

            // Check if received data matches the expected data
            // if (strncmp((const char *)data, expected_data.str, sizeof(expected_data.str)) == 0)
            // {
            //     printf("Received the expected data!\n");

            //     const char *data = "String from PROVEtech is recieved\n";
            //     uart_write_bytes(UART_NUM, data, strlen(data));
            //     vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
            // }
            // if (strncmp((const char *)data, expected_data.str, sizeof(expected_data.str)) != 0)
            // {
            //     printf("Received the unexpected data!\n");

            //     const char *data = "Data is incorrect !!!!!!!!!!!!!!\n";
            //     uart_write_bytes(UART_NUM, data, strlen(data));
            //     vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
            // }
            if (atoi((const char *)data) == expected_data.num)
            {
                printf("Received the expected number: %d\n", expected_data.num);

                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
                // Update duty to apply the new value
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                // Your logic here for the number case
            }
            else
            {
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
            }
        }
    }
    free(data);
}

static void uart_config()
{
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
}

void app_main(void)
{
    ledc_init();
    uart_config();
    xTaskCreate(uart_read_task, "uart_read_task", BUF_SIZE * 2, NULL, configMAX_PRIORITIES, NULL);
    // xTaskCreate(uart_write_task, "uart_send_task", BUF_SIZE * 2, NULL, configMAX_PRIORITIES, NULL);
    // while (1)
    // {

    //   uint32_t *data = (uint32_t *)malloc(BUF_SIZE);
    //   // Read data from the UART
    //   int len = uart_read_bytes(UART, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);
    //   // Write data back to the UART
    //    uart_write_bytes(UART, (const char *)data, len);

    //   vTaskDelay(pdMS_TO_TICKS(1000));
    // }
}
