#include "wrp_i2c.h"

esp_err_t i2c_master_bus_setup(i2c_master_bus_handle_t *i2c_bus) {
    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_PORT,
        .scl_io_num = I2C_SCL_IO,
        .sda_io_num = I2C_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, i2c_bus));
    
    return ESP_OK;
}

esp_err_t i2c_master_dev_setup(i2c_master_bus_handle_t i2c_bus, i2c_master_dev_handle_t *i2c_dev, uint16_t dev_addr){
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = dev_addr,
        .scl_speed_hz = I2C_FREQ_HZ,
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_bus, &dev_config, i2c_dev));

    return ESP_OK;
}

esp_err_t read_reg(i2c_master_dev_handle_t i2c_dev, uint8_t reg_addr, uint8_t *data, size_t len) {
    return i2c_master_transmit_receive(i2c_dev, &reg_addr, 1, data, len, pdMS_TO_TICKS(100));
}

esp_err_t write(i2c_master_dev_handle_t i2c_dev, uint8_t reg_addr, uint8_t data) {
    uint8_t write_buf[2] = { reg_addr, data };
    return i2c_master_transmit(i2c_dev, write_buf, sizeof(write_buf), pdMS_TO_TICKS(100));
}