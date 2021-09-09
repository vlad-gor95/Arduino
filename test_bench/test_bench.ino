#define DHT11_PIN 2
#define BUTTON_0_PIN 4

#include <GyverOS.h>               // подключаем простой диспетчер задач
GyverOS<5> OS;                     // количество подключенных задач - 5
#include <bra.h>            // подключение библиотеки энергосбережения
#include <Wire.h>                  // подключаем библиотеку для работы с I2C
#include <DHT.h>                   // подключаем библиотеку для датчика DHT11
DHT dht(DHT11_PIN, DHT11);         // сообщаем на каком порту и какой датчик будет работать
float DHT11_temp = 0;
byte DHT11_Hum = 0;
#include <LiquidCrystal_PCF8574.h> // Подключение библиотеки LiquidCrystal_PCF8574.h для управления дисплеем
LiquidCrystal_PCF8574 lcd(0x27);   // Вариант для библиотеки PCF8574
#include <EncButton.h>             // Подключение библиотеки для обработки кнопки
EncButton<EB_TICK, BUTTON_0_PIN> btn(INPUT_PULLUP);



void setup() {
  Serial.begin(9600);        // подключаем монитор порта
  dht.begin();               // запускаем датчик DHT11
  lcd.begin(16, 2);          // Экран 16 столбцов на 2 строки
  lcd.setBacklight(255);     // Установка максимальной яркости экрана

  // порядковый номер задачи, имя функции, время в мс.
  OS.attach(0, sensor_DHT11, 100);
  OS.attach(1, Display0, 1000);
  OS.attach(2, Display1, 1000);
  OS.attach(3, Display2, 1000);
  OS.attach(4, Display3, 1000);
}

void sensor_DHT11() {
  DHT11_temp = dht.readTemperature(); // Считываем температуру (t)
  DHT11_Hum = dht.readHumidity();     // Cчитываем  влажность (h)
}

void Display0() {
  /*
    float t = dht.readTemperature(); // Считываем температуру (t)
    byte h = dht.readHumidity();     // Cчитываем  влажность (h)
  */
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
  lcd.print(DHT11_temp, 1);
  lcd.setCursor(10, 1);
  lcd.print(DHT11_Hum, 1);

}

void Display1() {
  unsigned long time;
  time = micros();
  lcd.setCursor(0, 0);
  lcd.print(time);
  Serial.println(time);

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
  OS.tick();  // Вызов всех задач
  power.sleepDelay(OS.getLeft());
  Button1();
}
