#include "XOR.h"




XOR::XOR(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf,string s) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf; label = s;
}


void XOR::Operate()
{
	if ((m_InputPins[0].getStatus() == HIGH && m_InputPins[1].getStatus() == LOW)||
		(m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == HIGH)) {
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
void XOR::Draw(UI* pUI)
{
		//Call output class and pass gate drawing info to it.
		pUI->DrawXOR(*m_pGfxInfo, trandfa,label);
}

//returns status of outputpin
int XOR::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void XOR::save(ofstream& data) {
	data << XOR1 << "  " << label << "  " << m_pGfxInfo->PointsList[0].x << "  " << m_pGfxInfo->PointsList[0].y << "  " << m_pGfxInfo->PointsList[1].x << "  " << m_pGfxInfo->PointsList[1].y << endl;
}
int XOR::copy() {
	return XOR1;
}