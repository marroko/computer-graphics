#pragma once
#include <wx/wxprec.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/colordlg.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/wfstream.h>
#include <wx/frame.h>
#include "DrawPanel.h"

class Window : public wxFrame {

public:

	Window();
	~Window();

	void saveToFile(wxCommandEvent &event);
	void showBanana(wxCommandEvent &event);
	void changeArmAndProgress(wxScrollEvent &event);
	void pickColor(wxCommandEvent &event);
	void updateText(wxCommandEvent &event);
	void changeFigure(wxCommandEvent &event);

private:

	enum {
		SAVE_BUTTON = 1001,
		CHECKBOX = 1002,
		SCROLLBAR = 1003,
		PROGRESSBAR = 1004,
		COLOR_BOX = 1005,
		VERTICAL_TEXT = 1006,
		FIGURE_BOX = 1007,
	};

	DrawPanel *drawingPanel; // calls Refresh() every time control is used
	wxPanel *controlPanel;
	wxButton *saveButton;
	wxCheckBox *bananaCheck;
	wxScrollBar *armScrollBar;
	wxGauge *armProgress;
	wxButton *pickColorButton;
	wxTextCtrl *editableText;
	wxComboBox *chooseFigureBox;
	wxImage drawPanelImage;
};