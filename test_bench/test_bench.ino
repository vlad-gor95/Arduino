#include <Wire.h>        // подключаем библиотеку для работы с I2C
#include <DHT.h>         // подключаем библиотеку для датчика DHT11

#define DHTTYPE11 DHT11  // тип датчика DHT11
#define DHTTYPE22 DHT22  // тип датчика DHT22

#define DHT11_PIN 2      // пин подкючения датчика температуры DHT11
#define DHT22_PIN 5      // пин подкючения датчика температуры DHT22

DHT dht11(DHT11_PIN, DHTTYPE11); // сообщаем на каком порту и DHT11 будет работать
float DHT11_temp;
float DHT11_Hum;
DHT dht22(DHT22_PIN, DHTTYPE22); // сообщаем на каком порту и DHT22 будет работать
float DHT22_temp;
float DHT22_Hum;

#include <LiquidCrystal_PCF8574.h> // Подключение библиотеки LiquidCrystal_PCF8574.h для управления дисплеем
LiquidCrystal_PCF8574 lcd(0x27);   // Вариант для библиотеки PCF8574

#define lcd00 lcd.setCursor(0, 0);
#define lcd01 lcd.setCursor(0, 1);

#include "GyverButton.h"           // Подключение библиотеки для обработки кнопки
#define BUTTON_0 4       // кнопка для переключения между дисплеями
#define BUTTON_1 8       // кнопка для переключения между дисплеями в обратном порядке
GButton butt0(BUTTON_0);
GButton butt1(BUTTON_1);

#include "GyverTimer.h"            // Подключение библиотеки с таймерами
GTimer secTimer(MS, 1000);         // Таймер работающий раз в 1000 мс
GTimer Timer(MS, 2000);         // Таймер работающий раз в 1000 мс

void setup() {
  Serial.begin(9600);          // подключаем монитор порта
  dht11.begin();               // запускаем датчик DHT11
  dht22.begin();               // запускаем датчик DHT22
  lcd.begin(16, 2);            // Экран 16 столбцов на 2 строки
  lcd.setBacklight(255);       // Установка максимальной яркости экрана

  // устанавливаем опрос кнопок на автоматический
  butt0.setTickMode(AUTO);
  butt1.setTickMode(AUTO);
}

void loop() { // Основной цикл
  sensor_DHT22();
  sensor_DHT11();

  Switch_Display_Buttons();
}

void sensor_DHT11() {
  if ( isnan(DHT11_temp) || isnan(DHT11_Hum)) { // Проверка работоспособности датчика
    Serial.println("DHT11 ERROR");
  }
  DHT11_temp = dht11.readTemperature(); // Считываем температуру (t)
  DHT11_Hum = dht11.readHumidity();     // Cчитываем  влажность (h)
}

void sensor_DHT22() {
  if ( isnan(DHT22_temp) || isnan(DHT22_Hum)) { // Проверка работоспособности датчика
    Serial.println("DHT22 ERROR");
  }
  DHT22_temp = dht22.readTemperature(); // Считываем температуру (t)
  DHT22_Hum = dht22.readHumidity();     // Cчитываем  влажность (h)
}

void DHT11_info() {
  getDHTFunc(DHT11_temp, DHT11_Hum);
}

void DHT22_info() {
  getDHTFunc(DHT22_temp, DHT22_Hum);
}

float getDHTFunc (float DHT_Temp, float DHT_Hum) {
  lcd00;
  lcd.print("Temp:");
  lcd01;
  lcd.print("Humidity:");
  lcd.setCursor(15, 0);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.print("%");
  lcd.setCursor(10, 0);
  lcd.print(DHT_Temp, 1); // показать только 1 знак после зпт
  lcd.setCursor(10, 1);
  lcd.print(DHT_Hum, 1);
}

void Display1() {
  lcd01;
  lcd.print("Display 1");
  Serial.println("Display 1");
}

void Display2() {
  lcd01;
  lcd.print("Display 2");
  Serial.println("Display 2");
}

void Display3() {
  lcd01;
  lcd.print("Display 3");
  Serial.println("Display 3");
}

void Display4() {
  lcd01;
  lcd.print("Display 4");
  Serial.println("Display 4");
}

void Display5() {
  lcd01;
  lcd.print("Display 5");
  Serial.println("Display 5");
}

void Display_off() {
  lcd01;
  lcd.print("Button test");
  //Serial.println("Button test");
}

void Switch_Display_Buttons() {
  static byte mode = 0;
  if (butt0.isClick()) {
    if (++mode >= 6) mode = 0;
    Serial.println("Button0 pressed");
    lcd.clear();
  }
  if (butt1.isClick()) {
    if (--mode >= 6) mode = 5;
    Serial.println("Button1 pressed");
    lcd.clear();
  }

  switch (mode) {
    case 0: DHT11_info(); break;
    case 1: DHT22_info(); break;
    case 2: Display2(); break;
    case 3: Display3(); break;
    case 4: Display4(); break;
    case 5: Display5(); break;
  }
}
