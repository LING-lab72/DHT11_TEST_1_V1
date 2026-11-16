/*
 * DHT11 温湿度采集 + 串口输出
 * 开发板: Arduino UNO
 * 接线:  VCC  -> 5V
 *        GND  -> GND
 *        DATA -> D2 (数据脚与 VCC 之间接 4.7k~10k 上拉电阻)
 *
 * 依赖: 库管理器安装 "DHT sensor library" (Adafruit)
 */

#include "DHT.h"

#define DHTPIN  2          // DHT11 数据脚，实际接到哪个引脚就改这里
#define DHTTYPE DHT11      // 传感器是 DHT11 填 DHT11；DHT22/AM2302 填 DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 温湿度采集启动"));
  dht.begin();
}

void loop() {
  delay(2000);   // DHT11 采样周期建议 >= 1s，这里取 2s

  float h = dht.readHumidity();
  float t = dht.readTemperature();          // 摄氏度
  float f = dht.readTemperature(true);      // 华氏度

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("读取失败：请检查接线、上拉电阻和 DHTPIN"));
    return;
  }

  Serial.print(F("湿度: "));
  Serial.print(h, 1);
  Serial.print(F(" %RH    温度: "));
  Serial.print(t, 1);
  Serial.print(F(" C / "));
  Serial.print(f, 1);
  Serial.println(F(" F"));
}