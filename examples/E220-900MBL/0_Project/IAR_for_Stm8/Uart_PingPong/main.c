/**
  **********************************************************************************
  * @file      main.c
  * @brief     E15-EVB02 ������̼�
  * @details   ������Ϊ: ��������͸��ʾ��  ������μ� https://www.ebyte.com/
  * @author    JiangHeng
  * @date      2021-05-06
  * @version   1.0.0
  **********************************************************************************
  * @copyright BSD License
  *            �ɶ��ڰ��ص��ӿƼ����޹�˾
  *   ______   ____   __     __  _______   ______
  *  |  ____| |  _ \  \ \   / / |__   __| |  ____|
  *  | |__    | |_) |  \ \_/ /     | |    | |__
  *  |  __|   |  _ <    \   /      | |    |  __|
  *  | |____  | |_) |    | |       | |    | |____
  *  |______| |____/     |_|       |_|    |______|
  *
  **********************************************************************************
  */

#include "ebyte_core.h"
#include "ebyte_kfifo.h"
#include "ebyte_debug.h"
    
void Task_Transmit( void );
void Task_Button( void );

/* ���� ���ݴ洢���� */
Ebyte_FIFO_t hfifo;

/* ���� ֡������ɱ�ʶ */
uint8_t Uart_isRecvReady = 0;

/* ���� FIFO����ʶ */
uint8_t FIFO_isTimeCheckReady = 0;

/* ���� �Զ�����/������ */
uint8_t TxBuffer[64] = {0};
uint8_t RxBuffer[64] = {0};
uint8_t PcEchoBuffer[20] = {0};

uint8_t BufferPing[5] = {'p', 'i', 'n', 'g'};
uint8_t BufferPong[5] = {'p', 'o', 'n', 'g'};

/* ���� FIFO����ʶ */
uint8_t Callback_isPingCheckReady = 0;

/* �Լ�ģʽ ��ʶ */
uint8_t PC_isConnected = 0;

static BSP_BTN_EVENT_t BTN_Event;


/* !
 * @brief ������
 */
int main( void )
{
    /* ����Ӳ����Դ ��ʼ�� */
    Ebyte_BSP_Init();

    /* (��ѡ) �����жϽ���FIFO �ɸ�����Ҫ���д��� */
    Ebyte_FIFO_Init( &hfifo, EBYTE_FIFO_SIZE );

    /* EBYTE ����ģ���ʼ�� */
    Ebyte_RF.Init();

    /* MCU ��ȫ���ж� */
    Ebyte_BSP_GlobalIntEnable();

    DEBUG( "Start PingPong.....\r\n" );
    DEBUG( "Please push button1 or button2.....\r\n" );
    
    while( 1 )
    {
        /* �����¼���Ӧ */
        Task_Button();

        /* ����:��⴮�����ݲ����߷��� �ͻ��밴���Զ��� */
        Task_Transmit();

        /* ����:EBYTE��������������ִ������  �ͻ������޸� */
        Ebyte_RF.StartPollTask();
       
    }

}

/* !
 * @brief  ��ѯ���� ���ڽ��յ�����ͨ��ģ�鷢��
 *
 * @note ����ͻ�����Ҫ���͵����ݽ����������������Ҫ���Ƕ�������ߴ��俪��
 *       ע������ģ���ģʽ�л���һ������¿��Դ��ڽ���/����/��������  ��ʾ������Ϊ: ����ģʽ->����ģʽ->����ģʽ
 */
void Task_Transmit( void )
{
    uint16_t length = 0;
    uint8_t pcEchoLength = 0;
    uint8_t pongLength = 0;

    /* �Ƿ���������Ҫ���ߴ��� (���Դ��ڽ���FIFO����) */
    Ebyte_FIFO_GetDataLength( &hfifo, &length );

    /* �漰���첽�ж�,�����ʾ�� �ж���������
       1; ����FIFO�����������Ѿ����������յ�֡����ʱ�������߷���( ����ʱ���֡��ʽ,��������ʱ�����ж�ʱ��ᵼ������ճ�� ����ݾ�����Ŀ���п���֡�ж� )
       2: ����FIFO�������ݵ������Ѿ��˳��˽���״̬����ʱ����������� ( �ᵼ��FIFOʣ��δ�������ݱ�������߷��� ����ݾ�����Ŀ���п���֡�ж� )*/
    if( ( length != 0 && Uart_isRecvReady ) || ( length != 0 && FIFO_isTimeCheckReady ) )
    {
        Ebyte_BSP_LedControl( BSP_LED_1, ON );

        /* ��ȡFIFO ���ݷ���TxBuffer */
        Ebyte_FIFO_Read( &hfifo, TxBuffer, length );

        /* PC����ָ����Ӧ */
        if( Ebyte_DEBUG_CommandEcho( TxBuffer,length, PcEchoBuffer, &pcEchoLength ) )
        {
            Ebyte_BSP_UartTransmit( PcEchoBuffer , pcEchoLength); 
        }
        /* ������ָ��������͸�� */
        else
        {
            /* ��������ģ����з���  */
            Ebyte_RF.Send( TxBuffer, length, 0 );

            /* ��������ģ��������� */
            Ebyte_RF.EnterReceiveMode( 0 );          
        }
        
        /* ÿ����һ֡�ͼ���֡���� �����жϿ����Ѿ�д���˶�֡ */
        if( Uart_isRecvReady )  Uart_isRecvReady --;
        if( FIFO_isTimeCheckReady ) FIFO_isTimeCheckReady = 0;

        Ebyte_BSP_LedControl( BSP_LED_1, OFF );
    }
    
    /* ������ɻص�������⵽�� ping ���� �ظ� pong */
    if( Callback_isPingCheckReady )
    {   
        if( PC_isConnected )
        {
            pongLength = 5;
        }else{
            DEBUG( "\r\n Echo : pong \r\n" );
            pongLength = 4;
        }
        
        /* ��������ģ����з���  */
        Ebyte_RF.Send( BufferPong, pongLength, 0 );

        /* ��������ģ��������� */
        Ebyte_RF.EnterReceiveMode( 0 );   
        
        Callback_isPingCheckReady = 0;
    }
}

/* !
 * @brief �����¼���Ӧ
 */
void Task_Button( void )
{
    uint8_t pcEchoLength = 0;
    uint8_t pingLength = 0;
    
    if( ! Ebyte_BTN_FIFO_Pop( &BSP_BTN_FIFO, &BTN_Event ) )
    {
        switch( BTN_Event )
        {
        /* ����1 �̰� */
        case BTN_1_SHORT: 
            Ebyte_BSP_LedControl( BSP_LED_1, ON );
            
            if( PC_isConnected )
            {
               /* ֪ͨPC */
                Ebyte_DEBUG_CommandEcho( (uint8_t*)SimulatedCommandsButton1, EBYTE_CMD_PACKAGE_LENGTH , PcEchoBuffer, &pcEchoLength );
                Ebyte_BSP_UartTransmit( PcEchoBuffer , pcEchoLength); 
                BufferPing[4] = 0x01;
                pingLength = 5;
            }else
            {
                DEBUG( "\r\n Send Command : ping \r\n" );
                pingLength = 4;
            }
            
            /* ���� ping */
            Ebyte_RF.Send( BufferPing, pingLength, 0 );
            Ebyte_RF.EnterReceiveMode( 0 );
            
            Ebyte_BSP_LedControl( BSP_LED_1, OFF );
            break;
        /* ����1 ���� */    
        case BTN_1_LONG:
            Ebyte_BSP_LedControl( BSP_LED_1, TOGGLE );
            break;
        /* ����2 �̰� */     
        case BTN_2_SHORT:
            Ebyte_BSP_LedControl( BSP_LED_2, ON );
            if( PC_isConnected )
            {
               /* ֪ͨPC */
                Ebyte_DEBUG_CommandEcho( (uint8_t*)SimulatedCommandsButton2, EBYTE_CMD_PACKAGE_LENGTH , PcEchoBuffer, &pcEchoLength );
                Ebyte_BSP_UartTransmit( PcEchoBuffer , pcEchoLength); 
                BufferPing[4] = 0x02;
                pingLength = 5;
            }else
            {
                DEBUG( "\r\n Send Command : ping \r\n" );
                pingLength = 4;
            }
            
            /* ���� ping */
            Ebyte_RF.Send( BufferPing, pingLength, 0 );
            Ebyte_RF.EnterReceiveMode( 0 );
            
            Ebyte_BSP_LedControl( BSP_LED_2, OFF );  
            break;
        /* ����2 ���� */     
        case BTN_2_LONG:
            Ebyte_BSP_LedControl( BSP_LED_2, TOGGLE );
            break;
        default :
            break;
        }
    }
}

