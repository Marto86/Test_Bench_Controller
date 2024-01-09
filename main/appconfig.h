#ifndef __APPCONFIG_H__
#define __APPCONFIG_H__

#define FIRMWARE_VERSION "1.0.0"

#define COMMAND_RECEIVED_MSG "COMMAND RECEIVED"

#define ECHO_TEST_TXD (GPIO_NUM_4)
#define ECHO_TEST_RXD (GPIO_NUM_5)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define BUF_SIZE (2048)


#define LED_RELAY (49)
// #define RUN_TESTS
#define BTN_FORCE_RESEND_DELAY_SECONDS (180)
#define SEND_DATA_DIFF_INTERVAL_SECONDS (300)
#define SEND_DATA_ALL_INTERVAL_SECONDS (6 * 60 * 60) // 6 hours

#define LED_POWER (9)

#define RELEAY_POWER_ON (0)
#define RELEAY_POWER_OFF (1)

#define RELAY_1  (1)
#define RELAY_2  (2)
#define RELAY_3  (3)
#define RELAY_4  (4)
#define RELAY_5  (5)
#define RELAY_6  (6)
#define RELAY_7  (7)
#define RELAY_8  (8)

#define LED_COMMUNICATE (49)
// Chamber relays

#define CHAMBER_RELAY_1 (0)
#define CHAMBER_RELAY_2 (0)
#define CHAMBER_RELAY_3 (0)
#define CHAMBER_RELAY_4 (0)

#define DATA_READ_RETRY_COUNT (3)

static const int RX_BUF_SIZE = 1024;

#define UART_NUM UART_NUM_0
#define TX_PIN 17
#define RX_PIN 16
#define BAUD_RATE 115200

#define UART UART_NUM_0


#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (48) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (4000) // Frequency in Hertz. Set frequency at 4 kHz


#endif //__APPCONFIG_H__