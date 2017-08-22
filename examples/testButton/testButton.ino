#include "TroykaButton.h"

// создаём объект для работы с кнопкой
TroykaButton button(4);

void setup()
{
  // открываем монитор Serial порта
  Serial.begin(9600);
  // начало работы с кнопкой
  button.begin();
}

void loop() 
{
  // считывание данных с кнопки
  button.read();
  // опеределяем клик кнопки
  if (button.justPressed()) {
    Serial.println("Key on press");
  }
  // определяем отжатие кнопки
  if (button.justReleased()) {
    Serial.println("Key is release");
  }
  
  // определяем зажатие кнопки на 3 секунды
  else if (button.isHold(3000)) {
    Serial.println("Key on long press");
  }
}
