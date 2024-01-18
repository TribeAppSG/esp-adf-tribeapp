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


#include <string.h>
#include "driver/gpio.h"
#include "i2c_bus.h"
#include "board.h"
#include "esp_log.h"
#include "pcf8574.h"

static char *TAG = "PCF8574";
static i2c_bus_handle_t i2c_handle;

#define SET_BITS(_m, _s, _v)  ((_v) ? (_m)|((_s)) : (_m)&~((_s)))
#define GET_BITS(_m, _s)      (((_m) & (_s)) ? true : false)

typedef struct {
    uint8_t addr;
    char *name;
} pcf8574_dev_t;

static pcf8574_dev_t dev_list[] = {
    { 0x70, "PCF8574A"},
    { 0x40, "PCF8574"},
};

static uint8_t pcf8574_addr;

static esp_err_t expander_dev_probe()
{
    for (size_t i = 0; i < sizeof(dev_list) / sizeof(dev_list[0]); i++) {
        if (ESP_OK == i2c_bus_probe_addr(i2c_handle, dev_list[i].addr)) {
            ESP_LOGI(TAG, "Detected IO expander device at 0x%02X, name is: %s",
                     dev_list[i].addr, dev_list[i].name);
            pcf8574_addr = dev_list[i].addr;
            return ESP_OK;
        }
    }
    pcf8574_addr = 0;
    ESP_LOGE(TAG, "IO expander device has not detected");
    return ESP_ERR_NOT_FOUND;
}


static esp_err_t pcf8574_write_reg(uint8_t data)
{
    return i2c_bus_write_data(i2c_handle, pcf8574_addr, &data, sizeof(data));
}

static char pcf8574_read_reg(uint8_t *data)
{
    return i2c_bus_read_data(i2c_handle, pcf8574_addr, data, sizeof(uint8_t));
}

static int i2c_init()
{
    int res = 0;
    i2c_config_t es_i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
	
    res = get_i2c_pins(I2C_NUM_0, &es_i2c_cfg);
    i2c_handle = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
    return res;
}

esp_pcf8574_io_level_t pcf8574_get_input(esp_pcf8574_gpio_num_t gpio_num)
{
	esp_err_t err;
    uint8_t data = 0;
    if (gpio_num < PCF8574_GPIO_NUM_MAX) {
        err = pcf8574_read_reg(&data);
    } else {
        ESP_LOGE(TAG, "gpio num is error, current gpio: %d", gpio_num);
        return PCF8574_LEVEL_ERROR;
    }
	
	if(err != ESP_OK)
		return PCF8574_LEVEL_ERROR;
	
    return GET_BITS(data, gpio_num);
}


esp_err_t pcf8574_set_output(esp_pcf8574_gpio_num_t gpio_num, esp_pcf8574_io_level_t level)
{
    uint8_t data;
    esp_err_t res = ESP_FAIL;
	
    if (gpio_num < PCF8574_GPIO_NUM_MAX) {
        res = pcf8574_read_reg(&data);
		if(res==ESP_OK)
			res = pcf8574_write_reg(SET_BITS(data, gpio_num, level));
    } else {
        ESP_LOGE(TAG, "gpio num is error, current gpio: %d", gpio_num);
    }
	
    return res;
}

esp_err_t pcf8574_init()
{
    esp_err_t ret = ESP_OK;
    i2c_init();

    ret = expander_dev_probe();

    return ret;
}

esp_err_t pcf8574_deinit()
{
    i2c_bus_delete(i2c_handle);
    return ESP_OK;
}
