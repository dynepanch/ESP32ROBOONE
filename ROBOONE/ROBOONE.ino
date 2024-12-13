#include <PS4Controller.h>
#include <IcsHardSerialClass.h> // 近藤サーボ用のヘッダーファイル
//#include <Ps3Controller.h>      // コントローラ用ヘッダー
#include "comand.h"      // コントローラ用ヘッダー
#include "define.h"
#include <Wire.h>
#include "jailo.h"

hw_timer_t* typerion = NULL;
unsigned int servo_timer=0;
unsigned int flag_timer=0;

void IRAM_ATTR onTimer() {
  cnt_time+=1;
  ltimer+=1;
  servo_timer++;
}

void setup() {
  static int i=0;
  Serial1.begin(115200, SERIAL_8N1, 17, 26);
  Serial2.begin(115200, SERIAL_8N1, 18, 25);
  //Serial2.begin(115200);
  Serial.begin(115200);
  delay(1000);
  krs.begin();
  krs1.begin();
  krs2.begin();
  delay(1000);
  PS4.attachOnConnect(onConnect);
  PS4.begin();
  //Ps3.attachOnConnect(onConnect);
  //Ps3.begin("3c:e9:0e:8c:45:26");
  
  pinMode(LED_PIN1, OUTPUT);  // LEDの出力設定
  pinMode(LED_PIN2, OUTPUT);
  
  delay(500);
   // タイマーの設定
  typerion = timerBegin(0,80, true);  // 80はAPBクロックの分周比を指定
  timerAttachInterrupt(typerion, &onTimer, true);
  timerAlarmWrite(typerion, 300, true);
  timerAlarmEnable(typerion);

  Wire.begin();
  xTaskCreatePinnedToCore(SubProcess, "SubProcess", 4096, NULL, 1, NULL, 0);
}

void loop() {
  /*Serial.print(" pitch:");
  Serial.print(use_pitch());
  Serial.println();*/
  if (PS4.isConnected()){
        CNTR_PUTS();
    }
  servo_move();
  //Ps3.setPlayer(player);
  //LEDOUT(0x01);
  //Serial.println(Ps3.data.analog.button.l2);
  if(PS4.Share() && j_flag==0){
      pitch_0=pitch;
      roll_0=roll;
      j_flag=1;
      PS4.sendToController();
    }
  if(PS4.Options())j_flag=0;
}
