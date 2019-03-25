#include "Window.h"

Window::Window() : wxFrame(NULL, wxID_ANY, "GFK Lab 03") {

	SetTitle(_("GFK Lab 03"));
	SetIcon(wxNullIcon);
	Center();

	this->SetSizeHints(800, 600);

	wxBoxSizer* drawSizer;
	drawSizer = new wxBoxSizer(wxHORIZONTAL);

	drawingPanel = new DrawPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	drawSizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);

	controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer* controlSizer;
	controlSizer = new wxBoxSizer(wxVERTICAL);

	saveButton = new wxButton(controlPanel, SAVE_BUTTON, wxT("Save to file"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(saveButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

	bananaCheck = new wxCheckBox(controlPanel, CHECKBOX, wxT("Show banana"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(bananaCheck, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

	armScrollBar = new wxScrollBar(controlPanel, SCROLLBAR, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
	armScrollBar->SetScrollbar(0, 1, 100, 1);
	controlSizer->Add(armScrollBar, 0, wxALL | wxEXPAND, 5);

	armProgress = new wxGauge(controlPanel, PROGRESSBAR, 99, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	armProgress->SetValue(0);
	controlSizer->Add(armProgress, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

	pickColorButton = new wxButton(controlPanel, COLOR_BOX, wxT("Star color"), wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(pickColorButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

	editableText = new wxTextCtrl(controlPanel, VERTICAL_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	controlSizer->Add(editableText, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

	wxImage NewImage = wxImage();
	NewImage.AddHandler(new wxPNGHandler);
	NewImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	drawingPanel->setImage(wxBitmap(NewImage));

	chooseFigureBox = new wxComboBox(controlPanel, FIGURE_BOX, wxT("Star"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	chooseFigureBox->Append(wxT("Star"));
	chooseFigureBox->Append(wxT("Moon"));
	chooseFigureBox->Append(wxT("Sun"));
	controlSizer->Add(chooseFigureBox, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

	controlPanel->SetSizer(controlSizer);
	controlPanel->Layout();
	controlSizer->Fit(controlPanel);
	drawSizer->Add(controlPanel, 0, wxEXPAND | wxALL, 5);

	this->SetSizer(drawSizer);
	this->Layout();

	this->Centre(wxBOTH);

	saveButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Window::saveToFile), NULL, this);
	bananaCheck->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Window::showBanana), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	pickColorButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Window::pickColor), NULL, this);
	editableText->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Window::updateText), NULL, this);
	chooseFigureBox->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Window::changeFigure), NULL, this);
}


Window::~Window() {

	saveButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Window::saveToFile), NULL, this);
	bananaCheck->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Window::showBanana), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	armScrollBar->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(Window::changeArmAndProgress), NULL, this);
	pickColorButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Window::pickColor), NULL, this);
	editableText->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Window::updateText), NULL, this);
	chooseFigureBox->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Window::changeFigure), NULL, this);
	saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::saveToFile ), NULL, this );
	bananaCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::showBanana ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	armScrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Window::changeArmAndProgress ), NULL, this );
	pickColorButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::pickColor ), NULL, this );
	editableText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Window::updateText ), NULL, this );
	chooseFigureBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Window::changeFigure ), NULL, this );

	delete saveButton;
	delete bananaCheck;
	delete armScrollBar;
	delete armProgress;
	delete pickColorButton;
	delete editableText;
	delete chooseFigureBox;
	delete drawingPanel;
	delete controlPanel;
}

void Window::saveToFile(wxCommandEvent& event) {

	wxFileDialog saveFileDialog(this, 
								_("Choose a file"), "", "", 
								"BMP files (*.bmp)|*.bmp|JPG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString FileDialogPath = saveFileDialog.GetPath();
    wxFileOutputStream output_stream(FileDialogPath);

    if (!output_stream.IsOk()) {

        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }

   	drawPanelImage = drawingPanel->getBuffer().ConvertToImage();
	drawPanelImage.AddHandler(new wxJPEGHandler);
	drawPanelImage.AddHandler(new wxPNGHandler);
	drawPanelImage.SaveFile(FileDialogPath);
}

void Window::showBanana(wxCommandEvent& event) {

	armScrollBar->Enable(bananaCheck->IsChecked());
	drawingPanel->changeBananaVisibility(bananaCheck->IsChecked());
	drawingPanel->Refresh();
}

void Window::changeArmAndProgress(wxScrollEvent& event) {

	armProgress->SetValue(armScrollBar->GetThumbPosition());
	drawingPanel->setArmHeight(armProgress->GetValue());
	drawingPanel->Refresh();
}

void Window::pickColor(wxCommandEvent& event) {

	wxColourDialog colorChoiceDialog(this, nullptr);

	if (colorChoiceDialog.ShowModal() == wxID_CANCEL)
		return;

	drawingPanel->setFigureColor(colorChoiceDialog.GetColourData().GetColour());
	drawingPanel->Refresh();
}

void Window::updateText(wxCommandEvent& event) {

	drawingPanel->setText(editableText->GetValue());
	drawingPanel->Refresh();
}

void Window::changeFigure(wxCommandEvent& event) {

	switch (chooseFigureBox->GetSelection()) {

		case 0:
		default: {
			drawingPanel->whichFigureToDraw = &DrawPanel::drawStar;
			drawingPanel->setFigureText("Star color");
			break; }
		case 1: {
			drawingPanel->whichFigureToDraw = &DrawPanel::drawMoon;
			drawingPanel->setFigureText("Moon color");
			break; }
		case 2: {
			drawingPanel->whichFigureToDraw = &DrawPanel::drawSun;
			drawingPanel->setFigureText("Sun color");
			break; }
	}

	pickColorButton->SetLabel(drawingPanel->getFigureText());
	drawingPanel->Refresh();
}