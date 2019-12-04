#include "NOR.h"




NOR::NOR(GraphicsInfo* r_pGfxInfo, int r_FanOut, bool tf) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf;
}


void NOR::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void NOR::Draw(UI* pUI)
{
		//Call output class and pass gate drawing info to it.
		pUI->DrawNOR(*m_pGfxInfo, trandfa);
}

//returns status of outputpin
int NOR::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void NOR::save(ofstream& data) {
	data << NOR1 << "  " << m_pGfxInfo->PointsList[0].x << "  " << m_pGfxInfo->PointsList[0].y << "  " << m_pGfxInfo->PointsList[1].x << "  " << m_pGfxInfo->PointsList[1].y << endl;
}