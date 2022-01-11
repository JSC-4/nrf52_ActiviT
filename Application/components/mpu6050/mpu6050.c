#include "mpu6050.h"
#include "nrf_drv_twi.h"
#include <stdbool.h>
#include <stdio.h>

/* TWI instance ID. */
#define TWI_INSTANCE_ID 0

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

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
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
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

  err_code = nrf_drv_twi_tx(&m_twi, MPU6050_ADDRESS, tx_buf, sizeof(tx_buf), false);
  APP_ERROR_CHECK(err_code);

  while (m_xfer_done == false)
    ;

  return NRF_SUCCESS;
}

bool mpu6050_twi_read(uint8_t register_address, const uint8_t value) {
  ret_code_t err_code;
  m_xfer_done = false;

  err_code = nrf_drv_twi_tx(&m_twi, MPU6050_ADDRESS, register_address, 1, true);
  APP_ERROR_CHECK(err_code);

  while (m_xfer_done == false)
    ;

  if (NRF_SUCCESS != err_code) {
    return false;
  }

  return NRF_SUCCESS;
}

bool mpu6050_init(void) {

  return NRF_SUCCESS;
}