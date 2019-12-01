#include "XOR.h"




XOR::XOR(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf;
}


void XOR::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void XOR::Draw(UI* pUI)
{
	if (trandfa) {
		//Call output class and pass gate drawing info to it.
		pUI->DrawXOR(*m_pGfxInfo, trandfa);
	}
	else {
		pUI->DrawXOR(*m_pGfxInfo, trandfa);
	}
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
