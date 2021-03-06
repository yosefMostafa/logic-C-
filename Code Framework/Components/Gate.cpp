#include "Gate.h"
#include<fstream>
using namespace std;
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
		if (x >= m_pGfxInfo->PointsList[0].x &&
			x<= m_pGfxInfo->PointsList[1].x &&
			y >= m_pGfxInfo->PointsList[0].y &&
			y <= m_pGfxInfo->PointsList[1].y) {
			return true;
		}
		else {
			return false;
		}
}
void Gate::save(ofstream &data) {

}
void Gate::settrandfa(bool s) {
	trandfa = s;
}
void Gate::setlabel(string s) {
	label = s;
}
bool Gate::gettrandfa() {
	return trandfa;
}
void Gate::setGInfo(GraphicsInfo* r_GfxInfo) {
	m_pGfxInfo = r_GfxInfo;
}
void Gate::getlabel(string& s) {
	s = label;
}
void Gate::getGInfo(GraphicsInfo* r_GfxInfo) {
	r_GfxInfo = m_pGfxInfo;
}
int Gate::checker(GraphicsInfo* r_GfxInfo) {
	if (selected(r_GfxInfo->PointsList[0].x, r_GfxInfo->PointsList[0].y)) {
		if (r_GfxInfo->PointsList[0].x >=(m_pGfxInfo->PointsList[0].x+25)) {
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[1].x;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[0].y+25;
			return out;
		}
		else if(r_GfxInfo->PointsList[0].y<= (m_pGfxInfo->PointsList[0].y+25)){
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[0].x;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[0].y + 12;
			return in1;
		}
		else {
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[0].x;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[0].y + 38;
			return in2;
		}
	}
	return ncon;
}
