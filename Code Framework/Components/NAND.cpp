#include "NAND.h"




NAND2::NAND2(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf,string s) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf; label = s;
}


void NAND2::Operate()
{
	if (m_InputPins[0].getStatus() == HIGH && m_InputPins[1].getStatus() == HIGH) {
		m_OutputPin.setStatus(LOW);
		settrandfa(true);
	}
	else {
		m_OutputPin.setStatus(HIGH);
		settrandfa(false);
	}
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void NAND2::Draw(UI* pUI)
{
	
		//Call output class and pass gate drawing info to it.
	pUI->DrawNAND2(*m_pGfxInfo, trandfa, label);
}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void NAND2::save(ofstream& data) {
	data << NAND << "  " << label << "  " << m_pGfxInfo->PointsList[0].x << "  " << m_pGfxInfo->PointsList[0].y << "  " << m_pGfxInfo->PointsList[1].x << "  " << m_pGfxInfo->PointsList[1].y << endl;
}
int NAND2::copy() {
	return NAND;
}