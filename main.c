
#include "string.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "delay.h"

static int datasend_count = 0;

/********************改""里面的东西，"符号别删******************************/
#define USERNAME  "q4MRW978Iv" //产品id
#define CLIENTID   "stm32_to_onenet" //设备名称
#define PASSWORD  "version=2018-10-31&res=products%2Fq4MRW978Iv%2Fdevices%2Fstm32_to_onenet&et=1696006861&method=md5&sign=6hhEwHu5EQkmpCyWljfXYQ%3D%3D"
#define WIFINAME  "KKSK"  //WiFi的名字
#define WIFIPASSWORD "20032112" //WiFi的密码
#define IDENTIFIER1   "Current"    //标识符
#define IDENTIFIER2   "Temp"    //标识符
#define IDENTIFIER3   "Vdianya"    //标识符
#define IDENTIFIER4   "alive"    //标识符
#define IDENTIFIER5   "hum"    //标识符
#define BUFFSIZE   300     //buff的size
float Temp = 34.23;  //温度，自己有温度的变量就把下面“temp);		//订阅指令”的temp换成自己的温度变量，但是必须是float类型
float Current = 23.12; /***************以下是自己定义的变量*************************/
float Vdianya = 24.12;
float alive = 32.14;
float hum = 27.16;
uint8_t str_buff[BUFFSIZE] ;
int size = 0;
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	SysTick_Init(72);
  USART1_Init(115200);//串口波特率115200
  delay_ms(1000);
//以上是初始化
//---------------------------------------------------------
//发送指令，让ESP8266连接到阿里云

	printf("AT+RST\r\n");		//第一步		复位		只用一次
	delay_ms(1000);					//延迟			
	
	printf("AT+CWMODE=1\r\n");		//第二步		模式  只用一次
	delay_ms(1000);					//延迟

	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFINAME,WIFIPASSWORD);		//第三步
	delay_ms(3000);					//延迟

	printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",USERNAME,PASSWORD);		//第五步
	delay_ms(3000);					//延迟			

	printf("AT+MQTTCLIENTID=0,\"%s\"\r\n",CLIENTID);		//第六步
	delay_ms(3000);					//延迟	
	
	printf("AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1\r\n");		//第七步
	delay_ms(3000);					//延迟

    sprintf((char*)str_buff,"{\"id\":\"1694417136065\",\"version\":\"1.0\",\"params\":{\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f}}}",IDENTIFIER1,Current,IDENTIFIER2,Temp,IDENTIFIER3,Vdianya,IDENTIFIER4,alive,IDENTIFIER5,hum);
    size = strlen((char*)str_buff); // 获取字符占用的大小
    delay_ms (2000);
    printf("AT+MQTTPUBRAW=0,\"$sys/%s/%s/thing/property/post\",%d,1,0\r\n",USERNAME,CLIENTID,size);
    delay_ms (2000);
    printf("%s",str_buff);
 

	while(1)
	{
/***********************字符串字符少于256***********************/
//    datasend_count++;
//    if(datasend_count >= 3000)
//{
//	printf("AT+MQTTPUB=0,\"$sys/%s/%s/thing/property/post\",\"{\\\"id\\\":\\\"1694331119009\\\"\\,\\\"version\\\":\\\"1.0\\\"\\,\\\"params\\\":{\\\"%s\\\":{\\\"value\\\":%.1f}}}\",1,0\r\n",USERNAME,CLIENTID,IDENTIFIER,Temp);		//订阅指令
//  delay_ms(1000);
//  datasend_count = 0;
//}
//  delay_ms (1);
/***********************字符串字符大于256***********************/                                                                                                                                                                                                                                                                                         

	}
}


//第一步		AT+RST
// 
//第二步		AT+CWMODE=1

//第三步		AT+CIPSNTPCFG=1,8,"ntp1.aliyun.com"

//第四步		AT+CWJAP="WiFi名字","WiFi密码"

//第五步		AT+MQTTUSERCFG=0,1,"NULL","用户名","密码",0,0,""

//第六步		AT+MQTTCLIENTID=0,"ClienId"    					//clientId第二个参数注意每个逗号前加分隔符\

//第七步		AT+MQTTCONN=0,"连接域名",1883,1

//AT+MQTTSUB=0,"topic",1							//订阅指令

//AT+MQTTPUB=0,"topic","AJson格式内容",1,0		//发布指令


//注意：   "前面要加转义字符    \前面要加转义字符
