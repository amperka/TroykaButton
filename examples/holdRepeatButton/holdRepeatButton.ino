#include "TroykaButton.h"

// Пример работы с функциями длительного нажатия и автоматического повтора после длительного нажатия.

// создаём объект для работы с кнопкой с параметром номер пина
TroykaButton button(4, 2000, true, 200);
// время длительного зажатия кнопки равно 2000 мс
// при длительном зажатии кнопки каждые 200мс кнопка начнет рабатывать автоматически
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
  // определяем короткое нажатие кнопки
  if (button.isClick()) {
    Serial.println("Key is clicked");
  }
  // определяем автоматические клики
  if (button.isClickOnHold()) {
    Serial.println("Key is clicked during long press");
  }
}
