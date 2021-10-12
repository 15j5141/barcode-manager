/*
*******************************************************************************
* Equipped with Atom-Lite/Matrix sample source code
* Visit the website for more information：https://docs.m5stack.com/en/atom/atomic_qr
*
* describe: _
* date：2021/00/00
*******************************************************************************
*/

#include <M5Atom.h>
#include <String.h>
#include "config.h"

#define TRIG 23
#define DLED 33

#define GROVE_RX 26
#define GROVE_TX 32
const char* wifi_ssid = CONFIG_WIFI_SSID;
const char* wifi_pass = CONFIG_WIFI_PASS;
int ptr = 0;

// 有線通信
void setupSerial(){
  delay(10);
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, GROVE_RX, GROVE_TX);
}

void loopSerial(String barcode){
  // LCDが読み取れたら
   if (Serial1.available()) {
    // Serial1(EXT_IO) to Serial2(Grove)
//    int inByte = Serial1.read();
    Serial1.println(barcode);
  }
}

void setup() {
  M5.begin(true, false, true);
  Serial2.begin(9600, SERIAL_8N1, 22, 19);  //Set the baud rate of serial port 2 to 115200,8 data bits, no parity bits, and 1 stop bit, and set RX to 22 and TX to 19.  设置串口二的波特率为115200,8位数据位,没有校验位,1位停止位,并设置RX为22,TX为19
//  Serial2.setTimeout(100); // readStringUntilで無理やり読み取るために小さい値をセットする.
  M5.dis.fillpix(0xfff000); //YELLOW 黄色
  pinMode(TRIG, OUTPUT);
  pinMode(DLED, INPUT);
  digitalWrite(TRIG, HIGH);
  setupSerial();
}

void loop() {
  M5.update();
  if(M5.Btn.isPressed()){
    digitalWrite(TRIG, LOW);
  }else {
    digitalWrite(TRIG, HIGH);
  }
  if(digitalRead(DLED) == HIGH){  //If read the QR code.
    M5.dis.fillpix(0xf00000); //GREEN  绿色


    int i=0;
//    char recieved_data[256];
    String recieved_data;
    // バーコード読み取り開始
    while(Serial2.available() > 0){
      int size = Serial2.available();
      recieved_data = Serial2.readStringUntil('\r');
//      char ch = Serial2.read();
//      Serial.print(ch);
//      Serial.printf("[%d]%s", size, str.c_str());
//      recieved_data[i] = (char)ch;
      i++;
//    Serial.printf("[%d]",recieved_data.length());
    }
//    recieved_data[i] = 0; //終端文字
    // 実際に読み取りしたあとは一度だけ改行する.

    if(i>0){
      // PCに送信する.
      Serial.println(recieved_data.c_str());
      // LCDに送信する.
      loopSerial(recieved_data.c_str());
    }

  }else{
    M5.dis.fillpix(0xfff000);
  }

}
