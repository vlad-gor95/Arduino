#define DHT11_PIN 2     // пин подкючения датчика температуры
#define BUTTON_0_PIN 4  // кнопка для переключения между дисплеями
#define BUTTON_1_PIN 7

#include <Wire.h>                  // подключаем библиотеку для работы с I2C
#include <DHT.h>                   // подключаем библиотеку для датчика DHT11
DHT dht(DHT11_PIN, DHT11);         // сообщаем на каком порту и какой датчик будет работать
float DHT11_temp = 0;
byte DHT11_Hum = 0;
#include <LiquidCrystal_PCF8574.h> // Подключение библиотеки LiquidCrystal_PCF8574.h для управления дисплеем
LiquidCrystal_PCF8574 lcd(0x27);   // Вариант для библиотеки PCF8574
#include <EncButton.h>             // Подключение библиотеки для обработки кнопки
EncButton<EB_TICK, BUTTON_0_PIN > btn0(INPUT_PULLUP);
EncButton<EB_TICK, BUTTON_1_PIN > btn1(INPUT_PULLUP);

#include "GyverTimer.h"            // Подключение библиотеки с таймерами
GTimer secTimer(MS, 500);          // Таймер работающий раз в 500 мс

void setup() {
  Serial.begin(9600);        // подключаем монитор порта
  dht.begin();               // запускаем датчик DHT11
  lcd.begin(16, 2);          // Экран 16 столбцов на 2 строки
  lcd.setBacklight(255);     // Установка максимальной яркости экрана

}

void loop() { // Основной цикл
  sensor_DHT11();
  //Button0();
  Button1();
}

void sensor_DHT11() {
  if (secTimer.isReady()) {
    DHT11_temp = dht.readTemperature(); // Считываем температуру (t)
    DHT11_Hum = dht.readHumidity();     // Cчитываем  влажность (h)
  }
}

void Display0() {

  // выводим температуру (t) и влажность (h) на монитор порта (дебаг) и на дисплей
  /*
    Serial.print("Humidity: ");
    Serial.println(DHT11_Hum);
    Serial.print("Temperature: ");
    Serial.println(DHT11_temp);
    //lcd.setCursor(0, 1);
    // lcd.print("Display 0");
    Serial.println("Display 0");
  */

  //"Рисуем" интерфейс
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.setCursor(15, 0);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.print("%");
  lcd.setCursor(10, 0);
  lcd.print(DHT11_temp, 1); // показать только 1 знак после зпт
  lcd.setCursor(10, 1);
  lcd.print(DHT11_Hum);
}

void Display1() {
  if (secTimer.isReady()) {
    unsigned long time;
    time = micros();
    lcd.setCursor(0, 0);
    lcd.print(time);
    //Serial.println(time);
    lcd.setCursor(0, 1);
    lcd.print("Display 1");
  }
}

void Display2() {
  lcd.setCursor(0, 1);
  lcd.print("Display 2");
  //Serial.println("Display 2");
}

void Display3() {
  lcd.setCursor(0, 1);
  lcd.print("Display 3");
  //Serial.println("Display 3");
}

void Display4() {
  lcd.setCursor(0, 1);
  lcd.print("Display 4");
  //Serial.println("Display 4");
}

void Display_test() {
  lcd.setCursor(1, 1);
  lcd.print("Button 2");
  Serial.println("Button 2");

}

void Display_off() {
  lcd.setCursor(0, 1);
  lcd.print("Button test");
  //Serial.println("Button test");
}

void Button0() {
  static byte mode = 0;
  btn0.tick();
  if (btn0.isClick()) {
    if (++mode >= 4) mode = 0;
     Serial.println("Button0 pressed");
    lcd.clear();
  }

  switch (mode) {
    case 0: Display0(); break;
    case 1: Display1(); break;
    case 2: Display2(); break;
    case 3: Display3(); break;
  }
}

void Button1() {
  static byte mode1 = 0;
  btn1.tick();
  if (btn1.isClick()) {
    if (++mode1 >= 3) mode1 = 0;
    Serial.println("Button1 pressed");
    lcd.clear();
  }

  switch (mode1) {
    case 0: Display_test(); break;
    case 1: Display_off(); break;
  }
}
