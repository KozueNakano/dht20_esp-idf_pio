#ifndef _DHT20MOCK_H_
#define _DHT20MOCK_H_

#ifdef __cplusplus
extern "C"
{
#endif
    #include <esp_err.h>
    #include "driver/i2c.h"
    void spy_i2c_param_config(i2c_port_t*,i2c_config_t*);
    void set_i2c_driver_install(esp_err_t);
    void spy_i2c_driver_install(i2c_port_t *i2c_num, i2c_mode_t *mode, size_t *slv_rx_buf_len, size_t *slv_tx_buf_len, int *intr_alloc_flags);
    void set_i2c_cmd_link_create(i2c_cmd_handle_t);
    void set_return_i2c_master_start(esp_err_t);
    void spy_i2c_master_start(i2c_cmd_handle_t*);

#ifdef __cplusplus
}
#endif

#endif // _DHT20MOCK_H_