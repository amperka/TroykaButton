#ifndef _TROYKA_BUTTON_H_
#define _TROYKA_BUTTON_H_

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEBOUNCE_TIME   50
#define ON_PRESS        1
#define ON_PRESS_LONG   2
#define ON_RELEASE      3

class TroykaButton
{
public:
    TroykaButton(uint8_t pin, bool pullUP = true);
    void begin();
    // считывание данных с кнопки
    void read(uint32_t time = 2000);
    // определение клика кнопки
    bool onPress();
    // определение отжатие кнопки
    bool onRelease();
    // определение зажатие кнопки (по умолчанию 2 секунды)
    bool isPressed(uint32_t time = 2000);
private:
    // номера пина
    uint8_t	_pin;
    // выбор подтяжки
    bool _pullUP;
    // ранее состояние кнопки
    bool _buttonStateWas;
    // время нажатия кнопки
    uint32_t _msButtonState;
    // состояние системы
    uint8_t _state;
    // длинное нажатие
    bool _buttonStateNowLong;
};

#endif