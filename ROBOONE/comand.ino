#include "comand.h"      // コントローラ用ヘッダー
/*#include <Ps3Controller.h>      // コントローラ用ヘッダー
*/
unsigned int ps3_cmmand_1() {
 static unsigned int ps3_cmd = 0xff;
ps3_cmd = 0xFF; // 初期値をすべてのビットが1に設定

// 各ボタンの状態を対応ビットに反映
ps3_cmd &= ~(PS4.Left()      << 7); // 左ボタン（7ビット目）
ps3_cmd &= ~(PS4.Down()      << 6); // 下ボタン（6ビット目）
ps3_cmd &= ~(PS4.Right()     << 5); // 右ボタン（5ビット目）
ps3_cmd &= ~(PS4.Up()        << 4); // 上ボタン（4ビット目）
ps3_cmd &= ~(PS4.Touchpad()  << 3); // タッチパッド（3ビット目）
ps3_cmd &= ~(PS4.R3()        << 2); // R3ボタン（2ビット目）
ps3_cmd &= ~(PS4.L3()        << 1); // L3ボタン（1ビット目）
ps3_cmd &= ~PS4.PSButton();        // PSボタン（0ビット目）

/*if (PS4.Left())      ps3_cmd &= ~0x80; // 左ボタンが押された場合、対応ビットをクリア
if (PS4.Down())      ps3_cmd &= ~0x40; // 下ボタンが押された場合
if (PS4.Right())     ps3_cmd &= ~0x20; // 右ボタンが押された場合
if (PS4.Up())        ps3_cmd &= ~0x10; // 上ボタンが押された場合
if (PS4.Touchpad())  ps3_cmd &= ~0x08; // タッチパッドが押された場合
if (PS4.R3())        ps3_cmd &= ~0x04; // R3ボタンが押された場合
if (PS4.L3())        ps3_cmd &= ~0x02; // L3ボタンが押された場合
if (PS4.PSButton())  ps3_cmd &= ~0x01; // PSボタンが押された場合*/
  /*
  if (PS4.Left()) ps3_cmd &= 0x7f;
  if (PS4.Left()!=1) ps3_cmd |= 0x80;
  if (PS4.Down()) ps3_cmd &= 0xbf;
  if (PS4.Down()!=1) ps3_cmd |= 0x40;
  if (PS4.Right()) ps3_cmd &= 0xdf;
  if (PS4.Right()!=1) ps3_cmd |= 0x20;
  if (PS4.Up()) ps3_cmd &= 0xef;
  if (PS4.Up()!=1) ps3_cmd |= 0x10;
  if (PS4.Touchpad()) ps3_cmd &= 0xf7;
  if (PS4.Touchpad()!=1) ps3_cmd |= 0x08;
  if (PS4.R3()) ps3_cmd &= 0xfb;
  if (PS4.R3()!=1) ps3_cmd |= 0x04;
  if (PS4.L3()) ps3_cmd &= 0xfd;
  if (PS4.L3()!=1) ps3_cmd |= 0x02;
  if (PS4.PSButton()) ps3_cmd &= 0xfe;
  if (PS4.PSButton()!=1) ps3_cmd |= 0x01;
  */
 /* 
  if (Ps3.event.button_down.left) ps3_cmd &= 0x7f;
  if (Ps3.event.button_up.left) ps3_cmd |= 0x80;
  if (Ps3.event.button_down.down) ps3_cmd &= 0xbf;
  if (Ps3.event.button_up.down) ps3_cmd |= 0x40;
  if (Ps3.event.button_down.right) ps3_cmd &= 0xdf;
  if (Ps3.event.button_up.right) ps3_cmd |= 0x20;
  if (Ps3.event.button_down.up) ps3_cmd &= 0xef;
  if (Ps3.event.button_up.up) ps3_cmd |= 0x10;
  if (Ps3.event.button_down.start) ps3_cmd &= 0xf7;
  if (Ps3.event.button_up.start) ps3_cmd |= 0x08;
  if (Ps3.event.button_down.r3) ps3_cmd &= 0xfb;
  if (Ps3.event.button_up.r3) ps3_cmd |= 0x04;
  if (Ps3.event.button_down.l3) ps3_cmd &= 0xfd;
  if (Ps3.event.button_up.l3) ps3_cmd |= 0x02;
  if (Ps3.event.button_down.select) ps3_cmd &= 0xfe;
  if (Ps3.event.button_up.select) ps3_cmd |= 0x01;
  */
  return ps3_cmd;
}
unsigned int ps3_cmmand_2() {
 static unsigned int ps3_cmd = 0xff;
ps3_cmd = 0xFF; // 初期値をすべてのビットが1に設定 1111 1111

// ボタンの状態に応じてビットを操作
ps3_cmd &= ~(PS4.Square()    << 7); // 四角ボタン（7ビット目） 1000 0000 0111 1111
ps3_cmd &= ~(PS4.Cross()     << 6); // バツボタン（6ビット目） 0100 0000
ps3_cmd &= ~(PS4.Circle()    << 5); // 丸ボタン（5ビット目）   
ps3_cmd &= ~(PS4.Triangle()  << 4); // 三角ボタン（4ビット目）
ps3_cmd &= ~(PS4.R1()        << 3); // R1ボタン（3ビット目）
ps3_cmd &= ~(PS4.L1()        << 2); // L1ボタン（2ビット目）   

// R2, L2のトリガー値に応じてビットを操作
ps3_cmd = (ps3_cmd & ~0x02) | ((PS4.R2Value() <= 100) << 1); // R2トリガー
ps3_cmd = (ps3_cmd & ~0x01) | (PS4.L2Value() <= 100);        // L2トリガー

// ボタンの状態に応じてビットをクリア
/*
if (PS4.Square())    ps3_cmd &= ~0x80; // 四角ボタン
if (PS4.Cross())     ps3_cmd &= ~0x40; // バツボタン
if (PS4.Circle())    ps3_cmd &= ~0x20; // 丸ボタン
if (PS4.Triangle())  ps3_cmd &= ~0x10; // 三角ボタン
if (PS4.R1())        ps3_cmd &= ~0x08; // R1ボタン
if (PS4.L1())        ps3_cmd &= ~0x04; // L1ボタン

// R2, L2のトリガー値に応じてビットを操作
if (PS4.R2Value() > 100) ps3_cmd &= ~0x02; else ps3_cmd |= 0x02; // R2トリガー
if (PS4.L2Value() > 100) ps3_cmd &= ~0x01; else ps3_cmd |= 0x01; // L2トリガー
*/
 return ps3_cmd;
 /*
 if (PS4.Square()) ps3_cmd &= 0x7f;0111 1111 
  if (PS4.Square()!=1) ps3_cmd |= 0x80; 1000 0000
  if (PS4.Cross()) ps3_cmd &= 0xbf; 
  if (PS4.Cross()!=1) ps3_cmd |= 0x40; 
  if (PS4.Circle()) ps3_cmd &= 0xdf; 
  if (PS4.Circle()!=1) ps3_cmd |= 0x20; 
  if (PS4.Triangle()) ps3_cmd &= 0xef; 
  if (PS4.Triangle()!=1) ps3_cmd |= 0x10; 
  if (PS4.R1()) ps3_cmd &= 0xf7; 
  if (PS4.R1()!=1) ps3_cmd |= 0x08; 
  if (PS4.L1()) ps3_cmd &= 0xfb; 
  if (PS4.L1()!=1) ps3_cmd |= 0x04; 
  if (PS4.R2Value()>100) ps3_cmd &= 0xfd; 
  if (PS4.R2Value()<100) ps3_cmd |= 0x02; 
  if (PS4.L2Value()>100) ps3_cmd &= 0xfe; 
  if (PS4.L2Value()<100) ps3_cmd |= 0x01;
 */
 /* static unsigned int ps3_cmd = 0xff;
  if (Ps3.event.button_down.square) ps3_cmd &= 0x7f;
  if (Ps3.event.button_up.square) ps3_cmd |= 0x80;
  if (Ps3.event.button_down.cross) ps3_cmd &= 0xbf;
  if (Ps3.event.button_up.cross) ps3_cmd |= 0x40;
  if (Ps3.event.button_down.circle) ps3_cmd &= 0xdf;
  if (Ps3.event.button_up.circle) ps3_cmd |= 0x20;
  if (Ps3.event.button_down.triangle) ps3_cmd &= 0xef;
  if (Ps3.event.button_up.triangle) ps3_cmd |= 0x10;
  if (Ps3.event.button_down.r1) ps3_cmd &= 0xf7;
  if (Ps3.event.button_up.r1) ps3_cmd |= 0x08;
  if (Ps3.event.button_down.l1) ps3_cmd &= 0xfb;
  if (Ps3.event.button_up.l1) ps3_cmd |= 0x04;
  if (Ps3.data.analog.button.r2>100) ps3_cmd &= 0xfd;
  if (Ps3.data.analog.button.r2<100) ps3_cmd |= 0x02;
  if (Ps3.data.analog.button.l2>100) ps3_cmd &= 0xfe;
  if (Ps3.data.analog.button.l2<100) ps3_cmd |= 0x01;
  return ps3_cmd;*/
}
unsigned int CONTLLOR(void){
  static int cont_1= ps3_cmmand_2();
  static int cont_2= ps3_cmmand_1();
  cont_1= ps3_cmmand_2();
  cont_2= ps3_cmmand_1();
   
  return cont_1 | cont_2*0x100;
}
/*
void con_bat(void){
  int battery = 0;
  if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_low){
          Ps3.setRumble(100.0, 1000);
        }
    }
}*/