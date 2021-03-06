#pragma once
#include "Gate.h"
#include<fstream>
using namespace std;
class Switch :public Gate
{
public:
	Switch(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf, string s);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(UI*);
	virtual void save(ofstream& data);	//Draws 2-input gate
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual int copy();
	int checker(GraphicsInfo* r_GfxInfo);
	void settrandfa(bool s);
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


};
