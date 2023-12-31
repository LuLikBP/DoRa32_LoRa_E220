/**
  **********************************************************************************
  * @file      board.c
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

#include "board.h"
#include "ebyte_conf.h"

BSP_BTN_FIFO_t BSP_BTN_FIFO;    
      

/*!< @brief 辅助延时计算 用于定时器中断 递减 */
volatile uint32_t Ebyte_TimerDelayCounter = 0;

/* !
 * @brief 内部时钟初始化
 */
void Ebyte_BSP_HSI_Init(void)
{
  /* 内部 16M HSI 时钟 */ 
  CLK_SYSCLKSourceConfig( CLK_SYSCLKSource_HSI );
  
  /* 1分频  16M/1 */
  CLK_SYSCLKDivConfig( CLK_SYSCLKDiv_1 );
}



void Ebyte_BSP_E22xE220xGPIO_Init(void)
{
    /* E22/E220 */
    GPIO_Init( BSP_GPIO_PORT_NRST, BSP_GPIO_PIN_NRST, GPIO_Mode_Out_PP_High_Slow );  //模块:低电平复位 
    GPIO_Init( BSP_GPIO_PORT_BUSY, BSP_GPIO_PIN_BUSY, GPIO_Mode_In_FL_No_IT      );  
    GPIO_Init( BSP_GPIO_PORT_RXEN, BSP_GPIO_PIN_RXEN, GPIO_Mode_Out_PP_Low_Slow  );  //模块:高电平允许接收
    GPIO_Init( BSP_GPIO_PORT_TXEN, BSP_GPIO_PIN_TXEN, GPIO_Mode_Out_PP_Low_Slow  );  //模块:高电平允许发送   
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_NRST, BSP_GPIO_PIN_NRST, ENABLE);
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_RXEN, BSP_GPIO_PIN_RXEN, ENABLE);
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_TXEN, BSP_GPIO_PIN_TXEN, ENABLE);
}

void Ebyte_BSP_E10xGPIO_Init(void)
{
    GPIO_Init( BSP_GPIO_PORT_E10_SDN, BSP_GPIO_PIN_E10_SDN, GPIO_Mode_Out_PP_High_Slow ); //E10 高电平复位
    GPIO_Init( BSP_GPIO_PORT_E10_IRQ, BSP_GPIO_PIN_E49_DIO2, GPIO_Mode_In_FL_No_IT      );  
}

void Ebyte_BSP_E49xGPIO_Init(void)
{
    GPIO_Init( BSP_GPIO_PORT_E49_DIO1, BSP_GPIO_PIN_E49_DIO1,  GPIO_Mode_In_PU_No_IT      ); 
    GPIO_Init( BSP_GPIO_PORT_E49_DIO2, BSP_GPIO_PIN_E49_DIO2,  GPIO_Mode_In_PU_IT      ); 
    EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Rising);

    
    
    GPIO_Init( BSP_GPIO_PORT_E49_CSB,  BSP_GPIO_PIN_E49_CSB,  GPIO_Mode_Out_PP_High_Fast );
    GPIO_Init( BSP_GPIO_PORT_E49_FCSB, BSP_GPIO_PIN_E49_FCSB, GPIO_Mode_Out_PP_High_Fast );
    GPIO_Init( BSP_GPIO_PORT_E49_SDIO, BSP_GPIO_PIN_E49_SDIO, GPIO_Mode_Out_PP_High_Fast );
    GPIO_Init( BSP_GPIO_PORT_E49_SLCK, BSP_GPIO_PIN_E49_SLCK, GPIO_Mode_Out_PP_Low_Fast );
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_E49_CSB, BSP_GPIO_PIN_E49_CSB, ENABLE);
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_E49_FCSB, BSP_GPIO_PIN_E49_FCSB, ENABLE);
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_E49_SLCK, BSP_GPIO_PIN_E49_SLCK, ENABLE);
}

/* !
 * @brief 初始化所有IO
 * 
 * @note  目标硬件: EBYTE E15-EVB02 
 */
void Ebyte_BSP_GPIO_Init(void)
{
    /* 无线模块状态控制 */
    
#if defined(EBYTE_E22_400M22S)||defined(EBYTE_E22_900M22S)||defined(EBYTE_E220_400M22S)||defined(EBYTE_E220_900M22S)
    Ebyte_BSP_E22xE220xGPIO_Init();
    
#elif defined(EBYTE_E10_400M20S)||defined(EBYTE_E10_900M20S)   
    Ebyte_BSP_E10xGPIO_Init();
    
#elif defined(EBYTE_E49_900M20S)
    Ebyte_BSP_E49xGPIO_Init();
     
#endif   
    /* LED */
    GPIO_Init( BSP_GPIO_PORT_LED_1, BSP_GPIO_PIN_LED_1, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init( BSP_GPIO_PORT_LED_2, BSP_GPIO_PIN_LED_2, GPIO_Mode_Out_PP_Low_Slow );   
       
    /* 按键 */
    GPIO_Init( BSP_GPIO_PORT_BUTTON_1, BSP_GPIO_PIN_BUTTON_1, GPIO_Mode_In_PU_No_IT ); 

    GPIO_Init( BSP_GPIO_PORT_BUTTON_2, BSP_GPIO_PIN_BUTTON_2, GPIO_Mode_In_PU_No_IT );     
}

/* !
 * @brief 通信串口初始化
 * 
 * @note  请注意，不同的MCU可能无需端口映射
 */
void Ebyte_BSP_UART_Init( void )
{
    /* 时钟 */
    CLK_PeripheralClockConfig( BSP_USER_UART_CLOCK, ENABLE);
    
    /* GPIO */
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_UART_TX, BSP_GPIO_PIN_UART_TX, ENABLE );
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_UART_RX, BSP_GPIO_PIN_UART_RX, ENABLE );

    /* 端口重映射  */
    SYSCFG_REMAPPinConfig( REMAP_Pin_USART1TxRxPortA, ENABLE ); 
    
    /* 基础参数配置 E15-EVB02默认波特率9600 8N1 */
    USART_Init( BSP_USER_UART, BSP_USER_UART_BAUDRATE, USART_WordLength_8b, USART_StopBits_1, BSP_USER_UART_PARITY,  (USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx ));//允许接收和发送
    
    /* 打开接收中断 */;
    USART_ITConfig( BSP_USER_UART, USART_IT_RXNE, ENABLE );
     
    /* 串口 使能 */
    USART_Cmd( BSP_USER_UART, ENABLE);
}

void Ebyte_BSP_ThreeLinesSPI_Init()
{
    /* 合并到了E49 GPIO初始化中 */
}

/* !
 * @brief 无线模块通信SPI接口初始化函数
 */
void Ebyte_BSP_SPI_Init( void )
{
    /* 时钟 */
    CLK_PeripheralClockConfig( CLK_Peripheral_SPI1, ENABLE);
    
    /* GPIO */
    GPIO_Init( BSP_GPIO_PORT_SPI_NSS,  BSP_GPIO_PIN_SPI_NSS,  GPIO_Mode_Out_PP_High_Slow); //片选 CS
    GPIO_ExternalPullUpConfig( BSP_GPIO_PORT_SPI_SCK, BSP_GPIO_PIN_SPI_MOSI | BSP_GPIO_PIN_SPI_MISO | BSP_GPIO_PIN_SPI_SCK, ENABLE); // MOSI MISO SCK   
    
    /* 参数配置 */
    SPI_Init(  BSP_RF_SPI, 
               SPI_FirstBit_MSB,                 //从高位开始传输
               SPI_BaudRatePrescaler_2,          //16M/2 SCK速率
               SPI_Mode_Master,                  //主机模式
               SPI_CPOL_Low,                     //根据 CPOL=0  
               SPI_CPHA_1Edge,                   //根据 CPHA=0  第一个时钟边沿采样数据
               SPI_Direction_2Lines_FullDuplex,  //全双工
               SPI_NSS_Soft,                     //软件控制从机CS片选
               0x07);                            //CRC参数
    
    /* 使能 */
    SPI_Cmd( BSP_RF_SPI, ENABLE );
}

/* !
 * @brief RF模块SPI通信收/发函数
 * 
 * @param data 发送数据  
 * @return 接收数据 
 * @note stm8l SPI库函数中的SPI_SendData()/SPI_ReceiveData() 不能直接使用
 */
uint8_t Ebyte_BSP_SpiTransAndRecv( uint8_t data )
{
    BSP_RF_SPI->DR = data;
    while ((BSP_RF_SPI->SR & SPI_FLAG_TXE) == RESET);
    
    while ((BSP_RF_SPI->SR & SPI_FLAG_RXNE) == RESET);
    return BSP_RF_SPI->DR;
}

/* !
 * @brief 定时器初始化
 *
 * @note  使用了TIM3产生1ms周期性中断
 *        TIM3的主时钟为HSI 16MHz, 128分频即为 16 MHz / 128 = 125 000 Hz
 *        目标定时1ms 计数周期即为 ( 0.001 x 125000 - 1) = 124 
 */
void Ebyte_BSP_TIMER_Init( void )
{
    /* 时钟 */
    CLK_PeripheralClockConfig( CLK_Peripheral_TIM3, ENABLE); 
    
    /* 参数 */
    TIM3_TimeBaseInit( TIM3_Prescaler_128 , TIM3_CounterMode_Up, 124);
    
    /* 允许中断 */
    TIM3_ClearFlag(TIM3_FLAG_Update);
    TIM3_ITConfig(TIM3_IT_Update, ENABLE);
    
    /* 使能 */
    TIM3_Cmd(ENABLE);
}       

/* !
 * @brief E15-EVB02 板载资源初始化
 * 
 * @note  内部时钟HSI  x 16MHz
 *        用户通信串口 x USART1
 *        无线模块通信接口 x SPI1
 *        定时器  x TIM3
 *        按键    x 2
 *        指示灯  x 2
 */
void Ebyte_BSP_Init( void )
{
    /* 时钟     初始化 */
    Ebyte_BSP_HSI_Init();
    
    /* IO       初始化 */
    Ebyte_BSP_GPIO_Init();
    
    /* 串口     初始化 */
    Ebyte_BSP_UART_Init();
  
    /* SPI接口  初始化  (E49比较特殊) */
#if defined(EBYTE_E49_900M20S)  
    Ebyte_BSP_ThreeLinesSPI_Init();
#else    
    Ebyte_BSP_SPI_Init();
#endif    
    
    /* 定时器   初始化 */
    Ebyte_BSP_TIMER_Init();
    
    /* 按键事件队列 初始化 */
    Ebyte_BTN_FIFO_Init( &BSP_BTN_FIFO );
    
    
    

}

/* !
 * @brief 控制LED 开/关/翻转
 * 
 * @param LEDx  板载两颗发光二极管
 *              @arg BSP_LED_1 : LED1
 *              @arg BSP_LED_2 : LED2 
 * 
 * @param ctl   开 / 关
 *              @arg OFF     : 关
 *              @arg ON      : 开  
 *              @arg TOGGLE  : 翻转 
 */
void Ebyte_BSP_LedControl( BSP_LED_t LEDx , BSP_LED_Ctl_t ctl)
{
    if( TOGGLE == ctl )
    {
      switch( LEDx )
      {
        case BSP_LED_1 : GPIO_ToggleBits( BSP_GPIO_PORT_LED_1, BSP_GPIO_PIN_LED_1); break;
        case BSP_LED_2 : GPIO_ToggleBits( BSP_GPIO_PORT_LED_2, BSP_GPIO_PIN_LED_2); break;
        default: break;
      }    
    }
    else
    {
      switch( LEDx )
      {
        case BSP_LED_1 : GPIO_WriteBit( BSP_GPIO_PORT_LED_1, BSP_GPIO_PIN_LED_1, (BitAction)ctl); break;
        case BSP_LED_2 : GPIO_WriteBit( BSP_GPIO_PORT_LED_2, BSP_GPIO_PIN_LED_2, (BitAction)ctl); break;
        default: break;
      }    
    }

}


/* !
 * @brief 基于定时器的毫秒延时函数
 * 
 * @param nTime 单位:毫秒
 */
void Ebyte_BSP_DelayMs( volatile uint32_t nTime )
{
    Ebyte_TimerDelayCounter = nTime;
    
    while( Ebyte_TimerDelayCounter !=0 );
}

/* !
 * @brief 辅助毫秒延时计算 定时器中断调用
 */
void Ebyte_BSP_TimerDecrement(void)
{

  
    if( Ebyte_TimerDelayCounter != 0 ) 
    {
        Ebyte_TimerDelayCounter--;
    }
}


/* !
 * @brief 读取按键状态
 * 
 * @param btn 对应的按键编号
 *            @arg BSP_BUTTON_1 :按键1 
 *            @arg BSP_BUTTON_2 :按键2
 * @return 0:按键被按下  非0:按键未按下 
 * @note  板载按键未按下时 IO处于上拉状态 即为1；按下后IO接地 即为0
 */
uint8_t Ebyte_BSP_ReadButton( BSP_BUTTON_t btn )
{
    BitStatus result = RESET;
    
    switch ( btn )
    {
      case BSP_BUTTON_1: result = GPIO_ReadInputDataBit( BSP_GPIO_PORT_BUTTON_1 , BSP_GPIO_PIN_BUTTON_1); break;
      case BSP_BUTTON_2: result = GPIO_ReadInputDataBit( BSP_GPIO_PORT_BUTTON_2 , BSP_GPIO_PIN_BUTTON_2); break;
      default : break;
    }
    
    return result;
}


/* !
 * @brief 串口发送函数
 */
void Ebyte_BSP_UartTransmit( uint8_t *buffer , uint16_t length )
{
  
    uint8_t i;
    
    for( i = 0; i < length; i++ )
    {
        while ( USART_GetFlagStatus( USART1, USART_FLAG_TXE ) == RESET );
        USART_SendData8( USART1, *buffer++ );
    }  
}

