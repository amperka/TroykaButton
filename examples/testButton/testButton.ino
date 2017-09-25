#include "TroykaButton.h"

// создаём объект для работы с кнопкой и передаём номер пина
// также есть два необзятельных параметра:
// время длительного зажатия кнопки (по умолчанию 2000 мс)
// выбор подтяжки кнопки (по умолчанию подтяжка к минусу)
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
  
  // определяем длительное зажатие кнопки
  else if (button.isHold()) {
    Serial.println("Key on long press");
  }
}
