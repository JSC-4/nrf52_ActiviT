#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "mpu6050.h"
#include "nrf_drv_twi.h"

/* TWI instance ID. */
#define TWI_INSTANCE_ID 0

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;



/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const *p_event, void *p_context) {
  switch (p_event->type) {
  case NRF_DRV_TWI_EVT_DONE:
    //if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
    //{
    //    data_handler(m_sample);
    //}
    m_xfer_done = true;
    break;
  default:
    break;
  }
}

void twi_init(void) {

  ret_code_t err_code;

  const nrf_drv_twi_config_t mpu6050_twi_config = {
      .scl = MPU6050_SCL_M,
      .sda = MPU6050_SDA_M,
      .frequency = NRF_DRV_TWI_FREQ_400K,
      .interrupt_priority = APP_IRQ_PRIORITY_LOW,
      .clear_bus_init = false};

  err_code = nrf_drv_twi_init(&m_twi, &mpu6050_twi_config, twi_handler, NULL);
  APP_ERROR_CHECK(err_code);

  nrf_drv_twi_enable(&m_twi);
}

bool mpu6050_twi_write(uint8_t register_address, const uint8_t value) {

  ret_code_t err_code;
  m_xfer_done = false;

  uint8_t tx_buf[2];

  tx_buf[0] = register_address;
  tx_buf[1] = value;

  err_code = nrf_drv_twi_tx(&m_twi, MPU6050_ADDRESS, tx_buf, 2, false);
  APP_ERROR_CHECK(err_code);

  while (m_xfer_done == false);

  return NRF_SUCCESS;
}

bool mpu6050_twi_read(uint8_t register_address, uint8_t *rec_data, uint8_t number_of_bytes) {

  ret_code_t err_code;
  m_xfer_done = false;

  err_code = nrf_drv_twi_tx(&m_twi, MPU6050_ADDRESS, &register_address, 1, true);
  APP_ERROR_CHECK(err_code);

  while (m_xfer_done == false);

  m_xfer_done = false;

  err_code = nrf_drv_twi_rx(&m_twi, MPU6050_ADDRESS, rec_data, number_of_bytes);
  APP_ERROR_CHECK(err_code);

  while (m_xfer_done == false);

  return NRF_SUCCESS;
}

bool mpu6050_ReadAcc(int16_t *pACC_X , int16_t *pACC_Y , int16_t *pACC_Z)
{

  uint8_t data_buf[6];

  mpu6050_twi_read(MPU6050_RA_ACCEL_XOUT_H, data_buf, sizeof(data_buf));

  *pACC_X = (data_buf[0] << 8) | data_buf[1];
  *pACC_Y= (data_buf[2] << 8) | data_buf[3];
  *pACC_Z = (data_buf[4] << 8) | data_buf[5];

  return NRF_SUCCESS;
}

bool mpu6050_ReadGyro(int16_t *pGYRO_X , int16_t *pGYRO_Y , int16_t *pGYRO_Z)
{

  uint8_t data_buf[6];

  mpu6050_twi_read(MPU6050_RA_GYRO_XOUT_H, data_buf, sizeof(data_buf));

  *pGYRO_X = (data_buf[0] << 8) | data_buf[1];
  *pGYRO_Y=  (data_buf[2] << 8) | data_buf[3];
  *pGYRO_Z = (data_buf[4] << 8) | data_buf[5];

  return NRF_SUCCESS;
}

bool mpu6050_ReadTemp(int16_t *pTemp)
{

  uint8_t data_buf[2];

  mpu6050_twi_read(MPU6050_RA_TEMP_OUT_H, data_buf, sizeof(data_buf));

  *pTemp = (data_buf[0] << 8) | data_buf[1];

  return NRF_SUCCESS;
}

bool mpu6050_who_am_i(uint8_t *who)
{

  mpu6050_twi_read(MPU6050_RA_WHO_AM_I, who, sizeof(who));

  return NRF_SUCCESS;
}

bool mpu6050_setACCRange(mpu6050_acc_range pConfig)
{

  mpu6050_twi_write(MPU6050_RA_ACCEL_CONFIG, pConfig << 3);

  return NRF_SUCCESS;
}

bool mpu6050_setGYRORange(mpu6050_gyro_range pConfig)
{

  mpu6050_twi_write(MPU6050_RA_GYRO_CONFIG, pConfig << 3);

  return NRF_SUCCESS;
}

bool mpu6050_WakeUp(void)
{

  mpu6050_twi_write(MPU6050_RA_PWR_MGMT_1, 0x00);
  nrf_delay_ms(30);

  return NRF_SUCCESS;
}

bool mpu6050_Sleep(void)
{

  mpu6050_twi_write(MPU6050_RA_PWR_MGMT_1, (1 << MCP6050_SLEEP));

  return NRF_SUCCESS;
}