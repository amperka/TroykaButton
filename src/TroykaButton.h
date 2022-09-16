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
#define NONE            0
#define ON_PRESS        1
#define ON_PRESS_LONG   2
#define ON_RELEASE      3

class TroykaButton
{
public:
    TroykaButton(uint8_t pin, uint32_t timeHold = 2000, bool pullUP = true, uint32_t repeatDelay = 0);
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
    // определение автоматических кликов при длинном удержании
    bool isClickOnHold() const;
    // Отпущена ли кнопка
    bool isReleased() const;
    // Нажата ли кнопка
    bool isPressed() const;

private:
    // номера пина
    uint8_t _pin;
    // время длительного зажатия кнопки
    uint32_t _timeHold;
    // интервал повторного срабатывания кнопки при зажатии
    uint32_t _repeatDelay;
    // выбор подтяжки
    bool _pullUP;
    // короткое нажатие кнопки (клик)
    bool _isClick;
    // автоматический клик при зажатии кнопки
    bool _isClickOnHold;
    // информация о состоянии кнопки
    uint8_t _buttonEventState;
    // информация о предыдущием состоянии кнопки
    uint8_t _buttonEventStateOld;
    // состояние кнопки в данный момент
    bool _buttonStateNow;
    // ранее состояние кнопки
    bool _buttonStateWas;
    // длинное нажатие
    bool _buttonIsOnHold;
    // время прошлого переключения кнопки
    uint32_t _lastDebouceTimeMs;
    // время прошлого переключения кнопки
    uint32_t _lastClickTimeMs;
};

#endif