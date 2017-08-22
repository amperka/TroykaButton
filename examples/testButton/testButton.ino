#include "TroykaButton.h"

// создаём объект для работы с кнопкой
TroykaButton button(0);

void setup()
{
  // открываем монитор Serial порта
  Serial.begin(9600);
  // начало работы с кнопкой
  button.begin();
}

void loop() 
{
  // опеределяем клик кнопки
  if (button.onPress()) {
    Serial.println("Key on press");
  }
  // определяем отжатие кнопки
  if (button.onRelease()) {
    Serial.println("Key is release");
  }
  // определяем зажатие кнопки на 3 секунды
  if (button.isPressed(3000)) {
    Serial.println("Key on long press");
  }
}
