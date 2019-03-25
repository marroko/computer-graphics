#include "Window.h"

class Application : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
	Window *frame = new Window();
	frame->Show(true);
	return true;
}