#ifndef _DHT20_H_
#define _DHT20_H_

#ifdef __cplusplus
extern "C"
{
#endif

    #define I2C_MASTER_SCL_IO           CONFIG_I2C_MASTER_SCL      /*!< GPIO number used for I2C master clock */
    #define I2C_MASTER_SDA_IO           CONFIG_I2C_MASTER_SDA      /*!< GPIO number used for I2C master data  */
    #define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
    #define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
    #define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
    #define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */

    #include "driver/i2c.h"

    esp_err_t i2c_master_init(void);

#ifdef __cplusplus
}
#endif

#endif // _DHT20_H_