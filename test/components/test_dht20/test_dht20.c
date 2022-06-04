#include <unity.h>
#include "driver/i2c.h"
#include "../components/dht20/mocks/dht20_mock.h"
#include "../components/dht20/dht20.h"

int i2c_master_port;
i2c_config_t conf;

void setUp(void)
{
  // set stuff up here
    i2c_master_port = I2C_MASTER_NUM;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    set_i2c_driver_install(ESP_OK);

}

void tearDown(void)
{
  // clean stuff up here
}

//i2cDriverInitTest
void test_i2c_driver_mock_i2c_param_config(void)
{

  i2c_param_config(i2c_master_port, &conf);
  int spy_i2c_master_port = 1;
  i2c_config_t spy_conf;
  spy_i2c_param_config(&spy_i2c_master_port,&spy_conf);


  TEST_ASSERT_EQUAL(i2c_master_port, spy_i2c_master_port);
  TEST_ASSERT_EQUAL(conf.mode,spy_conf.mode);
  TEST_ASSERT_EQUAL(conf.sda_io_num,spy_conf.sda_io_num);
  TEST_ASSERT_EQUAL(conf.scl_io_num,spy_conf.scl_io_num);
  TEST_ASSERT_EQUAL(conf.sda_pullup_en,spy_conf.sda_pullup_en);
  TEST_ASSERT_EQUAL(conf.scl_pullup_en,spy_conf.scl_pullup_en);
  TEST_ASSERT_EQUAL(conf.master.clk_speed,spy_conf.master.clk_speed);
}

void test_i2c_driver_mock_i2c_driver_install(void){
  esp_err_t retVal_install = 
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
  TEST_ASSERT_EQUAL(ESP_OK,retVal_install);

  i2c_port_t spy_i2c_num;
  i2c_mode_t spy_mode;
  size_t spy_slv_rx_buf_len;
  size_t spy_slv_tx_buf_len;
  int spy_intr_alloc_flags;
  spy_i2c_driver_install(&spy_i2c_num, &spy_mode, &spy_slv_rx_buf_len, &spy_slv_tx_buf_len, &spy_intr_alloc_flags);

  TEST_ASSERT_EQUAL(i2c_master_port,spy_i2c_num);
  TEST_ASSERT_EQUAL(conf.mode,spy_mode);
  TEST_ASSERT_EQUAL(I2C_MASTER_RX_BUF_DISABLE,spy_slv_rx_buf_len);
  TEST_ASSERT_EQUAL(I2C_MASTER_TX_BUF_DISABLE,spy_slv_tx_buf_len);
  TEST_ASSERT_EQUAL(0,spy_intr_alloc_flags);
}

void test_function_i2c_master_init(void){
  esp_err_t init_ret_val = i2c_master_init();
  TEST_ASSERT_EQUAL(ESP_OK,init_ret_val);

  int spy_i2c_master_port = 1;
  i2c_config_t spy_conf;
  spy_i2c_param_config(&spy_i2c_master_port,&spy_conf);
  TEST_ASSERT_EQUAL(i2c_master_port, spy_i2c_master_port);
  TEST_ASSERT_EQUAL(conf.mode,spy_conf.mode);
  TEST_ASSERT_EQUAL(conf.sda_io_num,spy_conf.sda_io_num);
  TEST_ASSERT_EQUAL(conf.scl_io_num,spy_conf.scl_io_num);
  TEST_ASSERT_EQUAL(conf.sda_pullup_en,spy_conf.sda_pullup_en);
  TEST_ASSERT_EQUAL(conf.scl_pullup_en,spy_conf.scl_pullup_en);
  TEST_ASSERT_EQUAL(conf.master.clk_speed,spy_conf.master.clk_speed);

  i2c_port_t spy_i2c_num;
  i2c_mode_t spy_mode;
  size_t spy_slv_rx_buf_len;
  size_t spy_slv_tx_buf_len;
  int spy_intr_alloc_flags;
  spy_i2c_driver_install(&spy_i2c_num, &spy_mode, &spy_slv_rx_buf_len, &spy_slv_tx_buf_len, &spy_intr_alloc_flags);

  TEST_ASSERT_EQUAL(i2c_master_port,spy_i2c_num);
  TEST_ASSERT_EQUAL(conf.mode,spy_mode);
  TEST_ASSERT_EQUAL(I2C_MASTER_RX_BUF_DISABLE,spy_slv_rx_buf_len);
  TEST_ASSERT_EQUAL(I2C_MASTER_TX_BUF_DISABLE,spy_slv_tx_buf_len);
  TEST_ASSERT_EQUAL(0,spy_intr_alloc_flags);


}

//cmdLinkGenerateTest

i2c_cmd_handle_t cmd_handle = NULL;
int test_cmd_qty = 20;

void test_i2c_driver_mock_i2c_cmd_link_create(void)
{
  set_i2c_cmd_link_create(test_cmd_qty);
  TEST_ASSERT_EQUAL(test_cmd_qty , spy_i2c_cmd_link_create());
  cmd_handle = i2c_cmd_link_create();
  TEST_ASSERT_NOT_NULL(cmd_handle);

}

void test_i2c_driver_mock_i2c_master_start(void)
{
  set_return_i2c_master_start(ESP_OK);
  TEST_ASSERT_EQUAL(ESP_OK, i2c_master_start(cmd_handle));
  i2c_cmd_handle_t spy_cmd_handle;
  spy_i2c_master_start(&spy_cmd_handle);
  TEST_ASSERT_EQUAL(cmd_handle,spy_cmd_handle);
}


void test_i2c_driver_mock_i2c_master_write_byte(void)
{
  set_return_i2c_master_write_byte(ESP_OK);
  esp_err_t err =  i2c_master_write_byte(/*cmd_handle*/cmd_handle, /*data*/1, /*ack_en:EN*/0x01);
  TEST_ASSERT_EQUAL(ESP_OK,err);
}

const uint8_t data[3] = {3,4,5};
void test_i2c_driver_mock_i2c_master_write(void)
{
  set_return_i2c_master_write(ESP_OK);
  esp_err_t err = i2c_master_write(/*cmd_handle*/cmd_handle,/* *data*/data,/*data_len*/3,/*ack_en*/0x01);
  TEST_ASSERT_EQUAL(ESP_OK,err);
}

void test_i2c_driver_mock_i2c_master_stop(void)
{
  set_i2c_master_stop(ESP_OK);
  esp_err_t err = i2c_master_stop(cmd_handle);
  TEST_ASSERT_EQUAL(ESP_OK,err);
}

void test_i2c_driver_cmd_link(void){

struct cmd *cmd_link_tmp = cmd_handle;
int index = 0;
TEST_ASSERT_EQUAL(cmd_handle , cmd_link_tmp[index].cmd_handle);
TEST_ASSERT_EQUAL(START , cmd_link_tmp[index].type); 

index = 1;
TEST_ASSERT_EQUAL(cmd_handle , cmd_link_tmp[index].cmd_handle);
TEST_ASSERT_EQUAL(1 , cmd_link_tmp[index].data);
TEST_ASSERT_EQUAL(0x01 , cmd_link_tmp[index].ack_en);
TEST_ASSERT_EQUAL(WRITE , cmd_link_tmp[index].type);

index = 2;
TEST_ASSERT_EQUAL(cmd_handle , cmd_link_tmp[index].cmd_handle);
TEST_ASSERT_EQUAL(3 , cmd_link_tmp[index].data);
TEST_ASSERT_EQUAL(0x01 , cmd_link_tmp[index].ack_en);
TEST_ASSERT_EQUAL(WRITE , cmd_link_tmp[index].type);

index = 3;
TEST_ASSERT_EQUAL(cmd_handle , cmd_link_tmp[index].cmd_handle);
TEST_ASSERT_EQUAL(4 , cmd_link_tmp[index].data);
TEST_ASSERT_EQUAL(0x01 , cmd_link_tmp[index].ack_en);
TEST_ASSERT_EQUAL(WRITE , cmd_link_tmp[index].type);

index = 4;
TEST_ASSERT_EQUAL(cmd_handle , cmd_link_tmp[index].cmd_handle);
TEST_ASSERT_EQUAL(5 , cmd_link_tmp[index].data);
TEST_ASSERT_EQUAL(0x01 , cmd_link_tmp[index].ack_en);
TEST_ASSERT_EQUAL(WRITE , cmd_link_tmp[index].type);

index = 5;
TEST_ASSERT_EQUAL(cmd_handle , cmd_link_tmp[index].cmd_handle);
TEST_ASSERT_EQUAL(STOP , cmd_link_tmp[index].type);

}

void app_main()
{
  UNITY_BEGIN();

  RUN_TEST(test_i2c_driver_mock_i2c_param_config);
  RUN_TEST(test_i2c_driver_mock_i2c_driver_install);
  RUN_TEST(test_function_i2c_master_init);
  RUN_TEST(test_i2c_driver_mock_i2c_cmd_link_create);
  RUN_TEST(test_i2c_driver_mock_i2c_master_start);
  RUN_TEST(test_i2c_driver_mock_i2c_master_write_byte);
  RUN_TEST(test_i2c_driver_mock_i2c_master_write);
  RUN_TEST(test_i2c_driver_mock_i2c_master_stop);

  RUN_TEST(test_i2c_driver_cmd_link);
  UNITY_END();

}
