#ifndef WRP_I2C
#define WRP_i2C

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#define I2C_PORT                I2C_NUM_0
#define I2C_SCL_IO              GPIO_NUM_22
#define I2C_SDA_IO              GPIO_NUM_21
#define I2C_FREQ_HZ             100000

esp_err_t i2c_master_bus_setup(i2c_master_bus_handle_t *i2c_bus);
esp_err_t i2c_master_dev_setup(i2c_master_bus_handle_t i2c_bus, i2c_master_dev_handle_t *i2c_dev, uint16_t dev_addr);
esp_err_t read_reg(i2c_master_dev_handle_t i2c_dev, uint8_t reg_addr, uint8_t *data, size_t len);
esp_err_t write(i2c_master_dev_handle_t i2c_dev, uint8_t reg_addr, uint8_t data);

#endif