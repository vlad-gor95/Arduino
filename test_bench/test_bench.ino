#include <Wire.h>
#include <DHT.h>                   // подключаем библиотеку для датчика
DHT dht(2, DHT11);                 // сообщаем на каком порту будет датчик
#include <LiquidCrystal_PCF8574.h> // Подключение библиотеки LiquidCrystal_PCF8574.h
LiquidCrystal_PCF8574 lcd(0x27);   // Вариант для библиотеки PCF8574
#include <EncButton.h>             // Подключение библиотеки для обработки кнопки
EncButton<EB_TICK, 4> btn(INPUT_PULLUP);
#include "GyverTimer.h"            // Подключение библиотеки с таймерами
GTimer secTimer(MS, 1000);         // Таймер работающий раз в сек

void setup() {
  Serial.begin(9600);        // подключаем монитор порта
  dht.begin();               // запускаем датчик DHT11
  lcd.begin(16, 2);          // Экран 16 столбцов на 2 строки
  lcd.setBacklight(255);     // Установка максимальной яркости экрана

  pinMode(4, INPUT_PULLUP);  //Настройка кнопку на 4 выход
}


void Display0() {
  if (secTimer.isReady()) {
    float t = dht.readTemperature(); // Считываем температуру (t)
    byte h = dht.readHumidity();     // Cчитываем  влажность (h)

    // выводим температуру (t) и влажность (h) на монитор порта (дебаг) и на дисплей
    /*
      Serial.print("Humidity: ");
      Serial.println(h);
      Serial.print("Temperature: ");
      Serial.println(t);
      lcd.setCursor(0, 1);
      lcd.print("Display 0");
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
    lcd.print(t, 1);
    lcd.setCursor(10, 1);
    lcd.print(h, 1);
  }
}

void Display1() {
  if (secTimer.isReady()) {
    unsigned long time;
    time = micros();
    lcd.setCursor(0, 0);
    lcd.print(time);
    Serial.println(time);
  }
}

void Display2() {
}

void Display3() {
  lcd.setCursor(0, 1);
  lcd.print("Display-3");
  Serial.println("Display-3");
}

void Button1() {
  static byte mode = 0;
  btn.tick();
  if (btn.isClick()) {
    if (++mode >= 4) mode = 0;
    lcd.clear();
  }

  switch (mode) {
    case 0: Display0(); break;
    case 1: Display1(); break;
    case 2: Display2(); break;
    case 3: Display3(); break;
  }
}

void loop() { // Основной цикл
  Button1();
}
