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
        _state = ON_RELEASE;
        _msButtonState = millis();
    }
    if (buttonStateNow && !_buttonStateNowLong && millis() - _msButtonState > time) {
        _buttonStateNowLong = true;
        _state = ON_PRESS_LONG;
        _msButtonState = millis();
    }
    _buttonStateWas = buttonStateNow;
}

// определение клика кнопки
bool TroykaButton::onPress() {
    read();
    if (_state == ON_PRESS) {
        _state = false;
        return true;
    } else {
        return false;
    }
}

// определение отжатие кнопки
bool TroykaButton::onRelease() {
    read();
    if (_state == ON_RELEASE) {
        _state = false;
        return true;
    } else {
        return false;
    }
}

// определение зажатие кнопки (по умолчанию 2 секунды)
bool TroykaButton::isPressed(uint32_t time) {
    read(time);
    if (_state == ON_PRESS_LONG) {
        _state = false;
        return true;
    } else {
        return false;
    }
}
