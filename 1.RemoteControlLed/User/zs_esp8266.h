#ifndef _ZS_ESP8266_H
#define _ZS_ESP8266_H

#include "zs_spc.h"
#include "zs_systick.h"

#define SEND_PING_DELAYS (60*200) //>>zjs:�����������ļ��ʱ������
#define BLINK_DEALY (100) //>>zjs:������ʱ 100��Ӧ��100*5��ms

void EspConnectServer(void);
void RemoteControlLedTest(void);

#endif 


