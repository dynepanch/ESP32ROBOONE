#include <Wire.h>
#include "jailo.h"

void AcceleroMeterWireRead() {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)MPU6050_ADDR, (size_t)14, (bool)true); // 型を明示的に指定

    raw_acc_x = Wire.read() << 8 | Wire.read();
    raw_acc_y = Wire.read() << 8 | Wire.read();
    raw_acc_z = Wire.read() << 8 | Wire.read();
    raw_t = Wire.read() << 8 | Wire.read();
    raw_gyro_x = Wire.read() << 8 | Wire.read();
    raw_gyro_y = Wire.read() << 8 | Wire.read();
    raw_gyro_z = Wire.read() << 8 | Wire.read();
}

void AcceleroMeterAddressSetup() {
    byte error, address;
    int nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            if (address < 16) MPU6050_ADDR = address;
            nDevices++;
        }
    }
}

void writeMPU6050(byte reg, byte data) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

void calcAcceleration() {
    acc_x = ((float)raw_acc_x) / 16384.0;
    acc_y = ((float)raw_acc_y) / 16384.0;
    acc_z = ((float)raw_acc_z) / 16384.0;
    absAccelerometer = pow(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2), 0.5);
}

void calcAngle() {
    // 角度をラジアンから度に変換して計算
    pitch = atan2(acc_y, sqrt(acc_x * acc_x + acc_z * acc_z)) * 180 / PI;
    roll = atan2(acc_x, sqrt(acc_y * acc_y + acc_z * acc_z)) * 180 / PI;
}


float use_pitch() { 
    float pitch_first=pitch;
    static float alpha = 0.8; 
    static float filtered_pitch = 0.0; 
    static const int window_size = 10; // 移動平均フィルタのウィンドウサイズ
    static float pitch_history[window_size] = {0}; // 過去のピッチデータを保持する配列
    static int index = 0; // 配列のインデックス
    static float sum_pitch = 0.0; // 移動平均フィルタの合計
    static float prev_filtered_pitch = 0.0; // 前回のフィルタ済みピッチ
    static const float threshold = 5.0; // ノイズとみなす変化のしきい値
    static int spike_count = 0; // 飛び値のカウント
    static const int spike_threshold = 3; // 連続して飛び値が発生した場合の閾値

    // 現在のピッチ値を計算
    pitch_first = (pitch - pitch_0) *j_flag;

    // 前回のフィルタ済み値と比較して、急に飛んだ値かを判定
    if (abs(pitch_first - prev_filtered_pitch) < threshold) {
        // 一次低域通過フィルタを適用
        filtered_pitch = alpha * filtered_pitch + (1 - alpha) * pitch_first;

        // 移動平均フィルタの更新
        sum_pitch -= pitch_history[index]; // 古い値を引く
        pitch_history[index] = filtered_pitch; // 新しい値を格納
        sum_pitch += filtered_pitch; // 新しい値を加算

        // インデックスを更新し、配列の範囲内に収める
        index = (index + 1) % window_size;

        // フィルタ済みピッチ値を更新
        prev_filtered_pitch = filtered_pitch;
        
        // 飛び値カウントをリセット
        spike_count = 0; 
    } 
    // 急激に変化した場合
    else {
        spike_count++;
        
        // 連続してしきい値を超えた場合
        if (spike_count >= spike_threshold) {
            filtered_pitch = alpha * filtered_pitch + (1 - alpha) * pitch;

            // 移動平均フィルタの更新
            sum_pitch -= pitch_history[index]; // 古い値を引く
            pitch_history[index] = filtered_pitch; // 新しい値を格納
            sum_pitch += filtered_pitch; // 新しい値を加算

            // インデックスを更新し、配列の範囲内に収める
            index = (index + 1) % window_size;

            // フィルタ済みピッチ値を更新
            prev_filtered_pitch = filtered_pitch;

            // カウントをリセット
            spike_count = 0;
        }
        // まだしきい値を超えていない場合は前回の値を維持
        else {
            filtered_pitch = prev_filtered_pitch;
        }
    }

    // 移動平均値を計算
    float smoothed_pitch = sum_pitch / window_size;

    return smoothed_pitch; 
}


float use_roll() {  
    float roll_first = roll; // roll値の初期化
    static float alpha = 0.8;  
    static float filtered_roll = 0.0;  
    static const int window_size = 10; // 移動平均フィルタのウィンドウサイズ 
    static float roll_history[window_size] = {0}; // 過去のロールデータを保持する配列 
    static int index = 0; // 配列のインデックス 
    static float sum_roll = 0.0; // 移動平均フィルタの合計 
    static float prev_filtered_roll = 0.0; // 前回のフィルタ済みロール 
    static const float threshold = 5.0; // ノイズとみなす変化のしきい値 
    static int spike_count = 0; // 飛び値のカウント 
    static const int spike_threshold = 3; // 連続して飛び値が発生した場合の閾値 
 
    // 現在のロール値を計算 
    roll_first = (roll - roll_0) * j_flag; // j_flagやroll_0はピッチと同様の初期化が必要
 
    // 前回のフィルタ済み値と比較して、急に飛んだ値かを判定 
    if (abs(roll_first - prev_filtered_roll) < threshold) { 
        // 一次低域通過フィルタを適用 
        filtered_roll = alpha * filtered_roll + (1 - alpha) * roll_first; 
 
        // 移動平均フィルタの更新 
        sum_roll -= roll_history[index]; // 古い値を引く 
        roll_history[index] = filtered_roll; // 新しい値を格納 
        sum_roll += filtered_roll; // 新しい値を加算 
 
        // インデックスを更新し、配列の範囲内に収める 
        index = (index + 1) % window_size; 
 
        // フィルタ済みロール値を更新 
        prev_filtered_roll = filtered_roll; 
         
        // 飛び値カウントをリセット 
        spike_count = 0;  
    }  
    // 急激に変化した場合 
    else { 
        spike_count++; 
         
        // 連続してしきい値を超えた場合 
        if (spike_count >= spike_threshold) { 
            filtered_roll = alpha * filtered_roll + (1 - alpha) * roll; 
 
            // 移動平均フィルタの更新 
            sum_roll -= roll_history[index]; // 古い値を引く 
            roll_history[index] = filtered_roll; // 新しい値を格納 
            sum_roll += filtered_roll; // 新しい値を加算 
 
            // インデックスを更新し、配列の範囲内に収める 
            index = (index + 1) % window_size; 
 
            // フィルタ済みロール値を更新 
            prev_filtered_roll = filtered_roll; 
 
            // カウントをリセット 
            spike_count = 0; 
        } 
        // まだしきい値を超えていない場合は前回の値を維持 
        else { 
            filtered_roll = prev_filtered_roll; 
        } 
    } 
 
    // 移動平均値を計算 
    float smoothed_roll = sum_roll / window_size; 
 
    return smoothed_roll;  
}


void SubProcess(void* pvParameters) {
    AcceleroMeterAddressSetup();
    while (1) {
        AcceleroMeterWireRead();
        calcAcceleration();
        calcAngle(); // 角度計算
        pitch_feed=use_pitch();
        roll_feed=use_roll();
        //delay(10);
    }
}

int pd_pitch(float kp,float kd){
  
  static float buff=0;
  int out;
    out=pitch_feed*kp+(pitch_feed-buff)*kd;
    buff=pitch_feed;
  return out;
}
