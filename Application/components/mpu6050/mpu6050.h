#ifndef MPU6050_H__
#define MPU6050_H__


//MPU6050 Registers addresses, see datasheet for more info and each register's function
#define MPU_SELF_TESTX_REG		0x0D	
#define MPU_SELF_TESTY_REG		0x0E	
#define MPU_SELF_TESTZ_REG		0x0F	
#define MPU_SELF_TESTA_REG		0x10	
#define MPU_SAMPLE_RATE_REG		0x19	
#define MPU_CFG_REG                     0x1A	
#define MPU_GYRO_CFG_REG		0x1B	
#define MPU_ACCEL_CFG_REG		0x1C	
#define MPU_MOTION_DET_REG		0x1F	
#define MPU_FIFO_EN_REG			0x23	
#define MPU_I2CMST_CTRL_REG		0x24	
#define MPU_I2CSLV0_ADDR_REG            0x25	
#define MPU_I2CSLV0_REG			0x26	
#define MPU_I2CSLV0_CTRL_REG            0x27	
#define MPU_I2CSLV1_ADDR_REG            0x28	
#define MPU_I2CSLV1_REG			0x29	
#define MPU_I2CSLV1_CTRL_REG            0x2A	
#define MPU_I2CSLV2_ADDR_REG            0x2B	
#define MPU_I2CSLV2_REG			0x2C	
#define MPU_I2CSLV2_CTRL_REG            0x2D	
#define MPU_I2CSLV3_ADDR_REG            0x2E	
#define MPU_I2CSLV3_REG			0x2F	
#define MPU_I2CSLV3_CTRL_REG            0x30	
#define MPU_I2CSLV4_ADDR_REG            0x31	
#define MPU_I2CSLV4_REG			0x32	
#define MPU_I2CSLV4_DO_REG		0x33	
#define MPU_I2CSLV4_CTRL_REG            0x34	
#define MPU_I2CSLV4_DI_REG		0x35	


#define MPU_PWR_MGMT1_REG		0x6B	
#define MPU_PWR_MGMT2_REG		0x6C	

#define MPU_I2CMST_STA_REG		0x36	
#define MPU_INTBP_CFG_REG		0x37	
#define MPU_INT_EN_REG			0x38	
#define MPU_INT_STA_REG			0x3A	

#define MPU_I2CMST_DELAY_REG            0x67	
#define MPU_SIGPATH_RST_REG		0x68	
#define MPU_MDETECT_CTRL_REG            0x69	
#define MPU_USER_CTRL_REG		0x6A	
#define MPU_PWR_MGMT1_REG		0x6B	
#define MPU_PWR_MGMT2_REG		0x6C	
#define MPU_FIFO_CNTH_REG		0x72	
#define MPU_FIFO_CNTL_REG		0x73	
#define MPU_FIFO_RW_REG			0x74	
#define MPU_DEVICE_ID_REG		0x75	

#endif