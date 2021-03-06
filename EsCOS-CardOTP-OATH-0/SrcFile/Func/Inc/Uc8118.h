#include "REG_Z8D16R_2.h"
#include "typedefine.h"
#include "scufunc.h"

#define EPD_SPI_BUSY 			((IOMP1DIN&0x80) == 0x80?1:0) // GPIO15<-->BUSY 

#define EPD_SPI_SHD_N_OUT_EN()	{IOMP0DIR|=(0x01<<7);}
#define EPD_SPI_RST_N_OUT_EN()	{IOMP0DIR|=(0x01<<3);}
#define EPD_SPI_SDA_OUT_EN()	{IOMP1DIR|=(0x01);}
#define EPD_SPI_SCL_OUT_EN()	{IOMP1DIR|=(0x01<<1);}
#define EPD_SPI_CSB_OUT_EN()	{IOMP1DIR|=(0x01<<6);}


#define EPD_SPI_SDA_IN_EN()		{IOMP1DIR&=~(0x01);}
#define EPD_SPI_SCL_IN_EN()		{IOMP1DIR&=~(0x01<<1);}
#define EPD_SPI_BUSY_IN_EN()	{IOMP1DIR&=~(0x01<<7);}


#define EPD_SPI_SHD_N_PU_EN()	{IOMP0PU|=(0x01<<7);}   
#define EPD_SPI_RST_N_PU_EN()	{IOMP0PU|=(0x01<<3);}
#define EPD_SPI_SDA_PU_EN()		{IOMP1PU|=(0x01);}
#define EPD_SPI_SCL_PU_EN()		{IOMP1PU|=(0x01<<1);}
#define EPD_SPI_CSB_PU_EN()		{IOMP1PU|=(0x01<<6);}		

#define EPD_SPI_SHD_N_LOW()		{IOMP0DOUT&=~(0x01<<7);} // GPIO7<-->SHD LOW 
#define EPD_SPI_SHD_N_HIGH()	{IOMP0DOUT|=(0x01<<7);}	// GPIO7<-->SHD HIGH

#define EPD_SPI_RST_N_LOW()		{IOMP0DOUT&=~(0x01<<3);} // GPIO3<-->RST LOW
#define EPD_SPI_RST_N_HIGH()	{IOMP0DOUT|=(0x01<<3);}	// GPIO3<-->RST HIGH

#define EPD_SPI_SDA_LOW()		{IOMP1DOUT&=~(0x01);} 	// GPIO8<-->SDA LOW
#define EPD_SPI_SDA_HIGH()		{IOMP1DOUT|=(0x01);}	// GPIO8<-->SDA HIGH

#define EPD_SPI_SCL_LOW()		{IOMP1DOUT&=~(0x01<<1);} // GPIO9<-->SCL LOW
#define EPD_SPI_SCL_HIGH()		{IOMP1DOUT|=(0x01<<1);}	// GPIO9<-->SCL HIGH

#define EPD_SPI_CSB_LOW()		{IOMP1DOUT&=~(0x01<<6);} // GPIO14<-->CSB LOW
#define EPD_SPI_CSB_HIGH()		{IOMP1DOUT|=(0x01<<6);}	// GPIO14<-->CSB HIGH





void driver_delay_xms(UINT8 xms);
void SPI_Delay(unsigned long xrate);
void SPI_Write(unsigned char value);
void EPD_W21_Write_CMD_DATA(int dc,unsigned char command);
void EPD_W21_Init(void);
void SPI_Init(void);

void display(void);	
void LUT_spi_write_bb_ww(void);
void LUT_spi_write_bb_ww_vcom(void);
void LUT_spi_write_bb_ww_b(void);
void LUT_spi_write_bb_ww_w(void);
void LUT_spi_write_wb_bw(void);
void LUT_spi_write_wb_bw_vcom(void);
void LUT_spi_write_wb_bw_b(void);
void LUT_spi_write_wb_bw_w(void);
void poweroff_sleep(void);
void UC8118_SETTING(void);
void LUT_spi_write(unsigned char k);

void vPaper_String_Display(UINT8 cString[],UINT8 cLen);
void Paper_All_Clear(void);
void ElcPaper_Init(void);

