/**
  **********************************************************************************
  * @file      board_ebyte_E22xx.h
  * @brief     E49 ϵ�� ������     
  * @details   ������μ� https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-08     
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
#include "ebyte_conf.h"
#include "ebyte_callback.h"

/**
 * @note E49x ��ƵоƬ��ЧƵ�α�
 *              758MHz-840MHz  840MHz-1020MHz 
 *              379MHz-420MHz  420MHz-510MHz
 *              252.67MHz-280MHz  280MHz-340MHz 
 *              189.5MHz-210MHz   210MHz-255MHz 
 *              126.33MHz-140MHz  140MHz-170MHz 
 *
 * @note ֧��E49-400M20 E49-900M20
 */
    
#if defined(EBYTE_E49_400M20S )
/* �� 379.000 MHz��Ϊ����Ƶ�� */
   

#elif defined(EBYTE_E49_900M20S)

#endif

void Ebyte_E49x_Init( void );
void Ebyte_E49x_SendPayload( uint8e_t *payload, uint8e_t size, uint32e_t timeout );
void Ebyte_E49x_IntOrPollTask( void );
void Ebyte_E49x_SetRx( uint32e_t timeout );
    void Ebyte_E49x_InterruptTrigger( void );