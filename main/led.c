/* LEDC (LED Controller) basic example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "esp_err.h"
#include "esp_log.h"
#include "led_strip.h"

// GPIO assignment
#define LED_STRIP_GPIO_PIN 48
// Numbers of the LED in the strip
#define LED_STRIP_LED_COUNT 1
// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)

static const char *TAG = "example";

led_strip_handle_t configure_led_strip() {
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO_PIN, // The GPIO that connected to the
                                              // LED strip's data line
        .max_leds = LED_STRIP_LED_COUNT, // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,   // LED strip model
        .color_component_format =
            LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color order of the strip:
                                               // GRB
        .flags = {
            .invert_out = false, // don't invert the output signal
        }};

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to
                                        // different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .mem_block_symbols =
            64, // the memory size of each RMT channel, in words (4 bytes)
        .flags = {
            .with_dma =
                false, // DMA feature is available on chips like ESP32-S3/P4
        }};

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(
        led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with RMT backend");
    return led_strip;
}

led_strip_handle_t get_led_strip() {
    static bool initialized = false;
    static led_strip_handle_t led_strip = NULL;
    if (!initialized) {
        led_strip = configure_led_strip();
        initialized = true;
    }
    return led_strip;
}

void led_on() {
    ESP_ERROR_CHECK(led_strip_set_pixel(get_led_strip(), 0, 255, 255, 255));
    ESP_ERROR_CHECK(led_strip_refresh(get_led_strip()));
    ESP_LOGI(TAG, "LED ON!");
}

void led_off() {
    ESP_ERROR_CHECK(led_strip_clear(get_led_strip()));
    ESP_LOGI(TAG, "LED OFF!");
}