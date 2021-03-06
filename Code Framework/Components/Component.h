#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\UI\UI.h"
#include<fstream>
using namespace std;
class OutputPin;
class InputPin;
//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
protected:
	GraphicsInfo *m_pGfxInfo;	//The parameters required to draw a component
	bool trandfa;
	string label;
public:
	enum pin {
		ncon,
		in1,
		in2,
		out,
		led,
		on
	};
	enum gate {
		AND,
		OR,
		NAND,
		XOR1,
		LINE,
		XNOR1,
		NOR1,
		LED,
		Switch1,
		NOT1,
		LEBGHT
	};
	Component(GraphicsInfo *r_GfxInfo);
	virtual void settrandfa(bool s)=0;
	virtual bool gettrandfa() = 0;
	virtual void setlabel(string s) = 0;
	virtual void getlabel(string &s) = 0;
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(UI* ) = 0;	//for each component to Draw itself
	virtual bool selected(int x,int y) = 0;
	virtual void save(ofstream &data) = 0;
	virtual int copy() = 0;
	virtual int checker(GraphicsInfo* r_GfxInfo) = 0;
	virtual void setGInfo(GraphicsInfo* r_GfxInfo) = 0;
	virtual void getGInfo(GraphicsInfo* r_GfxInfo) = 0;
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual OutputPin* getout() =0;
	virtual InputPin* getin(int x) =0;
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
