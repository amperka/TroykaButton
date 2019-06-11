/****************************************************************************/
//  Function:       Header file for TroykaButton
//  Arduino IDE:    Arduino-1.8.5
//  Author:         Igor Dementiev
//  Date:           Sep 09,2018
//  Version:        v1.0
//  by www.amperka.ru
/****************************************************************************/

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
    TroykaButton(uint8_t pin, uint32_t timeHold = 2000, bool pullUP = true);
    // инициализация кнопки
    void begin();
    // считывание данных с кнопки
    void read();
    // определение клика кнопки
    bool justPressed() const;
    // определение отжатие кнопки
    bool justReleased() const;
    // определение зажатие кнопки (по умолчанию 2 секунды)
    bool isHold() const;
    // определение короткого клика, если сработал метод isHold() клик не сработает.
    bool isClick() const;
private:
    // номера пина
    uint8_t _pin;
    // время длительного зажатия кнопки
    uint32_t _timeHold;
    // выбор подтяжки
    bool _pullUP;
    // короткое нажатие кнопки (клик)
    bool _isClick;
    // состояние кнопки
    uint8_t _stateButton;
    // предыдущие состояние кнопки
    uint8_t _buttonStateOld;
    // ранее состояние кнопки
    bool _buttonStateWas;
    // длинное нажатие
    bool _buttonStateNowLong;
    // время нажатия кнопки
    uint32_t _msButtonState;
};

#endif