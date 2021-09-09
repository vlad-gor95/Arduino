#define DHT11_PIN 2
#define BUTTON_0_PIN 4

//#include <GyverOS.h>               // подключаем простой диспетчер задач
//GyverOS<5> OS;                     // количество подключенных задач - 5
//#include <GyverPower.h>                   // подключение библиотеки энергосбережения
#include <Wire.h>                  // подключаем библиотеку для работы с I2C
#include <DHT.h>                   // подключаем библиотеку для датчика DHT11
DHT dht(DHT11_PIN, DHT11);         // сообщаем на каком порту и какой датчик будет работать
float DHT11_temp = 0;
byte DHT11_Hum = 0;
#include <LiquidCrystal_PCF8574.h> // Подключение библиотеки LiquidCrystal_PCF8574.h для управления дисплеем
LiquidCrystal_PCF8574 lcd(0x27);   // Вариант для библиотеки PCF8574
#include <EncButton.h>             // Подключение библиотеки для обработки кнопки
EncButton<EB_TICK, BUTTON_0_PIN> btn(INPUT_PULLUP);
#include "GyverTimer.h"            // Подключение библиотеки с таймерами
GTimer secTimer(MS, 500);         // Таймер работающий раз в 500 мс



void setup() {
  Serial.begin(9600);        // подключаем монитор порта
  dht.begin();               // запускаем датчик DHT11
  lcd.begin(16, 2);          // Экран 16 столбцов на 2 строки
  lcd.setBacklight(255);     // Установка максимальной яркости экрана
  /*
    // порядковый номер задачи, имя функции, время в мс.
    OS.attach(0, sensor_DHT11, 1000);
    OS.attach(1, Display0, 1000);
    OS.attach(2, Display1, 1000);
    OS.attach(3, Display2, 1000);
    OS.attach(4, Display3, 1000);
  */
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
    lcd.setCursor(0, 1);
    lcd.print("Display 0");
    Serial.println("Display 0");
  */
  if (secTimer.isReady()) {
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

}

void Display1() {
  if (secTimer.isReady()) {
    unsigned long time;
    time = micros();
    lcd.setCursor(0, 0);
    lcd.print(time);
    Serial.println(time);
    lcd.setCursor(0, 1);
    lcd.print("Display 1");
  }

}

void Display2() {
  lcd.setCursor(0, 1);
  lcd.print("Display 2");
  Serial.println("Display 2");
}

void Display3() {
  lcd.setCursor(0, 1);
  lcd.print("Display 3");
  Serial.println("Display 3");
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
  //OS.tick();  // Вызов всех задач
  sensor_DHT11();
  Button1();
  //power.sleepDelay(OS.getLeft());

}
