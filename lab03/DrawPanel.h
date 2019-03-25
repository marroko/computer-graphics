#pragma once
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/settings.h>
#include <wx/string.h>

class DrawPanel : public wxPanel {

public:

	DrawPanel(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString &name = wxPanelNameStr) : wxPanel(parent, id, pos, size, style) {}
	~DrawPanel() = default;

	// inline methods
	void setArmHeight(int height) { armHeight = height; }
	void changeBananaVisibility(bool value) { isBananaShown = value; }
	void setImage(wxBitmap newImage) { image = newImage; }
	void setText(wxString string) { text = string; }
	void setFigureColor(wxColor color) { figureColor = color; }

	wxBitmap getBuffer() { return mainPanelBuffer;  }
	wxString getFigureText() { return colorFigureText; }
	void setFigureText(wxString string) { colorFigureText = string; }
	// end inline methods

	void drawText(wxDC &DC);
	void drawCharacter(wxDC &DC);

	void (DrawPanel::*whichFigureToDraw)(wxDC &) = &DrawPanel::drawStar;
	void drawStar(wxDC &DC);
	void drawMoon(wxDC &DC);
	void drawSun(wxDC &DC);

	void paintEvent(wxPaintEvent &event);
	void render(wxDC &DC);

	DECLARE_EVENT_TABLE();

private:

	wxBitmap mainPanelBuffer;
	wxBitmap image;
	wxString text;
	wxString colorFigureText = "Star color";
	wxSize panelSize;
	wxColour figureColor = wxColour(*wxCYAN);
	wxPoint figureCoords = wxPoint(-80, -80);

	int characterSize = 40;
	int armHeight = 0;
	bool isBananaShown = false;
};

