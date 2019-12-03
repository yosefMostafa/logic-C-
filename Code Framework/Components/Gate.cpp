#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(GraphicsInfo* pGfxInfo, int r_Inputs, int r_FanOut):Component(pGfxInfo), m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
}
bool Gate::selected(int x, int y) {
		if (x >= m_pGfxInfo->PointsList[0].x &&x <= m_pGfxInfo->PointsList[1].x && y >= m_pGfxInfo->PointsList[0].y && y <= m_pGfxInfo->PointsList[1].y) {
			return true;
		}
		else {
			return false;
		}
}