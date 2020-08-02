#ifndef _ZS_ESP8266_H
#define _ZS_ESP8266_H

#include "zs_spc.h"
#include "zs_systick.h"

#define SEND_PING_DELAYS (60*200) //>>zjs:发送心跳包的间隔时长定义
#define BLINK_DEALY (100) //>>zjs:闪灯延时 100对应（100*5）ms

void EspConnectServer(void);
void RemoteControlLedTest(void);

#endif 


