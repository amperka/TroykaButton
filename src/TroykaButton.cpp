/****************************************************************************/
//  Function:       Cpp file for TroykaButton
//  Arduino IDE:    Arduino-1.8.5
//  Author:         Igor Dementiev
//  Date:           Sep 09,2018
//  Version:        v1.0
//  by www.amperka.ru
/****************************************************************************/

#include "TroykaButton.h"

TroykaButton::TroykaButton(uint8_t pin, uint32_t timeHold, bool pullUP) {
    _pin = pin;
    _timeHold = timeHold;
    _pullUP = pullUP;
}

// инициализация кнопки
void TroykaButton::begin() {
    pinMode(_pin, INPUT);
    _msButtonState = 0;
    _buttonStateOld = ON_RELEASE;
	_isClick = false;
}

// считывание состояние кнопки
void TroykaButton::read() {
    _stateButton = false;
    _isClick = false;
    bool buttonStateNow = !digitalRead(_pin);
    if (!_pullUP) {
        buttonStateNow = !buttonStateNow;
    }
    if (buttonStateNow && buttonStateNow != _buttonStateWas && millis() - _msButtonState > DEBOUNCE_TIME) {
        _buttonStateNowLong = false;
        _msButtonState = millis();
        _stateButton = ON_PRESS;
        _buttonStateOld =  _stateButton;
    }
    if (!buttonStateNow && buttonStateNow != _buttonStateWas && millis() - _msButtonState > DEBOUNCE_TIME) {
        _msButtonState = millis();
        _stateButton = ON_RELEASE;
    }
    if (buttonStateNow && !_buttonStateNowLong && millis() - _msButtonState > _timeHold) {
        _buttonStateNowLong = true;
        _msButtonState = millis();
        _stateButton = ON_PRESS_LONG;
        _buttonStateOld =  _stateButton;
    }
    if (_stateButton == ON_RELEASE && _buttonStateOld == ON_PRESS ) {
		_buttonStateOld = ON_RELEASE;
        _isClick = true;
    }
    _buttonStateWas = buttonStateNow;
}

// определение клика кнопки
bool TroykaButton::justPressed() const {
    return _stateButton == ON_PRESS ? 1 : 0;
}

// определение отжатие кнопки
bool TroykaButton::justReleased() const {
    return _stateButton == ON_RELEASE ? 1 : 0;
}

// определение зажатие кнопки (по умолчанию 2 секунды)
bool TroykaButton::isHold() const {
    return _stateButton == ON_PRESS_LONG ? 1 : 0;
}

// определение короткого клика, если сработал метод isHold() клик не сработает.
bool TroykaButton::isClick() const {
    return _isClick;
}
