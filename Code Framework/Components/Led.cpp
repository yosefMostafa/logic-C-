#include "Led.h"




Led::Led(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf, string s) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf; label = s;
}


void Led::Operate()
{
	if (m_InputPins[0].getStatus()==HIGH) {
		m_OutputPin.setStatus(HIGH);
		settrandfa(false);
	}
	else {
		m_OutputPin.setStatus(LOW);
		settrandfa(true);
	}
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void Led::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->Drawled(*m_pGfxInfo, trandfa, label);

}

//returns status of outputpin
int Led::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int Led::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void Led::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void Led::save(ofstream& data) {

	data << LED << "  " << label << "  " << m_pGfxInfo->PointsList[0].x << "  " << m_pGfxInfo->PointsList[0].y << "  " << m_pGfxInfo->PointsList[1].x << "  " << m_pGfxInfo->PointsList[1].y << endl;
} 
int Led::copy() {
	return LED;
}
int Led::checker(GraphicsInfo* r_GfxInfo) {
	if (selected(r_GfxInfo->PointsList[0].x, r_GfxInfo->PointsList[0].y)) {
		if (r_GfxInfo->PointsList[0].x >= (m_pGfxInfo->PointsList[0].x + 25)) {
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[1].x-20;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[1].y;
			return out;
		}
		else {
			r_GfxInfo->PointsList[0].x = m_pGfxInfo->PointsList[0].x+20;
			r_GfxInfo->PointsList[0].y = m_pGfxInfo->PointsList[1].y;
			return in1;
		}
	}
	return ncon;
}