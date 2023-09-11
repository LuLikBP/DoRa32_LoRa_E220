/**
  **********************************************************************************
  * @file      ebyte_callback.h
  * @brief     EBYTE��������շ���ɻص����� �ɿͻ�ʵ���Լ����߼����� 
  * @details   ������μ� https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-26     
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
#include "ebyte_callback.h"

/*= !!!����Ŀ��Ӳ��ƽ̨ͷ�ļ� =======================================*/
#include "board.h"  //E15-EVB02 ������
/*= !!!����Ŀ��Ӳ������       =======================================*/
extern uint8_t RxBuffer[64];
extern uint8_t BufferPing[4];
extern uint8_t Callback_isPingCheckReady;
/*==================================================================*/



/* !
 * @brief ������ɻص��ӿ� �ɿͻ�ʵ���Լ��ķ�������߼�
 * 
 * @param state �ϲ�ص��ṩ��״̬�� �ͻ������ʾ��ע���ҵ���Ӧ����
 *  
 * @note E22x ģ����ṩ��״̬��
 *         IRQ_TX_DONE                             = 0x0001,
 *         IRQ_RX_DONE                             = 0x0002,
 *         IRQ_PREAMBLE_DETECTED                   = 0x0004,
 *         IRQ_SYNCWORD_VALID                      = 0x0008,
 *         IRQ_HEADER_VALID                        = 0x0010,
 *         IRQ_HEADER_ERROR                        = 0x0020,
 *         IRQ_CRC_ERROR                           = 0x0040,
 *         IRQ_CAD_DONE                            = 0x0080,
 *         IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
 *         IRQ_RX_TX_TIMEOUT                       = 0x0200, 
 */
void Ebyte_Port_TransmitCallback( uint16e_t state )
{       
    /* ����: ������� */
    if( state &= 0x0001 )
    {
        //To-do ʵ���Լ����߼� 
    }
    /* ����: �쳣��ʱ */
    else if ( state &= 0x0200 )
    {
        //To-do ʵ���Լ����߼� 
    }
    /* ����: δ֪���� */
    else
    {
        /* ����״̬��ʶ����ȷ��������Ӳ��  
           �������� 1:SPIͨ�Ų���ȷ 2:ģ�鹩�粻�� */
        while(1);
    }
}

/* !
 * @brief ������ɻص��ӿ� �ɿͻ�ʵ���Լ��ķ�������߼�
 * 
 * @param state �ϲ�ص��ṩ��״̬�� �ͻ������ʾ��ע���ҵ���Ӧ����
 * 
 * @note E22x ģ����ṩ��״̬��
 *         IRQ_TX_DONE                             = 0x0001,
 *         IRQ_RX_DONE                             = 0x0002,
 *         IRQ_PREAMBLE_DETECTED                   = 0x0004,
 *         IRQ_SYNCWORD_VALID                      = 0x0008,
 *         IRQ_HEADER_VALID                        = 0x0010,
 *         IRQ_HEADER_ERROR                        = 0x0020,
 *         IRQ_CRC_ERROR                           = 0x0040,
 *         IRQ_CAD_DONE                            = 0x0080,
 *         IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
 *         IRQ_RX_TX_TIMEOUT                       = 0x0200, 
 */
void Ebyte_Port_ReceiveCallback(  uint16e_t state, uint8e_t *buffer, uint8e_t length )
{
    uint8_t  i,j;
  
    /* ����: ���� */
    if( state &= 0x0002 )
    {
        
       
         
        //To-do ʵ���Լ����߼� 
        
        /* ͨ�������ж��Ƿ���ping pongָ��  */
        if( length == 4 )
        {
             uint8_t *p;
             p = buffer;
             for(j=0;j<4;j++)
             {
                 if( BufferPing[j] != *p++)
                 {
                    break;
                 }
                 
             }
             //�Ƚϵ���ĩβ��ʾ��ȫƥ��
             if( j == 4 )
             {
                Callback_isPingCheckReady = 1;
             }
        }
          
        Ebyte_BSP_LedControl( BSP_LED_1 , ON );
        
        for( i = 0; i < length; i++ )
        {
            while ( USART_GetFlagStatus( USART1, USART_FLAG_TXE ) == RESET );
            USART_SendData8( USART1, *buffer++ ); //EVB02�������
        }       
        Ebyte_BSP_LedControl( BSP_LED_1 , OFF );
    }
    /* ����: �쳣��ʱ */
    else if ( state &= 0x0200 )
    {
        //To-do ʵ���Լ����߼� 
    }
    /* ����: δ֪���� */
    else
    {
        /* ����״̬��ʶ����ȷ��������Ӳ��  
           �������� 1:SPIͨ�Ų���ȷ 2:ģ�鹩�粻�� */
        while(1);
    }
}