#pragma once
#include <iostream>
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"
#include<fstream>
using namespace std;
class Connection :	public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	//int		DstPin;		//The Input pin to which this connection is linked
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
public:
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(GraphicsInfo *r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin, bool trfa, string s);
	Connection(GraphicsInfo* r_GfxInfo,bool trfa,string s);
	virtual void Operate() ;	//Calculates the output according to the inputs
	virtual void Draw(UI* );//for each component to Draw itself
	virtual bool selected(int x, int y);
	virtual void save(ofstream &data);
	virtual void settrandfa(bool s);
	virtual void setlabel(string s);
	virtual void getlabel(string &s);
	virtual bool gettrandfa();
	virtual void getGInfo(GraphicsInfo* r_GfxInfo);
	virtual void setGInfo(GraphicsInfo* r_GfxInfo);
	virtual int copy();
	int checker(GraphicsInfo* r_GfxInfo) { return ncon; };
	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();
	OutputPin* getout() { return SrcPin; };
	InputPin* getin(int x) { return  DstPin; };


	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


};
