#include "dht20_mock.h"

static i2c_port_t i2c_num_mock;
static i2c_config_t i2c_conf_mock;
static esp_err_t i2c_driver_install_ret_val;
esp_err_t i2c_param_config(i2c_port_t i2c_num, const i2c_config_t *i2c_conf){
    i2c_num_mock = i2c_num;
    i2c_conf_mock = *i2c_conf;
    return ESP_OK;
}
void spy_i2c_param_config(i2c_port_t *spy_i2c_master_port,i2c_config_t *spy_conf){
    *spy_i2c_master_port = i2c_num_mock;
    *spy_conf = i2c_conf_mock;
}

void set_i2c_driver_install(esp_err_t esp_err){
    i2c_driver_install_ret_val = esp_err;
}

static size_t slv_rx_buf_len_mock;
static size_t slv_tx_buf_len_mock;
static int intr_alloc_flags_mock;

esp_err_t i2c_driver_install(i2c_port_t i2c_num, i2c_mode_t mode, size_t slv_rx_buf_len, size_t slv_tx_buf_len, int intr_alloc_flags){
    i2c_num_mock = i2c_num;
    i2c_conf_mock.mode = mode;
    slv_rx_buf_len_mock = slv_rx_buf_len;
    slv_tx_buf_len_mock = slv_tx_buf_len;
    intr_alloc_flags_mock = intr_alloc_flags;
    return i2c_driver_install_ret_val;
}

void spy_i2c_driver_install(i2c_port_t *spy_i2c_num, i2c_mode_t *spy_mode, size_t *spy_slv_rx_buf_len, size_t *spy_slv_tx_buf_len, int *spy_intr_alloc_flags){
    *spy_i2c_num = i2c_num_mock;
    *spy_mode = i2c_conf_mock.mode;
    *spy_slv_rx_buf_len = slv_rx_buf_len_mock;
    *spy_slv_tx_buf_len = slv_tx_buf_len_mock;
    *spy_intr_alloc_flags = intr_alloc_flags_mock;
    return;
}

static i2c_cmd_handle_t handle_mock;

void set_i2c_cmd_link_create(i2c_cmd_handle_t handle){
    handle_mock = handle;
    return;
}

i2c_cmd_handle_t i2c_cmd_link_create(void){
    return handle_mock;
}

static esp_err_t return_i2c_master_start_ret_val;
static i2c_cmd_handle_t cmd_handle_mock;
void set_return_i2c_master_start(esp_err_t esp_err){
    return_i2c_master_start_ret_val = esp_err;
    return;
}

esp_err_t i2c_master_start(i2c_cmd_handle_t cmd_handle){
    cmd_handle_mock = cmd_handle;
    return return_i2c_master_start_ret_val;
}

void spy_i2c_master_start(i2c_cmd_handle_t *cmd_handle_addr){
    *cmd_handle_addr = cmd_handle_mock;
    return;
}