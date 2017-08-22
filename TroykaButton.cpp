#include "TroykaButton.h"

TroykaButton::TroykaButton(uint8_t pin, bool pullUP) {
    _pin = pin;
    _pullUP = pullUP;
}

// инициализация кнопки
void TroykaButton::begin() {
    pinMode(_pin, INPUT);
    _msButtonState = 0;
}

// считывание состояние кнопки
void TroykaButton::read(uint32_t time) {
    _state = false;
    bool buttonStateNow = !digitalRead(_pin);
    if (!_pullUP) {
        buttonStateNow = !buttonStateNow;
    }
    if (buttonStateNow && buttonStateNow != _buttonStateWas && millis() - _msButtonState > DEBOUNCE_TIME) {
        _buttonStateNowLong = false;
        _msButtonState = millis();
        _state = ON_PRESS;
    }
    if (!buttonStateNow && buttonStateNow != _buttonStateWas &&  !_buttonStateNowLong && time && millis() - _msButtonState > DEBOUNCE_TIME) {
        _msButtonState = millis();
        _state = ON_RELEASE;
    }
    if (buttonStateNow && !_buttonStateNowLong && millis() - _msButtonState > time) {
        _buttonStateNowLong = true;
        _msButtonState = millis();
        _state = ON_PRESS_LONG;
    }
    _buttonStateWas = buttonStateNow;
}

// определение клика кнопки
bool TroykaButton::justPressed() const {
    return _state == ON_PRESS ? 1 : 0;
}

// определение отжатие кнопки
bool TroykaButton::justReleased() const {
    return _state == ON_RELEASE ? 1 : 0;
}

// определение зажатие кнопки (по умолчанию 2 секунды)
bool TroykaButton::isHold(uint32_t time) const {
    return _state == ON_PRESS_LONG ? 1 : 0;
}
