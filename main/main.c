/* LEDC (LED Controller) basic example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "driver/ledc.h"
#include "esp_err.h"
#include <stdio.h>

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY (4096)      // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY (4000) // Frequency in Hertz. Set frequency at 4 kHz

/* Warning:
 * For ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C2, ESP32C6, ESP32H2, ESP32P4
 * targets, when LEDC_DUTY_RES selects the maximum duty resolution (i.e. value
 * equal to SOC_LEDC_TIMER_BIT_WIDTH), 100% duty cycle is not reachable (duty
 * cannot be set to (2 ** SOC_LEDC_TIMER_BIT_WIDTH)).
 */

static void example_ledc_init(void) {
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY, // Set output frequency at 4 kHz
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel[3] = {
        {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_0,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = 14, // Set GPIO 14 as the LEDC output
            .duty = 0,      // Set duty to 0%
            .hpoint = 0,
        },
        {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_1,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = 13, // Set GPIO 13 as the LEDC output
            .duty = 0,      // Set duty to 0%
            .hpoint = 0,
        },
        {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_2,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = 12, // Set GPIO 12 as the LEDC output
            .duty = 0,      // Set duty to 0%
            .hpoint = 0,
        },
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[0]));
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[1]));
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[2]));
}

void app_main(void) {
    // Set the LEDC peripheral configuration
    example_ledc_init();
    // Set duty to 50%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0));
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1));
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_2, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_2));
}
