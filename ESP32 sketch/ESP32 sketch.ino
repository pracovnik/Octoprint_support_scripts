#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <ESP32Servo.h>


//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled

//this edit code doesn't use a gzipped html source code
//the html -code is open and is easy to update or modify  on the other tab page = app_httpd.cpp

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//board esp32wrower modul
// upload speed 921600
//partition scheme huge

#define CAMERA_MODEL_AI_THINKER
//ai-thinker: esp32 ai thinker esp 32 cam

//wrover : 


#include "camera_pins.h"

const char* ssid = "the wifi name";
const char* password = "the wifi password";

IPAddress local_IP(192, 168, 1, 198); //For printer
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


void startCameraServer();

  
void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("start1");
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_XGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  Serial.println("start2");
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  Serial.println("start3");
  //drop down frame size for higher initial frame rate
  sensor_t * s = esp_camera_sensor_get();
  //s->set_framesize(s, FRAMESIZE_QVGA);
  s->set_framesize(s, FRAMESIZE_XGA);//v12345vtm


  WiFi.begin(ssid, password);
  Serial.println("start4");
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  Serial.println("start5");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("N");
  }

  Serial.println("start6");
  startCameraServer();

  Serial.println("start7-");
  const int ServoPin = 2;  
  ledcSetup(8, 50, 16); // 50 hz PWM, 16-bit resolution, range from 3250 to 6500.
  ledcAttachPin(ServoPin, 8); 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
}
