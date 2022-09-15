#include "TroykaButton.h"

// Общий пример работы с кнопками.

// создаём объект для работы с кнопкой с параметром номер пина
TroykaButton button(4);
// также есть три необзятельных параметра:
// время длительного зажатия кнопки: по умолчанию 2000 мc
// выбор подтяжки кнопки: по умолчанию подтяжка к минусу
// интервал через который нажатие кнопки будет автоматически повторяться при длительном зажатии: по умолчанию 0 мс (данная функция отключена)
// TroykaButton button(4, 2000, true, 0);
void setup() {
  // открываем монитор Serial порта
  Serial.begin(9600);
  // начало работы с кнопкой
  button.begin();
}

void loop() 
{
  // считываем данные с кнопки
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
  if (button.isHold()) {
    Serial.println("Key on long press");
  }
  // определяем короткое нажатие кнопки
  if (button.isClick()) {
    Serial.println("Key is clicked");
  }
}
