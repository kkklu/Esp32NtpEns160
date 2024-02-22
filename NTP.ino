#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

//#include <Adafruit_SSD1306.h>

#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <esp_wifi.h>

//#include <wifi.h>

// This example just provide basic function test;
// For more informations, please vist www.heltec.cn or mail to support@heltec.cn

 #include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
 #include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
 #include "time.h"

//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA -- GPIO4
//OLED_SCL -- GPIO15
//OLED_RST -- GPIO16

 

const char* ssid ="kkklu";//"WXzhdtjt875";
const char* password="12345678";//"zhdtjt875";
struct tm timeinfo;
struct tm SZtimeinfo;
SSD1306  display(0x3c, 4, 15);

#define NTP1 "192.168.21.211"
#define NTP3 "ntp3.aliyun.com"
//HardwareSerial myserial(2);

/*
unsigned int intToBCD(int );

void tmToSZformat(const tm & timeinfo,tm & SZtimeinfo) //SZtimeinfo * toSZformat
{
       
    SZtimeinfo.tm_sec= intToBCD(timeinfo.tm_sec);
    SZtimeinfo.tm_min=intToBCD(timeinfo.tm_min);
    SZtimeinfo.tm_hour=intToBCD(timeinfo.tm_hour);
    SZtimeinfo.tm_mday=intToBCD(timeinfo.tm_mday);
    SZtimeinfo.tm_mon=intToBCD(timeinfo.tm_mon);
    SZtimeinfo.tm_year=intToBCD(timeinfo.tm_year-100); //自1900年起的年数
    SZtimeinfo.tm_wday=intToBCD(timeinfo.tm_wday); //一周算起的第几天 0-6
   
   
}

unsigned int intToBCD(int s)
{
 unsigned int tmp=0;
 switch(s)
 {
  case 0:
   tmp=0xFF;
   break;
  case 1:
   tmp=0xFD;
   break;
  case 2:
   tmp=0xFB;
   break;
  case 3:
   tmp=0xF9;
   break;
  case 4:
   tmp=0xF7;
   break;
  case 5:
   tmp=0xF5;
   break;
  case 6:
   tmp=0xF3;
   break;
  case 7:
   tmp=0xF1;
   break;
  case 8:
   tmp=0xEF;
   break;
  case 9:
   tmp=0xED;
   break;
  case 10:
   tmp=0xDF;
   break;
  case 11:
   tmp=0xDD;
   break;
  case 12:
   tmp=0xDB;
   break;
  case 13:
   tmp=0xD9;
   break;
  case 14:
   tmp=0xD7;
   break;
  case 15:
   tmp=0xD5;
   break;
  case 16:
   tmp=0xD3;
   break;
  case 17:
   tmp=0xD1;
   break;
  case 18:
   tmp=0xCF;
   break;
  case 19:
   tmp=0xCD;
   break;
  case 20:
   tmp=0xBF;
   break;
  case 21:
   tmp=0xBD;
   break;
  case 22:
   tmp=0xBB;
   break;
  case 23:
   tmp=0xB9;
   break;
  case 24:
   tmp=0xB7;
   break;
  case 25:
   tmp=0xB5;
   break;
  case 26:
   tmp=0xB3;
   break;
  case 27:
   tmp=0xB1;
   break;
  case 28:
   tmp=0xAF;
   break;
  case 29:
   tmp=0xAD;
   break;
  case 30:
   tmp=0x9F;
   break;
  case 31:
   tmp=0x9D;
   break;
  case 32:
   tmp=0x9B;
   break;
  case 33:
   tmp=0x99;
   break;
  case 34:
   tmp=0x97;
   break;
  case 35:
   tmp=0x95;
   break;
  case 36:
   tmp=0x93;
   break;
  case 37:
   tmp=0x91;
   break;
  case 38:
   tmp=0x8F;
   break;
  case 39:
   tmp=0x8D;
   break;
  case 40:
   tmp=0x7F;
   break;
  case41:
    tmp=0x7D;
   break;  
  case 42:
   tmp=0x7B;
   break;  
  case 43:
   tmp=0x79;
   break;  
  case 44:
   tmp=0x77;
   break;  
  case 45:
   tmp=0x75;
   break;  
  case 46:
   tmp=0x73;
   break;  
  case 47:
   tmp=0x71;
   break;  
  case 48:
   tmp=0x6F;
   break;  
  case 49:
   tmp=0x6D;
   break;  
  case 50:
   tmp=0x5F;
   break;  
  case 51:
   tmp=0x5D;
   break;  
  case 52:
   tmp=0x5B;
   break;  
  case 53:
   tmp=0x59;
   break;  
  case 54:
   tmp=0x57;
   break;  
  case 55:
   tmp=0x55;
   break;  
  case 56:
   tmp=0x53;
   break;  
  case 57:
   tmp=0x51;
   break;  
  case 58:
   tmp=0x4F;
   break;  
  case 59:
   tmp=0x4D;
   break;
  default: tmp=0;break;
  }
 //std::cout<<"tmp="<<tmp<<std::endl;
 return tmp;
}
*/
void setup() {
  Serial.begin(115200);
  //myserial.begin(115200,SERIAL_8N1,16,17); //效果跟Serial2一样
  Serial2.begin(4800);
 
  // put your setup code here, to run once:
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
  delay(50);

  display.init();
  //display.flipScreenVertically();
  display.setContrast(255);


  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);
 
configTime(60*60*8,-30,NTP3,"ntp1,aliyun.com","ntp2.aliyun.com");
while(!getLocalTime(&timeinfo))delay(10);


  Serial.println("Connected success!");
  Serial.println(WiFi.localIP()); //显示wifi的ip
 /*
  display.setLogBuffer(5, 30);
  display.println("Connected success!");
  display.drawLogBuffer(0, 0);
  display.display();
  delay(1000);
  display.clear();
 */

}

void loop() {
  // put your main code here, to run repeatedly:

//  Serial.println("Connected success!");
  /*************初始化变量***********/
  wl_status_t wifiInfo;
  char header=0xAA,end=0x00;
  //char  cHeader=0x9B;//0x9B;
  //char date[8]={00,23,05,31,3,20,8,11};//{0xB9, 0xF5,0xAD,0xFD};
/***************get local time**********************/
 if(getLocalTime(&timeinfo))
 {
   Serial.println(&timeinfo,"%A,%Y-%m-%d %H:%M:%S");
   Serial.println(timeinfo.tm_sec);
 
  //=========按青岛时钟的格式通过serial2发送到PC，一共9个字符========//
  //tmToSZformat(timeinfo,SZtimeinfo);
  //Serial2.println(&timeinfo,"%Y-%m-%d %H:%M:%S");

   Serial2.print(header);
   Serial2.print(end); //0x00
   Serial2.print((char)(timeinfo.tm_year-88));
   Serial2.print((char)(timeinfo.tm_mon+1));
   //Serial2.print(&timeinfo,"%m");
   Serial2.print((char)timeinfo.tm_mday);
   Serial2.print((char)timeinfo.tm_wday);
    /*
    Serial2.print(date[0]);
    Serial2.print(date[1]);
    Serial2.print(date[2]);
    Serial2.print(date[3]);
    Serial2.print(date[4]);
    Serial2.print(date[5]);
    Serial2.print(date[6]);
    Serial2.print(date[7]);
    */
   //Serial2.print(&timeinfo,"%S");

  Serial2.print((char)(timeinfo.tm_hour+8),DEC);
  Serial2.print((char)timeinfo.tm_min,DEC);
  Serial2.print((char)timeinfo.tm_sec,DEC);
  


   delay(450);
 
 }
 else
 {
   Serial.println("fail to get ntp server");
 }

/**************查询wifi状态 lost后reconnect*********/
  display.setLogBuffer(5, 30);
  if(WiFi.status()==WL_CONNECTED)
  {

  display.println("wifi connected! ");
  Serial.println("wifi connected!");
  }
  else
  {
    wifiInfo=WiFi.status();//wifiInfo=WiFi.begin(ssid,password);
    WiFi.disconnect();
    WiFi.begin(ssid,password);
    WiFi.reconnect();
    display.println("wifi lost!");
    Serial.println("wifi lost");
    Serial.println(wifiInfo);  
    delay(2000);
  }
  /***************显示时间*************************************/
  display.drawLogBuffer(0, 0);
  //display.display();
  // delay(1000);
  //display.clear();
  display.print("Date:");
  display.println(&timeinfo,"%A,%Y-%m-%d");
  display.drawLogBuffer(0, 1);

  display.print("Time:");
  display.println(&timeinfo, "%H:%M:%S");
  display.drawLogBuffer(0, 2);
 
  display.display();
  delay(500);
  display.clear();

}