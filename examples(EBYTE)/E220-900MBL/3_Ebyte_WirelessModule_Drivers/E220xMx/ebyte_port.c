/**
  **********************************************************************************
  * @file      ebyte_port.h
  * @brief     EBYTE�������Ӳ���ӿڲ� �ɿͻ��Լ��ṩIO�ӿ�    
  * @details   ������μ� https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-13     
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
#include "ebyte_port.h"


/*= !!!����Ŀ��Ӳ��ƽ̨ͷ�ļ� =======================================*/

/*==================================================================*/

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨SPI�ӿ��շ����� 
 * 
 * @param send EBYTE�������ϲ������Ҫ��������� 1 Byte 
 * @return SPI���յ����� 1 Byte
 * @note ��Ŀ��ƽ̨����Ӳ��SPI_NSSʱ�������� ebyte_conf.h�ļ� �ر���������������SPI_CS(NSS)
 *       ��Ŀ��ƽ̨�������SPI_NSSʱ������������� Ebyte_Port_SpiCsIoControl() ��������ĺ���˵��
 */
uint8e_t Ebyte_Port_SpiTransmitAndReceivce( uint8e_t send )
{
    uint8e_t result = 0;
    
    /* !�����ṩ: SPI�ӿ� */

    
    return result;
}

/* !
 * @brief (��ѡ)����Ŀ��Ӳ��ƽ̨SPI_CS(NSS)���� 
 * 
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����CS(NSS)��������͵�ƽ�߼��ź� EBYTEģ��SPI�ӿ�Ϊ�͵�ƽѡ��
 *            @arg 1: ����CS(NSS)��������ߵ�ƽ�߼��ź�
 * @note ��Ŀ��ƽ̨����Ӳ��SPI_NSSʱ���������ļ����� �˺�������Ч
 *       ��Ŀ��ƽ̨�������SPI_NSSʱ�������ô˺���
 */
void Ebyte_Port_SpiCsIoControl( uint8e_t cmd )
{
    if ( cmd == 1 )
    {
       /* !��ѡ: SPI CS���� E22xx�ߵ�ƽδѡ�� */  

    }
    else
    {
       /* !��ѡ: SPI CS���� E22xx�͵�ƽѡ�� */  

    }
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨��λ���� NRST ���ƺ��� 
 * 
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����NRST ��������͵�ƽ�߼��ź� 
 *            @arg 1: ����NRST ��������ߵ�ƽ�߼��ź�
 * @note EBYTEģ��NRSTΪ�͵�ƽ��λ
 */
void Ebyte_Port_RstIoControl( uint8e_t cmd )
{
    if ( cmd == 1 )
    {
        /* !�����ṩ: NRST����IO ����ߵ�ƽ */
 
    }
    else
    {
        /* !�����ṩ: Ŀ��Ӳ����·��ӦNRST����IO ����͵�ƽ */
      
    }
}

/* !
 * @brief (��ѡ)����Ŀ��Ӳ��ƽ̨����ʹ������ TXEN ���ƺ��� 
 * 
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����TXEN ��������͵�ƽ�߼��ź� 
 *            @arg 1: ����TXEN ��������ߵ�ƽ�߼��ź� 
 * @note EBYTEģ��TXENΪ�ߵ�ƽ��Ч
 *       ��Ŀ��ƽ̨����ģ��DIO2�Զ�����TXENʱ���˺�������Ч
 */
void Ebyte_Port_TxenIoControl( uint8e_t cmd )
{
    if ( cmd == 1 )
    {
        /* !��ѡ: Ŀ��Ӳ����·��ӦTXEN����IO ����ߵ�ƽ */

    }
    else
    {
        /* !��ѡ: Ŀ��Ӳ����·��ӦTXEN����IO ����͵�ƽ */
  
    }
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨����ʹ������ RXEN ���ƺ��� 
 * 
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����RXEN��������͵�ƽ�߼��ź� 
 *            @arg 1: ����RXEN��������ߵ�ƽ�߼��ź� 
 * @note EBYTEģ��RXENΪ�ߵ�ƽ��Ч
 */
void Ebyte_Port_RxenIoControl( uint8e_t cmd )
{
    if ( cmd == 1 )
    {
        /* !�����ṩ: Ŀ��Ӳ����·��ӦRXEN����IO ����ߵ�ƽ */
     
    }
    else
    {
        /* !�����ṩ: Ŀ��Ӳ����·��ӦRXEN����IO ����͵�ƽ */
     
    }
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨����ʹ������ BUSY ���ƺ��� 
 * 
 * @note EBYTEģ��BUSYΪ�ߵ�ƽ��ʾæ
 */
uint8e_t Ebyte_Port_BusyIoRead( void )
{
    uint8e_t result = 0 ;  
    
    /* !�����ṩ: Ŀ��Ӳ����·��ӦBUSY IO ״̬��ȡ */

    return result;
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨��ʱ����
 * 
 * @param time ������ʱ���� 
 * @note ��ע��ʱ��ģ���ʼ��ʱ�����ô˺�������ע���ж��Ƿ��Ӱ�쵽�˺���
 */
void Ebyte_Port_DelayMs( uint16e_t time )
{
    /* !�����ṩ: ��ʱ���� */
  

}



