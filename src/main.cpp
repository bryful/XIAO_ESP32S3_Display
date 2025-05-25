#include <LittleFS.h>
#include <WiFi.h>
#include <time.h>
#include "LGFX_XIAO_ESP32S3_SPI_ST7789.hpp"
#include "FsSerial.hpp"

// 準備したクラスのインスタンスを作成します。
LGFX_XIAO_ESP32S3_SPI_ST7789 display;

const char *ssid = "GO";
const char *password = "771177117711";

const char *ntpServer1 = "ntp.nict.jp";
const char *ntpServer2 = "time.google.com";
const char *ntpServer3 = "ntp.jst.mfeed.ad.jp";
const long gmtOffset_sec = 9 * 3600;
const int daylightOffset_sec = 0;

static int mmTime = 0;

void DisplayPrint(const char *str)
{
  display.fillScreen(TFT_RED);
  display.setCursor(0, 20);
  display.setTextColor(TFT_WHITE);
  display.println(str);
}

void printLocalTime()
{
  struct tm timeinfo;
  if (getLocalTime(&timeinfo))
  {
    display.drawBmpFile(LittleFS, "/girl.bmp", 0, 0);
  }
  display.setCursor(20, 210);
  display.setTextColor(TFT_RED);
  display.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
  Serial.begin(115200);

  display.init();
  display.setRotation(3); // 0:横向き, 1:縦向き, 2:横向き反転, 3:縦向き反転
  display.fillScreen(TFT_RED);

  LittleFS.begin();
  display.drawBmpFile(LittleFS, "/girl.bmp", 0, 0);
  display.setTextSize(2);

  // connect to WiFi
  // DisplayPrint("SmartConfig");
  // WiFi.setTxPower((wifi_power_t)60);

  
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig(); //< SmartConfigの初期化
  int retry = 1000;
  while (!WiFi.smartConfigDone())
  {
    delay(500);
    retry--;
    if (retry <= 0)
    {
      DisplayPrint("SmartConfig timeout");
      return;
    }
  }
  //WiFi.begin(); //< SmartConfigの初期化

  if (WiFi.status() == WL_CONNECTED)
  {
    DisplayPrint("SmartConfig CONNECTED");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2, ntpServer3);
    // printLocalTime();
  }
  else
  {
    DisplayPrint(" NO CONNECTED");
  }
  delay(500);
  display.drawBmpFile(LittleFS, "/girl.bmp", 0, 0);

  mmTime = millis() + 2000;
}
void loop()
{
  int mmNow = millis();
  if (mmNow > mmTime)
  {
    printLocalTime();
    mmTime = mmNow + 2000; // 2秒ごとに更新
  }
}