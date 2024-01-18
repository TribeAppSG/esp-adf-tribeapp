/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2021 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
 
/* 
 * PCF8574 driver modified from Espressif TCA9554 driver by TribeApp
 * Note that PCF8574 is quasi-bidirectional and has no config registers
 */

#ifndef _PCF8574_H
#define _PCF8574_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PCF8574_GPIO_NUM_0 = BIT(0),
    PCF8574_GPIO_NUM_1 = BIT(1),
    PCF8574_GPIO_NUM_2 = BIT(2),
    PCF8574_GPIO_NUM_3 = BIT(3),
    PCF8574_GPIO_NUM_4 = BIT(4),
    PCF8574_GPIO_NUM_5 = BIT(5),
    PCF8574_GPIO_NUM_6 = BIT(6),
    PCF8574_GPIO_NUM_7 = BIT(7),
    PCF8574_GPIO_NUM_MAX
} esp_pcf8574_gpio_num_t;

typedef enum {
    PCF8574_IO_LOW,
    PCF8574_IO_HIGH,
    PCF8574_LEVEL_ERROR
} esp_pcf8574_io_level_t;

/*
 * @brief Initialize PCF8574 chip
 *
 * @return
 *      - ESP_OK
 *      - ESP_FAIL
 */
esp_err_t pcf8574_init(void);

/**
 * @brief Deinitialize PCF8574 chip
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t pcf8574_deinit(void);

/*
 * @brief Get PCF8574 input level
 *
 * @param gpio_num  GPIO of PCF8574
 *
 * @return
 *      - esp_pcf8574_io_level_t
 */
esp_pcf8574_io_level_t pcf8574_get_input(esp_pcf8574_gpio_num_t gpio_num);

/*
 * @brief Set PCF8574 output state
 *
 * @param gpio_num  GPIO of PCF8574
 *
 * @return
 *      - esp_pcf8574_io_level_t
 */
esp_err_t pcf8574_set_output(esp_pcf8574_gpio_num_t gpio_num, esp_pcf8574_io_level_t level);



#ifdef __cplusplus
}
#endif

#endif
