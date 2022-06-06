#include "dht20_mock.h"

static i2c_port_t i2c_num_mock;
static i2c_config_t i2c_conf_mock;
static esp_err_t i2c_driver_install_ret_val;
esp_err_t i2c_param_config(i2c_port_t i2c_num, const i2c_config_t *i2c_conf)
{
    i2c_num_mock = i2c_num;
    i2c_conf_mock = *i2c_conf;
    return ESP_OK;
}
void spy_i2c_param_config(i2c_port_t *spy_i2c_master_port,i2c_config_t *spy_conf)
{
    *spy_i2c_master_port = i2c_num_mock;
    *spy_conf = i2c_conf_mock;
}

void set_i2c_driver_install(esp_err_t esp_err)
{
    i2c_driver_install_ret_val = esp_err;
}

static size_t slv_rx_buf_len_mock;
static size_t slv_tx_buf_len_mock;
static int intr_alloc_flags_mock;

esp_err_t i2c_driver_install(i2c_port_t i2c_num, i2c_mode_t mode, size_t slv_rx_buf_len, size_t slv_tx_buf_len, int intr_alloc_flags)
{
    i2c_num_mock = i2c_num;
    i2c_conf_mock.mode = mode;
    slv_rx_buf_len_mock = slv_rx_buf_len;
    slv_tx_buf_len_mock = slv_tx_buf_len;
    intr_alloc_flags_mock = intr_alloc_flags;
    return i2c_driver_install_ret_val;
}

void spy_i2c_driver_install(i2c_port_t *spy_i2c_num, i2c_mode_t *spy_mode, size_t *spy_slv_rx_buf_len, size_t *spy_slv_tx_buf_len, int *spy_intr_alloc_flags)
{
    *spy_i2c_num = i2c_num_mock;
    *spy_mode = i2c_conf_mock.mode;
    *spy_slv_rx_buf_len = slv_rx_buf_len_mock;
    *spy_slv_tx_buf_len = slv_tx_buf_len_mock;
    *spy_intr_alloc_flags = intr_alloc_flags_mock;
    return;
}

static int cmd_qty_mock = 0;

void set_i2c_cmd_link_create(int cmd_qty)
{
    cmd_qty_mock = cmd_qty;
    return;
}

int spy_i2c_cmd_link_create(void)
{
    return cmd_qty_mock;
}

static struct cmd *cmd_link;
static int cmd_link_counter = 0;
i2c_cmd_handle_t i2c_cmd_link_create(void)
{
    cmd_link = calloc(cmd_qty_mock, sizeof(struct cmd));   /* 引数2つ！ */
    return cmd_link;
}

static esp_err_t return_i2c_master_start_ret_val;
static i2c_cmd_handle_t spy_handle_mock;

void set_return_i2c_master_start(esp_err_t esp_err)
{
    return_i2c_master_start_ret_val = esp_err;
    return;
}

esp_err_t i2c_master_start(i2c_cmd_handle_t cmd_handle)
{
    struct cmd *cmd_link_tmp = cmd_handle;
    cmd_link_tmp[cmd_link_counter].cmd_handle = cmd_handle;
    cmd_link_tmp[cmd_link_counter].type = START;
    cmd_link_counter++;
    spy_handle_mock = cmd_handle;
    return return_i2c_master_start_ret_val;
}

void spy_i2c_master_start(i2c_cmd_handle_t *cmd_handle_addr)
{
    *cmd_handle_addr = spy_handle_mock;
    return;
}

static esp_err_t return_i2c_master_write_byte = ESP_OK;
void set_return_i2c_master_write_byte(esp_err_t err)
{
    return_i2c_master_write_byte = err;
}

esp_err_t i2c_master_write_byte(i2c_cmd_handle_t cmd_handle, uint8_t data, bool ack_en)
{

    struct cmd *cmd_link_tmp = cmd_handle;
    cmd_link_tmp[cmd_link_counter].cmd_handle = cmd_handle;
    cmd_link_tmp[cmd_link_counter].type = WRITE;
    cmd_link_tmp[cmd_link_counter].data = data;
    cmd_link_tmp[cmd_link_counter].ack_en = ack_en;
    cmd_link_counter++;
    return return_i2c_master_write_byte;
}

static esp_err_t return_i2c_master_write = ESP_OK;
void set_return_i2c_master_write(esp_err_t err)
{
    return_i2c_master_write = err;
}

esp_err_t i2c_master_write(i2c_cmd_handle_t cmd_handle, const uint8_t *data, size_t data_len, bool ack_en)
{
    struct cmd *cmd_link_tmp = cmd_handle;
    for (size_t i = 0; i < data_len; i++)
    {
        int index = cmd_link_counter+(int)i;
        cmd_link_tmp[index].cmd_handle = cmd_handle;
        cmd_link_tmp[index].type = WRITE;
        cmd_link_tmp[index].data = *(data+i);
        cmd_link_tmp[index].ack_en = ack_en;
    }
    cmd_link_counter += data_len;
    return return_i2c_master_write;
}

static esp_err_t return_i2c_master_stop = ESP_OK;
void set_i2c_master_stop(esp_err_t err)
{
    return_i2c_master_stop = err;
}

esp_err_t i2c_master_stop(i2c_cmd_handle_t cmd_handle)
{
    struct cmd *cmd_link_tmp = cmd_handle;
    cmd_link_tmp[cmd_link_counter].cmd_handle = cmd_handle;
    cmd_link_tmp[cmd_link_counter].type = STOP;
    cmd_link_counter++;
    return return_i2c_master_stop;
}

uint8_t return_rd_data = 0;
esp_err_t return_i2c_master_read_byte = ESP_OK;
void set_return_i2c_master_read_byte(esp_err_t err,uint8_t test_rd_data)
{
    return_rd_data = test_rd_data;
    return_i2c_master_read_byte = err;
}

esp_err_t i2c_master_read_byte(i2c_cmd_handle_t cmd_handle, uint8_t *data, i2c_ack_type_t ack)
{
    struct cmd *cmd_link_tmp = cmd_handle;
    cmd_link_tmp[cmd_link_counter].cmd_handle = cmd_handle;
    cmd_link_tmp[cmd_link_counter].type = READ;
    cmd_link_tmp[cmd_link_counter].ack = ack;
    cmd_link_counter++;

    *data = return_rd_data;

    return return_i2c_master_read_byte;
}

uint8_t *return_rd_data_array = NULL;
size_t return_rd_data_array_len = 0;
esp_err_t return_i2c_master_read = ESP_OK;

void set_return_i2c_master_read(esp_err_t err,uint8_t *test_rd_data,size_t test_rd_data_len)
{
    return_i2c_master_read = err;
    return_rd_data_array = test_rd_data;
    return_rd_data_array_len = test_rd_data_len;
    return;
}

esp_err_t i2c_master_read(i2c_cmd_handle_t cmd_handle, uint8_t *data, size_t data_len, i2c_ack_type_t ack)
{

    struct cmd *cmd_link_tmp = cmd_handle;
    for (size_t i = 0; i < data_len; i++)
    {
        int index = cmd_link_counter+(int)i;
        cmd_link_tmp[index].cmd_handle = cmd_handle;
        cmd_link_tmp[index].type = READ;
        cmd_link_tmp[index].ack = ack;

        data[i] = return_rd_data_array[i];
    }
    cmd_link_counter += data_len;

    return return_i2c_master_read;
}


static esp_err_t return_i2c_master_cmd_begin = ESP_OK;
void set_i2c_master_cmd_begin(esp_err_t err)
{
    return_i2c_master_cmd_begin = err;
    return;
}

esp_err_t i2c_master_cmd_begin(i2c_port_t i2c_num, i2c_cmd_handle_t cmd_handle, TickType_t ticks_to_wait)
{
    return return_i2c_master_cmd_begin;
}

void i2c_cmd_link_delete(i2c_cmd_handle_t cmd_handle)
{
    free(cmd_handle);
}