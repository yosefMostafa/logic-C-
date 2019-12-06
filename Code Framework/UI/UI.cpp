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
	lastclickx = 0;
	lastclicky = 0;
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

void UI::GetString(string &userInput)
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 13) {
			break;
		}
		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			break; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			break;
		
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
int z = 0;
//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() 
{	
	int x,y;
	
	if (z != 0) {
		pWind->WaitMouseClick(x, y);//Get the coordinates of the user click
		lastclicky = y;
		lastclickx = x;
	}
	else {
		z = 1;
		y = 600, x = 600;
	}
	
	

	if(AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( (y >= 0 && y < ToolBarHeight)||(x>width- ToolItemWidth&&y>(ToolBarHeight)&& y < (height- StatusBarHeight)))
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
				if (ClickedItemOrder == 15 && y > ToolBarHeight + 15) {
					ClickedItemOrder = 15+((y-20)/ ToolBarHeight);
				}
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_XOR: return ADD_XOR_GATE_2;
			case ITM_XNOR: return ADD_XNOR_GATE_2;
			case ITM_SM: CreateSimulationToolBar();
				break;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_DELETE: return DEL;
			case ITM_UNDO:return UNDO;
			case ITM_REDO:return REDO;
			case ITM_SAVE:return SAVE;
			case ITM_LOAD:return LOAD;
			case ITM_EDIT:return EDIT_Label;
			case ITM_UNSELECT:return USELECT;
			case ITM_pen:return ADD_CONNECTION;	
			case ITM_SWITCH:return ADD_Switch;
			case ITM_LED:return ADD_LED;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_MOVE: return MOVE;
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
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case IIM_TRUTHTABLE: return TRUTH_TABLE;
			case ITM_DM:CreateDesignToolBar();
				break;
			case EXIT1:return EXIT;
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}	//This should be changed after creating the compelete simulation bar 
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
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
	pWind->SetPen(BLACK,3);
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
	pWind->SetPen(WHITE, 1);
	pWind->DrawRectangle(0, 0, width, ToolBarHeight + 14);
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Gates\\Gate_AND2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_pen] = "images\\Menu\\WIRE.jpg";
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
	MenuItemImages[ITM_SM] = "images\\Menu\\SM.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Menu\\pen.jpg";
	MenuItemImages[ITM_UNSELECT] = "images\\Menu\\unselect.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\one.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\LAMP.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\Menu\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\paste.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\move.jpg";



	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	int j = 1;
	for (int i = 0; i < ITM_DSN_CNT; i++) {
		if (i>= 16) {
			pWind->DrawImage(MenuItemImages[i], width- (ToolItemWidth+14), (ToolBarHeight+15)*(j), ToolItemWidth, ToolBarHeight);
			j++;
		}
		else {
			pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);
		}
	}
	int n = 1;
	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15,5, MODERN);
	string gatelabel[22]= { "AND","NAND","OR","NOR","XOR","XNOR","WIRE","Delete","Undo","Redo","Save","Load","Edit label","Simulation","unselect","EXIT","Switch","LED","Copy","Cut","Paste","Move" };
	for (int i = 0; i < 22; i++) {
		if (i==12||i==13) {
			pWind->DrawString(i * ToolItemWidth +10, 80, gatelabel[i]);
		}
		else if(i>=16){
			pWind->DrawString(width-(ToolItemWidth+12) ,65+ ToolItemWidth *(n), gatelabel[i]);
			n++;
		}else {
			pWind->DrawString(i * ToolItemWidth +25, 80, gatelabel[i]);
		}
	}
	pWind->SetPen(BLACK,3);
	pWind->DrawLine(0, ToolBarHeight + 15, width, ToolBarHeight + 15);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(width - 95, 95, width - 95, height - 50);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode
	pWind->SetPen(WHITE, 1);
	pWind->DrawRectangle(0, 0, width, ToolBarHeight+14);
	pWind->DrawRectangle(width -(ToolItemWidth+13), ToolBarHeight+13, width, height - StatusBarHeight);
	string STbarItemImages[ITM_STN_CNT];
	STbarItemImages[IIM_TRUTHTABLE] = "images\\Menu\\TTL.jpg";
	STbarItemImages[ITM_DM] = "images\\Menu\\Load.jpg";
	STbarItemImages[EXIT1] = "images\\Menu\\Menu_Exit.jpg";
	for (int i = 0; i < ITM_STN_CNT; i++) {
		pWind->DrawImage(STbarItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	string gatelabel[3] = { "TRuth Table","Design mode" ,"Exit program"};
	for (int i = 0; i < 3; i++) {
			pWind->DrawString(i * ToolItemWidth, 80, gatelabel[i]);
	}
	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)

}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawAND2(const GraphicsInfo &r_GfxInfo, bool selected,string f) const
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
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x+GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y+GATE_Height + 5, f);
}
void UI::DrawNAND2(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
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
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
void UI::DrawOR2(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\OR.jpg";
	else
		GateImage = "Images\\Gates\\OR_Hi.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
void UI::DrawXOR(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XOR.jpg";
	else
		GateImage = "Images\\Gates\\XOR_Hi.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
void UI::DrawXNOR(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XNOR.jpg";
	else
		GateImage = "Images\\Gates\\XNOR_Hi.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
void UI::DrawNOR(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NOR.jpg";
	else
		GateImage = "Images\\Gates\\NOR_Hi.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
void UI::Drawled(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\ON_LAMP.jpg";
	else
		GateImage = "Images\\Gates\\ON_LAMP _Hi.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
void UI::Drawswitch(const GraphicsInfo& r_GfxInfo, bool selected, string f) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\one.jpg";
	else
		GateImage = "Images\\Gates\\zero.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString((r_GfxInfo.PointsList[0].x + GATE_Width / 2) - 20, r_GfxInfo.PointsList[0].y + GATE_Height + 5, f);
}
//TODO: Add similar functions to draw all components


void UI::DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected, string f)
{
	
	if (selected) {
		pWind->SetPen(BLACK, 5);
	}else{
		pWind->SetPen(RED, 5);
	}
	if (r_GfxInfo.PointsList[0].y > ToolBarHeight+15 && r_GfxInfo.PointsList[1].y < height-StatusBarHeight&& r_GfxInfo.PointsList[0].y < height - StatusBarHeight&& r_GfxInfo.PointsList[1].y > ToolBarHeight+15&& r_GfxInfo.PointsList[0].x < width-100&& r_GfxInfo.PointsList[1].x < width - 100) {
		pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[0].y);
		pWind->DrawLine(r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);//TODO: Add code to draw connection
	}
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	pWind->DrawString(((r_GfxInfo.PointsList[0].x + r_GfxInfo.PointsList[1].x) / 2), r_GfxInfo.PointsList[0].y-25, f);
}


UI::~UI()
{
	delete pWind;
}
void UI::drawRectangle(int x, int y, int x1, int y1) {
	pWind->SetPen(WHITE, 1);
	pWind->DrawRectangle(x, y,x1, y1);
}
void UI::drawline(int x, int y, int x1, int y1) {
	pWind->SetPen(GREY, 1);
	pWind->DrawLine(x, y, x1, y1);
}
int UI::getlastclickx() {
	return lastclickx;
}
int UI::getlastclicky() {
	return lastclicky;
}
void UI::drawstring(int x, int y, string f) {
	pWind->DrawString(x, y, f);
}
void UI::WaitKeyPress(char& key) {
	pWind->WaitKeyPress(key);
}

