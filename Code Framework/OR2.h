
#ifndef _OR2_H
#define _OR2_H

/*
  Class AND2
  -----------
  represent the 2-input AND gate
*/

#include "D:\zewail\Y2 Fall\C++\CIE202 - Project Fall 2019 - student\Code Framework\Components\Gate.h"

class OR2 :public Gate
{
public:
	OR2(GraphicsInfo* r_pGfxInfo, int r_FanOut,bool tf);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(UI*);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


};

#endif

