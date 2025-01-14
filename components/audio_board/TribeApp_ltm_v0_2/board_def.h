/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2019 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
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

#ifndef _AUDIO_BOARD_DEFINITION_H_
#define _AUDIO_BOARD_DEFINITION_H_

/**
 * @brief SDCARD Function Definition
 */
//#define FUNC_SDCARD_EN            (1)
#define SDCARD_OPEN_FILE_NUM_MAX  0
#define SDCARD_INTR_GPIO          -1
#define SDCARD_PWR_CTRL           -1


/**
 * @brief LED Function Definition
 */
#define FUNC_SYS_LEN_EN           (1)
#define BLUE_LED_GPIO             -1
#define GREEN_LED_GPIO            -1
#define YELLOW_LED_GPIO            -1


/**
 * @brief Audio Codec Chip Function Definition
 */
#define FUNC_AUDIO_CODEC_EN       (1)
#define ES7243_MCLK_GPIO          GPIO_NUM_0
//#define HEADPHONE_DETECT          -1
#define PA_ENABLE_GPIO            GPIO_NUM_12
#define LED_CS_GPIO					GPIO_NUM_19
#define UWB_CS_GPIO					GPIO_NUM_21
#define AMMICOM_CS_GPIO				GPIO_NUM_22
#define ES8311_MCLK_SOURCE        0   /* 0 From MCLK of esp32   1 From BCLK */
#define CODEC_ADC_I2S_PORT        (1)
#define CODEC_ADC_BITS_PER_SAMPLE I2S_BITS_PER_SAMPLE_16BIT
#define CODEC_ADC_SAMPLE_RATE     (16000)
#define RECORD_HARDWARE_AEC       (true)

extern audio_hal_func_t AUDIO_CODEC_ES8311_DEFAULT_HANDLE;
extern audio_hal_func_t AUDIO_CODEC_ES7243_DEFAULT_HANDLE;
#define AUDIO_CODEC_DEFAULT_CONFIG(){                   \
        .adc_input  = AUDIO_HAL_ADC_INPUT_LINE1,        \
        .dac_output = AUDIO_HAL_DAC_OUTPUT_ALL,         \
        .codec_mode = AUDIO_HAL_CODEC_MODE_BOTH,        \
        .i2s_iface = {                                  \
            .mode = AUDIO_HAL_MODE_SLAVE,               \
            .fmt = AUDIO_HAL_I2S_NORMAL,                \
            .samples = AUDIO_HAL_48K_SAMPLES,           \
            .bits = AUDIO_HAL_BIT_LENGTH_16BITS,        \
        },                                              \
};


/**
 * @brief Button Function Definition
 */
#define FUNC_BUTTON_EN            (1)
#define ADC_DETECT_GPIO           -1
#define INPUT_KEY_NUM     			2             /* You need to define the number of input buttons on your board */

#define BUTTON_SET_ID             GPIO_NUM_39		//GPIO num of set key (SENSOR_VN)
#define BUTTON_MODE_ID            GPIO_NUM_34		//GPIO num of mode key (IO34)



#define INPUT_KEY_DEFAULT_INFO() {                      \
     {                                                  \
        .type = PERIPH_ID_BUTTON,                       \
        .user_id = INPUT_KEY_USER_ID_MODE,               \
        .act_id = BUTTON_MODE_ID,                        \
    },                                                  \
    {                                                   \
        .type = PERIPH_ID_BUTTON,                       \
        .user_id = INPUT_KEY_USER_ID_SET,              \
        .act_id = BUTTON_SET_ID,                       \
    }													\
}

#endif
