#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range()
{
	double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
	double x,y,step;

	xmin = cfg->Get_x_start();
	xmax = cfg->Get_x_stop();

	step = (cfg->Get_x_stop() - cfg->Get_x_start()) / static_cast<double>(x_step);
	x = cfg->Get_x_start();

	for (int i=0;i<=x_step;i++)
	{
		y = GetFunctionValue(x);
		if (y>ymax) 
			ymax = y;
		if (y<ymin) 
			ymin = y;
		x += step;
	}

	y_min = ymin;
	y_max = ymax;
	x_min = xmin;
	x_max = xmax;
}

double ChartClass::GetFunctionValue(double x)
{
	if (cfg->Get_F_type()==1) 
		return x*x;
	if (cfg->Get_F_type()==2) 
		return 0.5*exp(4*x-3*x*x);

	return x+sin(x*4.0);
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

void ChartClass::Draw(wxDC *dc, int w, int h)
{
	dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	dc->Clear();
	dc->SetPen(wxPen(RGB(255, 0, 0)));
	dc->DrawRectangle(10, 10, w - 20, h - 20);

	Matrix transformation;
	if (cfg->RotateScreenCenter()) // if - obroc wokol srodka ekranu, else - obroc wokol punktu 0 na osi
		transformation = prepareRotation(w, h) * prepareTranslation() * prepareScale(w, h);
	else
		transformation = prepareTranslation() * prepareRotation(w, h) * prepareScale(w, h); // trywialne przypisania macierzy

	dc->SetFont(wxFont(wxFontInfo(10).Bold()));
	dc->SetPen(wxPen(RGB(0, 0, 255)));
	drawAxes(dc, transformation, w, h);

	const double dx = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
	const double stop = cfg->Get_x_stop();
	double x = cfg->Get_x_start();

	dc->SetPen(wxPen(*wxBLACK));

	while (x < stop) {

		line2d(transformation, 
			   x, GetFunctionValue(x), 
			   x + dx, GetFunctionValue(x + dx), 
			   w, h, dc);
		x += dx;
	}

	// zapobieganie rysowaniu poza swiatem
	dc->SetPen(wxPen(*wxWHITE));
	dc->DrawRectangle(0, 0, w, 10);
	dc->DrawRectangle(0, 10, 10, h - 10);
	dc->DrawRectangle(10, h - 10, w - 10, 10);
	dc->DrawRectangle(w - 10, 10, 10, h - 20);

}
Matrix ChartClass::prepareRotation(int w, int h) {

	Matrix rotation;
	const double angle = cfg->Get_Alpha();
	const double cosinus = cos(angle * M_PI / 180.0);
	const double sinus = sin(angle * M_PI / 180.0);

	rotation.data[0][0] = rotation.data[1][1] = cosinus;
	rotation.data[0][1] = sinus;
	rotation.data[1][0] = -sinus;

	if (cfg->RotateScreenCenter()) { // if - obroc wokol srodka ekranu, else - obroc wokol punktu 0 na osi

		rotation.data[0][2] = (w / 2.0) * (1 - cosinus) + (h / 2.0) * (-sinus);
		rotation.data[1][2] = (w / 2.0) * sinus + (h / 2.0) * (1 - cosinus);
	}
	else {

		Matrix m = prepareScale(w, h);
		rotation.data[0][2] = m.data[0][2] * (1 - cosinus) + m.data[1][2] * (-sinus);
		rotation.data[1][2] = m.data[0][2] * sinus + m.data[1][2] * (1 - cosinus);
	}
	return rotation;
}

Matrix ChartClass::prepareScale(int w, int h) {

	Matrix scale;
	scale.data[0][0] = (w - 20.0) / (cfg->Get_x1() - cfg->Get_x0());
	scale.data[1][1] = (h - 20.0) / (cfg->Get_y1() - cfg->Get_y0());
	scale.data[0][2] = 10.0 - scale.data[0][0] * cfg->Get_x0();
	scale.data[1][2] = 10.0 - scale.data[1][1] * cfg->Get_y0();
	return scale;
}

Matrix ChartClass::prepareTranslation() {

	Matrix translation;
	translation.data[0][0] = translation.data[1][1] = translation.data[2][2] = 1;
	translation.data[0][2] = cfg->Get_dX();
	translation.data[1][2] = cfg->Get_dY();
	return translation;
}

void ChartClass::rotatedText(wxDC *dc, Matrix transformation, wxString text, double x, double y, int w, int h) {

	Vector rotated;
	rotated.Set(x, y);
	rotated = transformation * rotated;
	dc->DrawRotatedText(text, rotated.GetX(), h - rotated.GetY(), -cfg->Get_Alpha());
}

void ChartClass::line2d(Matrix transformation, double x1, double y1, double x2, double y2, int w, int h, wxDC *dc) {

	Vector start;
	start.Set(x1, y1);
	start = transformation * start;

	Vector end;
	end.Set(x2, y2);
	end = transformation * end;

	dc->DrawLine(start.GetX(), h - start.GetY(), end.GetX(), h - end.GetY());
}

void ChartClass::drawAxes(wxDC *dc, Matrix transformation, int w, int h) {

	constexpr double step = 0.05;

	line2d(transformation, cfg->Get_x_start(), 0		  ,cfg->Get_x_stop(), 0, w, h, dc);
	line2d(transformation, 0				 , Get_Y_min(), 0				, Get_Y_max(), w, h, dc);

	const double dx = 1 + static_cast<int>((cfg->Get_x1() - cfg->Get_x0()) / 10);
	const double dy = 1 + static_cast<int>((cfg->Get_y1() - cfg->Get_y0()) / 10);

	// start X
	double x = x_min;
	while(x <= x_max) {

		line2d(transformation, x, -step, x, step, w, h, dc);
		rotatedText(dc, transformation, wxString::Format(wxT("%.2g"), x), x - 0.1, -0.1, w, h);
		x += dx / 2;
	}
	line2d(transformation, x_max, 0, x_max - step, step, w, h, dc);
	line2d(transformation, x_max, 0, x_max - step, -step, w, h, dc);

	// start Y
	double y = y_min;
	while(y <= y_max) {

		line2d(transformation, -step, y, step, y, w, h, dc);
		rotatedText(dc, transformation, wxString::Format(wxT("%.2g"), y), 0.1, y, w, h);
		y += dy / 2;
	}
	line2d(transformation, 0, y_max, step, y_max - step, w, h, dc);
	line2d(transformation, 0, y_max, -step, y_max - step, w, h, dc);
}