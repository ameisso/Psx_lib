/*  PSX Controller Decoder Library (Psx.cpp)
	Written by: Kevin Ahrendt June 22nd, 2008
	
	Controller protocol implemented using Andrew J McCubbin's analysis.
	http://www.gamesx.com/controldata/psxcont/psxcont.htm
	
	Shift command is based on tutorial examples for ShiftIn and ShiftOut
	functions both written by Carlyn Maw and Tom Igoe
	http://www.arduino.cc/en/Tutorial/ShiftIn
	http://www.arduino.cc/en/Tutorial/ShiftOut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Psx.h"

Psx::Psx()
{
}

byte Psx::shift(byte _dataOut) // Does the actual shifting, both in and out simultaneously
{
	_temp = 0;
	_dataIn = 0;

	for (_i = 0; _i <= 7; _i++)
	{
		if (_dataOut & (1 << _i))
			digitalWrite(_cmndPin, HIGH); // Writes out the _dataOut bits
		else
			digitalWrite(_cmndPin, LOW);
		digitalWrite(_clockPin, LOW);
		delayMicroseconds(_delay);
		_temp = digitalRead(_dataPin); // Reads the data pin
		if (_temp)
		{
			_dataIn = _dataIn | (B10000000 >> _i); // Shifts the read data into _dataIn
		}
		digitalWrite(_clockPin, HIGH);
		delayMicroseconds(_delay);
	}
	return _dataIn;
}

void Psx::setupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin, byte delay)
{
	pinMode(dataPin, INPUT_PULLUP);
	_dataPin = dataPin;

	pinMode(cmndPin, OUTPUT);
	_cmndPin = cmndPin;

	pinMode(attPin, OUTPUT);
	_attPin = attPin;
	digitalWrite(_attPin, HIGH);

	pinMode(clockPin, OUTPUT);
	_clockPin = clockPin;
	digitalWrite(_clockPin, HIGH);

	_delay = delay;
}

void Psx::update()
{
	digitalWrite(_attPin, LOW);

	shift(0x01);
	shift(0x42);
	shift(0xFF);

	_data1 = ~shift(0xFF);
	_data2 = ~shift(0xFF);

	digitalWrite(_attPin, HIGH);

	_dataOut = (_data2 << 8) | _data1;

	if (_previousData != _dataOut)
	{
		if (_dataOut & psxLeft && _leftCallback && !_leftPressed)
		{
			_leftPressed = true;
			_leftCallback(_leftPressed);
		}
		if (_dataOut & psxDown && _downCallback && !_downPressed)
		{
			_downPressed = true;
			_downCallback(_downPressed);
		}
		if (_dataOut & psxRight && _rightCallback && !_rightPressed)
		{
			_rightPressed = true;
			_rightCallback(_rightPressed);
		}
		if (_dataOut & psxUp && _upCallback && !_upPressed)
		{
			_upPressed = true; 
			_upCallback(_upPressed);
		}
		if (_dataOut & psxStart && _startCallback && !_startPressed)
		{
			_startPressed = true;
			_startCallback(_startPressed);
		}
		if (_dataOut & psxSelect && _selectCallback && !_selectPressed)
		{
			_selectPressed = true;
			_selectCallback(_selectPressed);
		}
		if (_dataOut & psxSquare && _squareCallback && !_squarePressed)
		{
			_squarePressed = true;
			_squareCallback(_squarePressed);
		}
		if (_dataOut & psxCross && _crossCallback && !_crossPressed)
		{
			_crossPressed = true;
			_crossCallback(_crossPressed);
		}
		if (_dataOut & psxRound && _roundCallback && !_roundPressed)
		{
			_roundPressed = true;
			_roundCallback(_roundPressed);
		}
		if (_dataOut & psxTriangle && _triangleCallback && !_trianglePressed)
		{
			_trianglePressed = true;
			_triangleCallback(_trianglePressed);
		}
		if (_dataOut & psxR1 && _R1Callback && !_R1Pressed)
		{
			_R1Pressed = true;
			_R1Callback(_R1Pressed);
		}
		if (_dataOut & psxL1 && _L1Callback && !_L1Pressed)
		{
			_L1Pressed = true;
			_L1Callback(_L1Pressed);
		}
		if (_dataOut & psxR2 && _R2Callback && !_R2Pressed)
		{
			_R2Pressed = true;
			_R2Callback(_R2Pressed);
		}
		if (_dataOut & psxL2 && _L2Callback && !_L2Pressed)
		{
			_L2Pressed = true;
			_L2Callback(_L2Pressed);
		}

		//RELEASED
		if (!(_dataOut & psxLeft) && _leftCallback && _leftPressed)
		{
			_leftPressed = false;
			_leftCallback(_leftPressed);
		}
		if (!(_dataOut & psxDown) && _downCallback && _downPressed)
		{
			_downPressed = false;
			_downCallback(_downPressed);
		}
		if (!(_dataOut & psxRight) && _rightCallback && _rightPressed)
		{
			_rightPressed = false;
			_rightCallback(_rightPressed);
		}
		if (!(_dataOut & psxUp) && _upCallback && _upPressed)
		{
			_upPressed = false;
			_upCallback(_upPressed);
		}
		if (!(_dataOut & psxStart) && _startCallback && _startPressed)
		{
			_startPressed = false;
			_startCallback(_startPressed);
		}
		if (!(_dataOut & psxSelect) && _selectCallback && _selectPressed)
		{
			_selectPressed = false;
			_selectCallback(_selectPressed);
		}
		if (!(_dataOut & psxSquare) && _squareCallback && _squarePressed)
		{
			_squarePressed = false;
			_squareCallback(_squarePressed);
		}
		if (!(_dataOut & psxCross) && _crossCallback && _crossPressed)
		{
			_crossPressed = false;
			_crossCallback(_crossPressed);
		}
		if (!(_dataOut & psxRound) && _roundCallback && _roundPressed)
		{
			_roundPressed = false;
			_roundCallback(_roundPressed);
		}
		if (!(_dataOut & psxTriangle) && _triangleCallback && _trianglePressed)
		{
			_trianglePressed = false;
			_triangleCallback(_trianglePressed);
		}
		if (!(_dataOut & psxR1) && _R1Callback && _R1Pressed)
		{
			_R1Pressed = false;
			_R1Callback(_R1Pressed);
		}
		if (!(_dataOut & psxL1) && _L1Callback && _L1Pressed)
		{
			_L1Pressed = false;
			_L1Callback(_L1Pressed);
		}
		if (!(_dataOut & psxR2) && _R2Callback && _R2Pressed)
		{
			_R2Pressed = false;
			_R2Callback(_R2Pressed);
		}
		if (!(_dataOut & psxL2) && _L2Callback && _L2Pressed)
		{
			_L2Pressed = false;
			_L2Callback(_L2Pressed);
		}
	}
	_previousData = _dataOut;
}

void Psx::setLeftCallback(void (*leftCallback)(bool state))
{
	_leftCallback = leftCallback;
}
void Psx::setDownCallback(void (*downCallback)(bool state))
{
	_downCallback = downCallback;
}
void Psx::setRightCallback(void (*rightCallback)(bool state))
{
	_rightCallback = rightCallback;
}
void Psx::setUpCallback(void (*upCallback)(bool state))
{
	_upCallback = upCallback;
}
void Psx::setStartCallback(void (*startCallback)(bool state))
{
	_startCallback = startCallback;
}
void Psx::setSelectCallback(void (*selectCallback)(bool state))
{
	_selectCallback = selectCallback;
}
void Psx::setSquareCallback(void (*squareCallback)(bool state))
{
	_squareCallback = squareCallback;
}
void Psx::setCrossCallback(void (*crossCallback)(bool state))
{
	_crossCallback = crossCallback;
}
void Psx::setRoundCallback(void (*roundCallback)(bool state))
{
	_roundCallback = roundCallback;
}
void Psx::setTriangleCallback(void (*triangleCallback)(bool state))
{
	_triangleCallback = triangleCallback;
}
void Psx::setR1Callback(void (*R1Callback)(bool state))
{
	_R1Callback = R1Callback;
}
void Psx::setL1Callback(void (*L1Callback)(bool state))
{
	_L1Callback = L1Callback;
}
void Psx::setR2Callback(void (*R2Callback)(bool state))
{
	_R2Callback = R2Callback;
}
void Psx::setL2Callback(void (*L2Callback)(bool state))
{
	_L2Callback = L2Callback;
}


// GETTERS
bool Psx::getLeft()
{
	return _leftPressed;
}
bool Psx::getDown()
{
	return _downPressed;
}
bool Psx::getRight()
{
	return _rightPressed;
}
bool Psx::getUp()
{
	return _upPressed;
}

bool Psx::getSelect()
{
	return _selectPressed;
}
bool Psx::getStart()
{
	return _startPressed;
}

bool Psx::getSquare()
{
	return _squarePressed;
}
bool Psx::getCross()
{
	return _crossPressed;
}
bool Psx::getRound()
{
	return _roundPressed;
}
bool Psx::getTriangle()
{
	return _trianglePressed;
}

bool Psx::getR1()
{
	return _R1Pressed;
}
bool Psx::getL1()
{
	return _L1Pressed;
}
bool Psx::getR2()
{
	return _R2Pressed;
}
bool Psx::getL2()
{
	return _L2Pressed;
}