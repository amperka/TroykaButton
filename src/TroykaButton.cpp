/****************************************************************************/
//  Function:       Cpp file for TroykaButton
//  Arduino IDE:    Arduino-1.8.5
//  Author:         Igor Dementiev
//  Date:           Sep 09,2018
//  Version:        v1.0
//  by www.amperka.ru
/****************************************************************************/

#include "TroykaButton.h"

TroykaButton::TroykaButton(uint8_t pin, uint32_t timeHold, bool pullUP, uint32_t repeatDelay) {
    _pin = pin;
    _timeHold = timeHold;
    _repeatDelay = repeatDelay;
    _pullUP = pullUP;
}

// инициализация кнопки
void TroykaButton::begin() {
    pinMode(_pin, _pullUP ? INPUT_PULLUP : INPUT);
    _lastDebouceTimeMs = 0;
    _buttonStateWas = 0;
    _buttonStateNow = 0;
    _isClick = false;
    _isClickOnHold = false;
    _buttonEventState = NONE;
    _buttonEventStateOld = NONE;
    _buttonIsOnHold = false;
}

// считывание состояние кнопки
void TroykaButton::read() {
    _buttonEventState = NONE;
    _isClick = false;
    _isClickOnHold = false;
    _buttonIsOnHold = false;
    // Считываем текущее состояние кнопки
    _buttonStateNow = digitalRead(_pin);

    // Инвертируем значение если включена подтяжка
    if (_pullUP)
        _buttonStateNow = !_buttonStateNow;

    // Обработка кнопки

    uint32_t timeNow = millis();

    if (_buttonStateNow != _buttonStateWas) {// Если произошло новое событие
        if (timeNow - _lastDebouceTimeMs < DEBOUNCE_TIME) { // Если время нас не устраивает то это дребезг
            _lastDebouceTimeMs = timeNow;
            return;
        }

        if (_buttonStateNow) {
            _buttonEventState = ON_PRESS; // Клавиша нажата
        } else {
            _buttonEventState = ON_RELEASE; // Клавиша отпущена
            if (_buttonEventStateOld == ON_PRESS) // Если перед этим клавиша была просто нажата
               _isClick = true;  // то это еще и клик
        }
        _lastDebouceTimeMs = timeNow;

    } else { // Если события не произошло
        if (_buttonStateNow && ((timeNow - _lastDebouceTimeMs) > _timeHold)) { // Если клавиша зажата и с прошлого нажатия прошло время
            _buttonIsOnHold = true; // То это длительное нажатие
            _buttonEventState = ON_PRESS_LONG;
            if (_repeatDelay && ((timeNow - _lastClickTimeMs) > _repeatDelay)) {
                _isClickOnHold = true;
                _lastClickTimeMs = timeNow;
            }
        }
    }

    if (_buttonEventState)
        _buttonEventStateOld = _buttonEventState;

    _buttonStateWas = _buttonStateNow;
}

// определение клика кнопки
bool TroykaButton::justPressed() const {
    return _buttonEventState == ON_PRESS ? 1 : 0;
}

// определение отжатие кнопки
bool TroykaButton::justReleased() const {
    return _buttonEventState == ON_RELEASE ? 1 : 0;
}

// определение зажатие кнопки (по умолчанию 2 секунды)
bool TroykaButton::isHold() const {
    return _buttonIsOnHold;
}

// определение короткого клика, если сработал метод isHold() клик не сработает.
bool TroykaButton::isClick() const {
    return _isClick;
}

// определение автоматических кликов при длинном удержании
bool TroykaButton::isClickOnHold() const {
    return _isClickOnHold;
}

// Отпущена ли кнопка
bool TroykaButton::isReleased() const {
    return !_buttonStateNow;
}

// Нажата ли кнопка
bool TroykaButton::isPressed() const {
    return _buttonStateNow;
}
