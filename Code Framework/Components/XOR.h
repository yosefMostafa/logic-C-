#pragma once
#include "Gate.h"
#include<fstream>
using namespace std;
class XOR :public Gate
{
public:
	XOR(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(UI*);	//Draws 2-input gate
	virtual void save(ofstream& data);
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


};

