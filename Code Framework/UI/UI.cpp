#include "UI.h"

UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = RED;
	MsgColor = RED;
	BkGrndColor =WHITE;
	
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Logic Simulator Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}


int UI::getGateWidth() const
{
	return GATE_Width;
}

int UI::getGateHeight() const
{
	return GATE_Height;
}

//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string UI::GetSrting()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);

		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			return userInput;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		
		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() 
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	lastclicky = y;
	lastclickx = x;
	if(AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_XOR: return ADD_XOR_GATE_2;
			case ITM_XNOR: return ADD_XNOR_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_DELETE: return DEL;
			case ITM_pen:return ADD_CONNECTION;	
			case ITM_EXIT: return EXIT;	
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}



//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar()
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_pen] = "images\\Menu\\pen.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\OR.jpg";
	MenuItemImages[ITM_XOR] = "images\\Gates\\XOR.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Gates\\NOR.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Gates\\NAND.jpg";
	MenuItemImages[ITM_XNOR] = "images\\Gates\\XNOR.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\delete.jpg";
	MenuItemImages[ITM_UNDO] = "images\\Menu\\Undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\Menu\\Redo.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Load.jpg";






	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++) {
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 20);
	string gatelabel[13]= { "AND","NAND","OR","NOR","XOR","XNOR","PEN","Delete","Undo","Redo","Save","Load","EXIT" };
	for (int i = 0; i < 13; i++) {
		pWind->DrawString(i * ToolItemWidth + 30, 85, gatelabel[i]);
	}
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, ToolBarHeight + 15, width, ToolBarHeight + 15);
	pWind->SetPen(BLACK, 1);
	for (int i = 0; i < width; i = i + 15) {
		pWind->DrawLine(i,100 , i, height-50);
	}
	for (int i = 0; i < height-150; i = i + 15) {
		pWind->DrawLine(0,i+100, width,i+100);
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawAND2(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected) {//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2.jpg";
	}
	else {
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	}

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}
void UI::DrawNAND2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected) {//use image in the highlighted case
		GateImage = "Images\\Gates\\NAND.jpg";
	}
	else {
		GateImage = "Images\\Gates\\NAND_Hi.jpg";
	}

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}
void UI::DrawOR2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\OR.jpg";
	else
		GateImage = "Images\\Gates\\OR_Hi.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

//TODO: Add similar functions to draw all components


void UI::DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected) 
{
	pWind->SetPen(BLACK, 5);
	pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[0].y);
	pWind->DrawLine(r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);//TODO: Add code to draw connection
}


UI::~UI()
{
	delete pWind;
}