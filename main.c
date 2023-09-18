
#include "string.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "delay.h"

static int datasend_count = 0;

/********************��""����Ķ�����"���ű�ɾ******************************/
#define USERNAME  "q4MRW978Iv" //��Ʒid
#define CLIENTID   "stm32_to_onenet" //�豸����
#define PASSWORD  "version=2018-10-31&res=products%2Fq4MRW978Iv%2Fdevices%2Fstm32_to_onenet&et=1696006861&method=md5&sign=6hhEwHu5EQkmpCyWljfXYQ%3D%3D"
#define WIFINAME  "KKSK"  //WiFi������
#define WIFIPASSWORD "20032112" //WiFi������
#define IDENTIFIER1   "Current"    //��ʶ��
#define IDENTIFIER2   "Temp"    //��ʶ��
#define IDENTIFIER3   "Vdianya"    //��ʶ��
#define IDENTIFIER4   "alive"    //��ʶ��
#define IDENTIFIER5   "hum"    //��ʶ��
#define BUFFSIZE   300     //buff��size
float Temp = 34.23;  //�¶ȣ��Լ����¶ȵı����Ͱ����桰temp);		//����ָ���temp�����Լ����¶ȱ��������Ǳ�����float����
float Current = 23.12; /***************�������Լ�����ı���*************************/
float Vdianya = 24.12;
float alive = 32.14;
float hum = 27.16;
uint8_t str_buff[BUFFSIZE] ;
int size = 0;
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	SysTick_Init(72);
  USART1_Init(115200);//���ڲ�����115200
  delay_ms(1000);
//�����ǳ�ʼ��
//---------------------------------------------------------
//����ָ���ESP8266���ӵ�������

	printf("AT+RST\r\n");		//��һ��		��λ		ֻ��һ��
	delay_ms(1000);					//�ӳ�			
	
	printf("AT+CWMODE=1\r\n");		//�ڶ���		ģʽ  ֻ��һ��
	delay_ms(1000);					//�ӳ�

	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFINAME,WIFIPASSWORD);		//������
	delay_ms(3000);					//�ӳ�

	printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",USERNAME,PASSWORD);		//���岽
	delay_ms(3000);					//�ӳ�			

	printf("AT+MQTTCLIENTID=0,\"%s\"\r\n",CLIENTID);		//������
	delay_ms(3000);					//�ӳ�	
	
	printf("AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1\r\n");		//���߲�
	delay_ms(3000);					//�ӳ�

    sprintf((char*)str_buff,"{\"id\":\"1694417136065\",\"version\":\"1.0\",\"params\":{\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f},\"%s\":{\"value\":%.2f}}}",IDENTIFIER1,Current,IDENTIFIER2,Temp,IDENTIFIER3,Vdianya,IDENTIFIER4,alive,IDENTIFIER5,hum);
    size = strlen((char*)str_buff); // ��ȡ�ַ�ռ�õĴ�С
    delay_ms (2000);
    printf("AT+MQTTPUBRAW=0,\"$sys/%s/%s/thing/property/post\",%d,1,0\r\n",USERNAME,CLIENTID,size);
    delay_ms (2000);
    printf("%s",str_buff);
 

	while(1)
	{
/***********************�ַ����ַ�����256***********************/
//    datasend_count++;
//    if(datasend_count >= 3000)
//{
//	printf("AT+MQTTPUB=0,\"$sys/%s/%s/thing/property/post\",\"{\\\"id\\\":\\\"1694331119009\\\"\\,\\\"version\\\":\\\"1.0\\\"\\,\\\"params\\\":{\\\"%s\\\":{\\\"value\\\":%.1f}}}\",1,0\r\n",USERNAME,CLIENTID,IDENTIFIER,Temp);		//����ָ��
//  delay_ms(1000);
//  datasend_count = 0;
//}
//  delay_ms (1);
/***********************�ַ����ַ�����256***********************/                                                                                                                                                                                                                                                                                         

	}
}


//��һ��		AT+RST
// 
//�ڶ���		AT+CWMODE=1

//������		AT+CIPSNTPCFG=1,8,"ntp1.aliyun.com"

//���Ĳ�		AT+CWJAP="WiFi����","WiFi����"

//���岽		AT+MQTTUSERCFG=0,1,"NULL","�û���","����",0,0,""

//������		AT+MQTTCLIENTID=0,"ClienId"    					//clientId�ڶ�������ע��ÿ������ǰ�ӷָ���\

//���߲�		AT+MQTTCONN=0,"��������",1883,1

//AT+MQTTSUB=0,"topic",1							//����ָ��

//AT+MQTTPUB=0,"topic","AJson��ʽ����",1,0		//����ָ��


//ע�⣺   "ǰ��Ҫ��ת���ַ�    \ǰ��Ҫ��ת���ַ�
