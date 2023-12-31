/**
  **********************************************************************************
  * @file      board.h
  * @brief     E15-EVB02 板级软件驱动层     
  * @details   详情请参见 https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-06     
  * @version   1.0.0     
  **********************************************************************************
  * @copyright BSD License 
  *            成都亿佰特电子科技有限公司  
  *   ______   ____   __     __  _______   ______ 
  *  |  ____| |  _ \  \ \   / / |__   __| |  ____|
  *  | |__    | |_) |  \ \_/ /     | |    | |__   
  *  |  __|   |  _ <    \   /      | |    |  __|  
  *  | |____  | |_) |    | |       | |    | |____ 
  *  |______| |____/     |_|       |_|    |______| 
  *
  **********************************************************************************
  */

#include "stm8l15x_conf.h"
#include "board_mini_printf.h"

/* 引脚配置 LED   */
#define BSP_GPIO_PORT_LED_1       GPIOC
#define BSP_GPIO_PIN_LED_1        GPIO_Pin_6

#define BSP_GPIO_PORT_LED_2       GPIOC
#define BSP_GPIO_PIN_LED_2        GPIO_Pin_5

/* 引脚配置 按键 */
#define BSP_GPIO_PORT_BUTTON_1    GPIOA
#define BSP_GPIO_PIN_BUTTON_1     GPIO_Pin_4

#define BSP_GPIO_PORT_BUTTON_2    GPIOA
#define BSP_GPIO_PIN_BUTTON_2     GPIO_Pin_5

/* 引脚配置 SPI通信接口 */
#define BSP_GPIO_PORT_SPI_NSS     GPIOB
#define BSP_GPIO_PIN_SPI_NSS      GPIO_Pin_4

#define BSP_GPIO_PORT_SPI_MOSI    GPIOB
#define BSP_GPIO_PIN_SPI_MOSI     GPIO_Pin_6

#define BSP_GPIO_PORT_SPI_MISO    GPIOB
#define BSP_GPIO_PIN_SPI_MISO     GPIO_Pin_7

#define BSP_GPIO_PORT_SPI_SCK     GPIOB
#define BSP_GPIO_PIN_SPI_SCK      GPIO_Pin_5

/* 引脚配置 通信串口 */
#define BSP_GPIO_PORT_UART_TX     GPIOA
#define BSP_GPIO_PIN_UART_TX      GPIO_Pin_2

#define BSP_GPIO_PORT_UART_RX     GPIOA
#define BSP_GPIO_PIN_UART_RX      GPIO_Pin_3

/* 引脚配置 EBYTE无线模块控制 */
/* E22 E220引脚兼容 */
#define BSP_GPIO_PORT_NRST        GPIOC
#define BSP_GPIO_PIN_NRST         GPIO_Pin_0
#define BSP_GPIO_PORT_BUSY        GPIOD
#define BSP_GPIO_PIN_BUSY         GPIO_Pin_4
#define BSP_GPIO_PORT_RXEN        GPIOC
#define BSP_GPIO_PIN_RXEN         GPIO_Pin_1
#define BSP_GPIO_PORT_TXEN        GPIOC
#define BSP_GPIO_PIN_TXEN         GPIO_Pin_2
/* E07 */
#define BSP_GPIO_PORT_E07_GDO0    GPIOC
#define BSP_GPIO_PIN_E07_GDO0     GPIO_Pin_0    
#define BSP_GPIO_PORT_E07_GDO1    GPIOD
#define BSP_GPIO_PIN_E07_GDO1     GPIO_Pin_4 
/* E10 */
#define BSP_GPIO_PORT_E10_DIO2    GPIOC
#define BSP_GPIO_PIN_E10_DIO2     GPIO_Pin_1    
#define BSP_GPIO_PORT_E10_DIO3    GPIOC
#define BSP_GPIO_PIN_E10_DIO3     GPIO_Pin_2 
#define BSP_GPIO_PORT_E10_IRQ     GPIOD
#define BSP_GPIO_PIN_E10_IRQ      GPIO_Pin_4
#define BSP_GPIO_PORT_E10_SDN     GPIOC
#define BSP_GPIO_PIN_E10_SDN      GPIO_Pin_0
/* E49 */
#define BSP_GPIO_PORT_E49_DIO1    GPIOC
#define BSP_GPIO_PIN_E49_DIO1     GPIO_Pin_1
#define BSP_GPIO_PORT_E49_DIO2    GPIOC
#define BSP_GPIO_PIN_E49_DIO2     GPIO_Pin_2
#define BSP_GPIO_PORT_E49_DIO3    
#define BSP_GPIO_PIN_E49_DIO3      
#define BSP_GPIO_PORT_E49_CSB     GPIOB
#define BSP_GPIO_PIN_E49_CSB      GPIO_Pin_4
#define BSP_GPIO_PORT_E49_FCSB    GPIOB
#define BSP_GPIO_PIN_E49_FCSB     GPIO_Pin_7
#define BSP_GPIO_PORT_E49_SDIO    GPIOB
#define BSP_GPIO_PIN_E49_SDIO     GPIO_Pin_6
#define BSP_GPIO_PORT_E49_SLCK    GPIOB
#define BSP_GPIO_PIN_E49_SLCK     GPIO_Pin_5


/* 参数配置 SPI */
#define BSP_RF_SPI                  SPI1
#define BSP_RF_SPI_CLOCK            CLK_Peripheral_SPI1
#define Ebyte_BSP_RfSpiSelected()   GPIO_WriteBit( BSP_GPIO_PORT_SPI_NSS , BSP_GPIO_PIN_SPI_NSS, RESET )
#define Ebyte_BSP_RfSpiUnselected() GPIO_WriteBit( BSP_GPIO_PORT_SPI_NSS , BSP_GPIO_PIN_SPI_NSS, SET )

/* 参数配置 无线模块控制IO */
/* E22/E220兼容 */
#define Ebyte_BSP_RfResetIoLow()  GPIO_WriteBit( BSP_GPIO_PORT_NRST , BSP_GPIO_PIN_NRST, RESET )
#define Ebyte_BSP_RfResetIoHigh() GPIO_WriteBit( BSP_GPIO_PORT_NRST , BSP_GPIO_PIN_NRST, SET )
#define Ebyte_BSP_RfTxIoDisable() GPIO_WriteBit( BSP_GPIO_PORT_TXEN , BSP_GPIO_PIN_TXEN, RESET )
#define Ebyte_BSP_RfTxIoEnable()  GPIO_WriteBit( BSP_GPIO_PORT_TXEN , BSP_GPIO_PIN_TXEN, SET )
#define Ebyte_BSP_RfRxIoDisable() GPIO_WriteBit( BSP_GPIO_PORT_RXEN , BSP_GPIO_PIN_RXEN, RESET )
#define Ebyte_BSP_RfRxIoEnable()  GPIO_WriteBit( BSP_GPIO_PORT_RXEN , BSP_GPIO_PIN_RXEN, SET ) 
/* E07 */
#define Ebyte_BSP_RfBusyIoRead()  GPIO_ReadInputDataBit( BSP_GPIO_PORT_BUSY , BSP_GPIO_PIN_BUSY)
#define Ebyte_BSP_RfGdo0IoRead()  GPIO_ReadInputDataBit( BSP_GPIO_PORT_E07_GDO0 , BSP_GPIO_PIN_E07_GDO0)
#define Ebyte_BSP_RfGdo1IoRead()  GPIO_ReadInputDataBit( BSP_GPIO_PORT_E07_GDO1 , BSP_GPIO_PIN_E07_GDO1)
/* E10 */
#define Ebyte_BSP_E10IrqIoRead()  GPIO_ReadInputDataBit( BSP_GPIO_PORT_E10_IRQ , BSP_GPIO_PIN_E10_IRQ)
#define Ebyte_BSP_E10Dio2Read()   GPIO_ReadInputDataBit( BSP_GPIO_PORT_E10_DIO2 , BSP_GPIO_PIN_E10_DIO2)
#define Ebyte_BSP_E10Dio3Read()   GPIO_ReadInputDataBit( BSP_GPIO_PORT_E10_DIO3 , BSP_GPIO_PIN_E10_DIO3)
#define Ebyte_BSP_E10SdnIoLow()   GPIO_WriteBit( BSP_GPIO_PORT_E10_SDN , BSP_GPIO_PIN_E10_SDN, RESET )
#define Ebyte_BSP_E10SdnIoHigh()  GPIO_WriteBit( BSP_GPIO_PORT_E10_SDN , BSP_GPIO_PIN_E10_SDN, SET )
/* E49 */
#define Ebyte_BSP_E49Dio1IoRead() GPIO_ReadInputDataBit( BSP_GPIO_PORT_E49_DIO1 , BSP_GPIO_PIN_E49_DIO1) 
#define Ebyte_BSP_E49Dio2IoRead() GPIO_ReadInputDataBit( BSP_GPIO_PORT_E49_DIO2 , BSP_GPIO_PIN_E49_DIO2) 
#define Ebyte_BSP_E49FcsbIoLow()  GPIO_WriteBit( BSP_GPIO_PORT_E49_FCSB , BSP_GPIO_PIN_E49_FCSB, RESET ) 
#define Ebyte_BSP_E49FcsbIoHigh() GPIO_WriteBit( BSP_GPIO_PORT_E49_FCSB , BSP_GPIO_PIN_E49_FCSB, SET ) 
#define Ebyte_BSP_E49CsbIoLow()   GPIO_WriteBit( BSP_GPIO_PORT_E49_CSB , BSP_GPIO_PIN_E49_CSB, RESET )
#define Ebyte_BSP_E49CsbIoHigh()  GPIO_WriteBit( BSP_GPIO_PORT_E49_CSB , BSP_GPIO_PIN_E49_CSB, SET ) 
#define Ebyte_BSP_E49SlckIoLow()  GPIO_WriteBit( BSP_GPIO_PORT_E49_SLCK , BSP_GPIO_PIN_E49_SLCK, RESET ) 
#define Ebyte_BSP_E49SlckIoHigh() GPIO_WriteBit( BSP_GPIO_PORT_E49_SLCK , BSP_GPIO_PIN_E49_SLCK, SET ) 
#define Ebyte_BSP_E49SdioIoLow()  GPIO_WriteBit( BSP_GPIO_PORT_E49_SDIO , BSP_GPIO_PIN_E49_SDIO, RESET ) 
#define Ebyte_BSP_E49SdioIoHigh() GPIO_WriteBit( BSP_GPIO_PORT_E49_SDIO , BSP_GPIO_PIN_E49_SDIO, SET ) 
#define Ebyte_BSP_E49SdioIoOutput()  GPIO_Init( BSP_GPIO_PORT_E49_SDIO, BSP_GPIO_PIN_E49_SDIO, GPIO_Mode_Out_PP_High_Fast )
#define Ebyte_BSP_E49SdioIoInput()   GPIO_Init( BSP_GPIO_PORT_E49_SDIO, BSP_GPIO_PIN_E49_SDIO, GPIO_Mode_In_FL_No_IT )
#define Ebyte_BSP_E49SdioIoRead()    GPIO_ReadInputDataBit( BSP_GPIO_PORT_E49_SDIO , BSP_GPIO_PIN_E49_SDIO) 
/* 全局中断 */
#define Ebyte_BSP_GlobalIntEnable()                __enable_interrupt()
#define Ebyte_BSP_GlobalIntDisable()               __disable_interrupt()

/* 参数配置 UART */
#define BSP_USER_UART             USART1
#define BSP_USER_UART_CLOCK       CLK_Peripheral_USART1
#define BSP_USER_UART_BAUDRATE    9600                  //波特率
#define BSP_USER_UART_PARITY      USART_Parity_No       //USART_Parity_No:无校验  USART_Parity_Even:奇校验  USART_Parity_Odd:偶校验     
#define BSP_USER_UART_IRQ         USART1_RX_IRQn        //中断类型
#define BSP_USER_UART_IRQ_LEVEL   ITC_PriorityLevel_2   //优先级


/* 参数配置 按键事件队列 */
#define BSP_BTN_FIFO_LENGTH       16

/* 参数配置 调试打印信息 关闭打印需要注释掉宏定义 EBYTE_DEBUG */
#define EBYTE_DEBUG   
#ifdef EBYTE_DEBUG
#define DEBUG(format, ...)  mprintf(format, ##__VA_ARGS__)  
#else
#define DEBUG(...)     
#endif
typedef enum { BSP_LED_1 = 0, BSP_LED_2 } BSP_LED_t;
typedef enum { OFF = 0, ON , TOGGLE} BSP_LED_Ctl_t;
typedef enum { UART_8N1 = 0, UART_8O1, UART_8E1 } BSP_UART_Parity_t;

typedef enum { BSP_BUTTON_1 = 0, BSP_BUTTON_2 } BSP_BUTTON_t;
typedef enum
{
    BTN_1_SHORT, //按键1 短按 
    BTN_1_LONG,	 //按键1 长按 
    BTN_2_SHORT, //按键2 短按 
    BTN_2_LONG,	 //按键2 长按 
}BSP_BTN_EVENT_t;

typedef struct
{
    uint8_t fifoLen   ;
    uint8_t fifoRead  ;
    uint8_t fifoWrite ;
    uint8_t buff[BSP_BTN_FIFO_LENGTH];
}BSP_BTN_FIFO_t;

extern BSP_BTN_FIFO_t BSP_BTN_FIFO;

void Ebyte_BSP_Init( void );
void Ebyte_BTN_FIFO_Init(BSP_BTN_FIFO_t *fifo);
void Ebyte_BSP_DelayMs( volatile uint32_t nTime );
void Ebyte_BSP_TimerDecrement(void);
void Ebyte_BSP_LedControl( BSP_LED_t LEDx , BSP_LED_Ctl_t ctl);
void Ebyte_BSP_UartTransmit( uint8_t *buffer , uint16_t length );

uint8_t Ebyte_BSP_ReadButton( BSP_BUTTON_t btn );
uint8_t Ebyte_BSP_SpiTransAndRecv( uint8_t data );

uint8_t Ebyte_BTN_FIFO_Push(BSP_BTN_FIFO_t *fifo, BSP_BTN_EVENT_t event);
uint8_t Ebyte_BTN_FIFO_Pop(BSP_BTN_FIFO_t *fifo, BSP_BTN_EVENT_t *event);
uint32_t Ebyte_BSP_TimerGetTick(void);