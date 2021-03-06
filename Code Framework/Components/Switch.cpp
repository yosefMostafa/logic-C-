#include "Switch.h"




Switch::Switch(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf, string s) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf; label = s;
}


void Switch::Operate()
{
	if (trandfa) {
		m_OutputPin.setStatus(HIGH);
	}
	else {
		m_OutputPin.setStatus(LOW);
	}//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void Switch::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->Drawswitch(*m_pGfxInfo, trandfa, label);

}

//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int Switch::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void Switch::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void Switch::save(ofstream& data) {

	data << Switch1 << "  " << label << "  " << m_pGfxInfo->PointsList[0].x << "  " << m_pGfxInfo->PointsList[0].y << "  " << m_pGfxInfo->PointsList[1].x << "  " << m_pGfxInfo->PointsList[1].y << endl;
}
int Switch::copy() {
	return Switch1;
}
int Switch::checker(GraphicsInfo* r_GfxInfo) {
	if (selected(r_GfxInfo->PointsList[0].x, r_GfxInfo->PointsList[0].y)) {
		if (r_GfxInfo->PointsList[0].x >= (m_pGfxInfo->PointsList[0].x + 25)) {
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[1].x;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[0].y + 25;
			return on;
		}
		else {
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[1].x;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[0].y + 25;
			return on;
		}
	}
	return ncon;
}
void Switch::settrandfa(bool s) {
	if (s) {
		m_OutputPin.setStatus(HIGH);
	}
	else {
		m_OutputPin.setStatus(LOW);
	}
	trandfa = s;
}