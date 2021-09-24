#define DHT11_PIN 2     // пин подкючения датчика температуры
#define BUTTON_0 4      // кнопка для переключения между дисплеями
#define BUTTON_1 8      // кнопка для переключения между дисплеями в обратном порядке

#include <Wire.h>                  // подключаем библиотеку для работы с I2C
#include <DHT.h>                   // подключаем библиотеку для датчика DHT11
DHT dht(DHT11_PIN, DHT11);         // сообщаем на каком порту и какой датчик будет работать
float DHT11_temp;
float DHT11_Hum;
// экран использует A5 для SLC, A4 SDA
#include <LiquidCrystal_PCF8574.h> // Подключение библиотеки LiquidCrystal_PCF8574.h для управления дисплеем
LiquidCrystal_PCF8574 lcd(0x27);   // Вариант для библиотеки PCF8574
#include "GyverButton.h"           // Подключение библиотеки для обработки кнопки
GButton butt0(BUTTON_0);
GButton butt1(BUTTON_1);

#include "GyverTimer.h"            // Подключение библиотеки с таймерами
GTimer secTimer(MS, 1000);         // Таймер работающий раз в 1000 мс

void setup() {
  Serial.begin(9600);        // подключаем монитор порта
  dht.begin();               // запускаем датчик DHT11
  lcd.begin(16, 2);          // Экран 16 столбцов на 2 строки
  lcd.setBacklight(255);     // Установка максимальной яркости экрана

  // устанавливаем опрос кнопок на автоматический
  butt0.setTickMode(AUTO);
  butt1.setTickMode(AUTO);

}

void loop() { // Основной цикл
  sensor_DHT11();
  Switch_Display_Buttons();
}

void sensor_DHT11() {
  if ( isnan(DHT11_temp) || isnan(DHT11_Hum)) { // Проверка работоспособности датчика
    Serial.println("DHT11 ERROR");
    return;
  }
  if (secTimer.isReady()) {
    DHT11_temp = dht.readTemperature(); // Считываем температуру (t)
    DHT11_Hum = dht.readHumidity();     // Cчитываем  влажность (h)
  }
}

void DHT11_info() {

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
  lcd.setCursor(0, 1);
  lcd.print("Display 1");
  Serial.println("Display 1");
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

void Display4() {
  lcd.setCursor(0, 1);
  lcd.print("Display 4");
  Serial.println("Display 4");
}

void Display5() {
  lcd.setCursor(0, 1);
  lcd.print("Display 5");
  Serial.println("Display 5");
}

void Display_off() {
  lcd.setCursor(0, 1);
  lcd.print("Button test");
  //Serial.println("Button test");
}

void   Switch_Display_Buttons() {
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
    case 1: Display1(); break;
    case 2: Display2(); break;
    case 3: Display3(); break;
    case 4: Display4(); break;
    case 5: Display5(); break;
  }
}
