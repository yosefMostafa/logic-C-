#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"
#include<fstream>
using namespace std;
class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;	
public:
	Gate(GraphicsInfo* pGfxInfo, int r_Inputs, int r_FanOut);
	bool selected(int x, int y);
	virtual void save(ofstream &data);
	virtual void settrandfa(bool s);
	virtual bool gettrandfa();
	virtual void setlabel(string s);
	OutputPin* getout() { return &m_OutputPin;};
	InputPin* getin(int x) { return &m_InputPins[x];};
	virtual void setGInfo(GraphicsInfo* r_GfxInfo);
	virtual void getlabel(string& s);
	virtual void getGInfo(GraphicsInfo* r_GfxInfo);
	virtual int copy() { return NULL; };
	int checker(GraphicsInfo* r_GfxInfo);
};

#endif
