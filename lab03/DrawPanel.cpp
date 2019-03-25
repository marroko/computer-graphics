#include "DrawPanel.h"

void DrawPanel::drawText(wxDC &DC) {

	wxString horizontalText(text);
	DC.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri"));
	DC.DrawText(horizontalText, -60, 100);

	wxString verticalText(text);
	DC.SetFont(wxFont(20, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, "Times New Roman"));
	DC.DrawRotatedText(verticalText, 40, 100, 90);
}

void DrawPanel::drawCharacter(wxDC &DC) {

	DC.DrawCircle(0, -characterSize - 30, 30); // head
	DC.DrawEllipse(-10, -characterSize*2, 10, 12); // eyes
	DC.DrawEllipse(10, -characterSize*2, 10, 12);

	if (isBananaShown) {

		DC.DrawEllipticArc(-12, -60, 25, 10, 180, 360); // positive face
		DC.DrawBitmap(image, -60, -5 - armHeight / 3.0); 
	}
	else
		DC.DrawEllipticArc(-12, -60, 25, 10, 0, 180); // negative face

	DC.DrawLine(0, -characterSize, 0, characterSize); // body

	DC.DrawLine(0, -characterSize / 2, -35, 15 - armHeight / 3.0); // left arm
	DC.DrawLine(0, -characterSize / 2, 35, 15); // right arm

	DC.DrawLine(0, characterSize, -30, 100); // left leg
	DC.DrawLine(0, characterSize, 30, 100); // right leg

	DC.SetBrush(*wxBLACK_BRUSH);

	DC.DrawCircle(-6, -characterSize * 2 + 5, 2); // pupils
	DC.DrawCircle(14, -characterSize * 2 + 5, 2);
}

void DrawPanel::drawStar(wxDC &DC) {

	DC.SetBrush(figureColor);
	DC.SetPen(figureColor);

	wxPoint polygon[5] = {

		figureCoords + wxPoint(0,0),
		figureCoords + wxPoint(30,135),
		figureCoords + wxPoint(-60,60),
		figureCoords + wxPoint(60,60),
		figureCoords + wxPoint(-30,135),
	};
	DC.DrawPolygon(5, polygon, figureCoords.x, figureCoords.y);
}

void DrawPanel::drawMoon(wxDC &DC) {

	DC.SetBrush(figureColor);
	DC.SetPen(figureColor);
	DC.DrawCircle(figureCoords.x, figureCoords.y, 30); // whole moon

	DC.SetBrush(*wxWHITE_BRUSH);
	DC.SetPen(*wxWHITE_PEN);
	DC.DrawCircle(figureCoords.x - 20, figureCoords.y, 30); // make half-moon

	DC.SetBrush(*wxBLACK_BRUSH);
	DC.SetPen(*wxBLACK_PEN);
	DC.DrawCircle(figureCoords.x + 10, figureCoords.y - 15, 4); // eye
	DC.DrawLine(figureCoords.x + 10, figureCoords.y + 5, figureCoords.x + 20, figureCoords.y); // smile
}

void DrawPanel::drawSun(wxDC &DC) {

	DC.SetBrush(figureColor);
	DC.SetPen(figureColor);
	DC.DrawCircle(figureCoords.x, figureCoords.y, 30);
	DC.SetBrush(*wxBLACK_BRUSH);
	DC.SetPen(*wxBLACK_PEN);
	DC.DrawCircle(figureCoords.x - 5, figureCoords.y - 7, 4); // eyes
	DC.DrawCircle(figureCoords.x + 20, figureCoords.y - 7, 4);

	DC.SetBrush(figureColor);
	DC.DrawEllipticArc(figureCoords.x - 20, figureCoords.y - 5, 40, 25, 180, 360); // smile
}

void DrawPanel::paintEvent(wxPaintEvent &event) {

	wxPaintDC paintDC(this);
	panelSize = this->GetSize();

	mainPanelBuffer = wxBitmap(panelSize);
	wxBufferedDC DC(&paintDC, mainPanelBuffer);
	render(DC);
}

void DrawPanel::render(wxDC &DC) {

	DC.SetDeviceOrigin(panelSize.x / 2, panelSize.y / 2);
	DC.SetBackground(*wxWHITE_BRUSH);
	DC.Clear();

	this->drawCharacter(DC);
	(*this.*whichFigureToDraw)(DC);
	this->drawText(DC);
}

BEGIN_EVENT_TABLE(DrawPanel, wxPanel)
EVT_PAINT(DrawPanel::paintEvent)
END_EVENT_TABLE()