/*  PSX Controller Decoder Library (Psx.h)
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

#ifndef Psx_h
#define Psx_h

#include "Arduino.h"

// Button Hex Representations:
#define psxLeft 0x0001
#define psxDown 0x0002
#define psxRight 0x0004
#define psxUp 0x0008
#define psxStart 0x0010
#define psxSelect 0x0080

#define psxSquare 0x0100
#define psxCross 0x0200
#define psxRound 0x0400
#define psxTriangle 0x0800
#define psxR1 0x1000
#define psxL1 0x2000
#define psxR2 0x4000
#define psxL2 0x8000

class Psx
{
public:
	Psx();
	void setupPins(byte, byte, byte, byte, byte);
	void update();

	void setLeftCallback(void (*leftCallback)(bool state));
	void setDownCallback(void (*downCallback)(bool state));
	void setRightCallback(void (*rightCallback)(bool state));
	void setUpCallback(void (*upCallback)(bool state));

	void setStartCallback(void (*startCallback)(bool state));
	void setSelectCallback(void (*selectCallback)(bool state));

	void setSquareCallback(void (*squareCallback)(bool state));
	void setCrossCallback(void (*crossCallback)(bool state));
	void setRoundCallback(void (*roundCallback)(bool state));
	void setTriangleCallback(void (*triangleCallback)(bool state));

	void setR1Callback(void (*R1Callback)(bool state));
	void setL1Callback(void (*L1Callback)(bool state));
	void setR2Callback(void (*R2Callback)(bool state));
	void setL2Callback(void (*L2Callback)(bool state));

	bool getLeft();
	bool getDown();
	bool getRight();
	bool getUp();

	bool getSelect();
	bool getStart();

	bool getSquare();
	bool getCross();
	bool getRound();
	bool getTriangle();

	bool getR1();
	bool getL1();
	bool getR2();
	bool getL2();


private:
	byte shift(byte _dataOut);

	byte _dataPin;
	byte _cmndPin;
	byte _attPin;
	byte _clockPin;

	byte _delay;
	byte _i;
	boolean _temp;
	byte _dataIn;

	byte _data1;
	byte _data2;
	unsigned int _dataOut;
	unsigned int _previousData;

	void (*_leftCallback)(bool state);
	void (*_downCallback)(bool state);
	void (*_rightCallback)(bool state);
	void (*_upCallback)(bool state);

	void (*_startCallback)(bool state);
	void (*_selectCallback)(bool state);

	void (*_squareCallback)(bool state);
	void (*_crossCallback)(bool state);
	void (*_roundCallback)(bool state);
	void (*_triangleCallback)(bool state);

	void (*_R1Callback)(bool state);
	void (*_L1Callback)(bool state);
	void (*_R2Callback)(bool state);
	void (*_L2Callback)(bool state);

	bool _leftPressed;
	bool _downPressed;
	bool _rightPressed;
	bool _upPressed;

	bool _squarePressed;
	bool _crossPressed;
	bool _roundPressed;
	bool _trianglePressed;

	bool _startPressed;
	bool _selectPressed;

	bool _R1Pressed;
	bool _L1Pressed;
	bool _R2Pressed;
	bool _L2Pressed;


};

#endif
