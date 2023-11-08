#ifndef GROUND_CONTROL_I2C_H
#define GROUND_CONTROL_I2C_H

#include "driver/i2c.h"

#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 100000

class I2C
{
public:
    static void init()
    {
        i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO,
            .scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master = {
                .clk_speed = I2C_MASTER_FREQ_HZ
            },
            .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL
        };

        i2c_param_config(I2C_MASTER_NUM, &conf);
        i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
    }
};

#endif