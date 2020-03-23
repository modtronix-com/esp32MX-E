/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "sdkconfig.h"

#define BLINK_GPIO 5	// esp32MX-E uses GPIO 5 for the LED

#define STM32_BOOTLOADER

void blink_task(void *pvParameter) {
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

#define BUF_SIZE (1024)

static void echo_task(void *arg)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        //.parity    = UART_PARITY_DISABLE,
        .parity    = UART_PARITY_EVEN,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // Configure UART 0 - Ensure UART 0 has been disabled in ESD-IDF!
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, 1, 3, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);

    uart_config_t uart_config1 = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        //.parity    = UART_PARITY_DISABLE,
        .parity    = UART_PARITY_EVEN,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // Configure UART 1
    uart_param_config(UART_NUM_1, &uart_config1);
    uart_set_pin(UART_NUM_1, 33, 32, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Configure a temporary buffer for the incoming data
    uint8_t *data0 = (uint8_t *) malloc(BUF_SIZE);
    uint8_t *data1 = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART0, and sent to UART1
        int len0 = uart_read_bytes(UART_NUM_0, data0, BUF_SIZE, 20 / portTICK_RATE_MS);
        uart_write_bytes(UART_NUM_1, (const char *) data0, len0);

        int len1 = uart_read_bytes(UART_NUM_1, data1, BUF_SIZE, 20 / portTICK_RATE_MS);
        uart_write_bytes(UART_NUM_0, (const char *) data1, len1);
    }
}

void app_main() {
    //printf("Hello world!\n");

    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    xTaskCreate(echo_task, "uart_echo_task", 1024, NULL, 10, NULL);
}
