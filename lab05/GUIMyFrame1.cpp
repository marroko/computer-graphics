#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>

struct Point {

	float x, y, z;
	Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {

	int R, G, B;
	Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {

	Point begin, end;
	Color color;
	Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;
constexpr double norm = M_PI / 180;

GUIMyFrame1::GUIMyFrame1(wxWindow* parent) : MyFrame1(parent)
{
	m_button_load_geometry->SetLabel(_("Load geometry"));
	m_staticText25->SetLabel(_("Rotation X:"));
	m_staticText27->SetLabel(_("Rotation Y:"));
	m_staticText29->SetLabel(_("Rotation Z:"));

	WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
	WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
	WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

	WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
	WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
	WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

	WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
	WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
	WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint(wxUpdateUIEvent& event)
{
	Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click(wxCommandEvent& event)
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		double x1, y1, z1, x2, y2, z2;
		int r, g, b;

		std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
		if (in.is_open())
		{
			data.clear();
			while (!in.eof())
			{
				in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
				data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
			}
			in.close();
		}
	}
}

void GUIMyFrame1::Scrolls_Updated(wxScrollEvent& event)
{
	WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
	WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
	WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

	WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
	WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
	WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

	WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
	WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
	WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));

	Repaint();
}

///////

Matrix4 GUIMyFrame1::makeCenter() const {

	Matrix4 tmp;

	tmp.data[0][0] = tmp.data[2][2] = tmp.data[1][1] = 1;
	tmp.data[0][3] = tmp.data[1][3] = 0.5;

	return tmp;
}


Matrix4 GUIMyFrame1::makeRotationX(const double xRotation) const {

	Matrix4 tmp;
	const double angle = xRotation * norm;

	tmp.data[0][0] = 1;
	tmp.data[1][1] = tmp.data[2][2] = cos(angle);
	tmp.data[2][1] = sin(angle);
	tmp.data[1][2] = -sin(angle);

	return tmp;
}

Matrix4 GUIMyFrame1::makeRotationY(const double yRotation) const {

	Matrix4 tmp;
	const double angle = yRotation * norm;

	tmp.data[1][1] = 1;
	tmp.data[0][0] = tmp.data[2][2] = cos(angle);
	tmp.data[0][2] = sin(angle);
	tmp.data[2][0] = -sin(angle);

	return tmp;
}

Matrix4 GUIMyFrame1::makeRotationZ(const double zRotation) const {

	Matrix4 tmp;
	const double angle = zRotation * norm;

	tmp.data[0][0] = tmp.data[1][1] = cos(angle);
	tmp.data[2][2] = 1;
	tmp.data[1][0] = sin(angle);
	tmp.data[0][1] = -sin(angle);

	return tmp;
}

Matrix4 GUIMyFrame1::makeScale(const double x, const double y, const double zScale) const {

	Matrix4 tmp;

	tmp.data[0][0] = x;
	tmp.data[1][1] = y;
	tmp.data[2][2] = zScale;

	return tmp;
}

Matrix4 GUIMyFrame1::makeTranslation(const double x, const double y, const double z) const {

	Matrix4 tmp;

	tmp.data[0][0] = tmp.data[1][1] = tmp.data[2][2] = 1.0;
	tmp.data[0][3] = x;
	tmp.data[1][3] = y;
	tmp.data[2][3] = z;

	return tmp;
}

void GUIMyFrame1::Repaint() {

	wxClientDC dc(WxPanel);
	wxBufferedDC dcBuff(&dc);
	int width, height;

	WxPanel->GetSize(&width, &height);
	dcBuff.SetBackground(wxBrush(*wxWHITE));
	dcBuff.Clear();

	const Matrix4 center = makeCenter();

	const Matrix4 xRot = makeRotationX(WxSB_RotateX->GetValue());
	const Matrix4 yRot = makeRotationY(WxSB_RotateY->GetValue());
	const Matrix4 zRot = makeRotationZ(WxSB_RotateZ->GetValue());
	const Matrix4 finalRotation = xRot * yRot * zRot;

	auto xScale = WxSB_ScaleX->GetValue() / 100.0;
	auto yScale = WxSB_ScaleY->GetValue() / 100.0;
	auto zScale = WxSB_ScaleZ->GetValue() / 100.0;
	const Matrix4 finalScale = makeScale(xScale, yScale, zScale);

	auto xTransl = (WxSB_TranslationX->GetValue() - 100.0) / 50.0;
	auto yTransl = (WxSB_TranslationY->GetValue() - 100.0) / 50.0;
	auto zTransl = (WxSB_TranslationZ->GetValue() - 100.0) / 50.0 + 2;
	const Matrix4 finalTranslation = makeTranslation(xTransl, yTransl, zTransl);

	const Matrix4 transformation = finalTranslation * finalRotation * finalScale;

	for (const auto & segment : data) {

		Vector4 start, end;

		start.Set(segment.begin.x, segment.begin.y, segment.begin.z);
		start = transformation * start;
		start.Set(start.GetX() / start.GetZ(), start.GetY() / start.GetZ(), start.GetZ());
		start = center * start;

		end.Set(segment.end.x, segment.end.y, segment.end.z);
		end = transformation * end;
		end.Set(end.GetX() / end.GetZ(), end.GetY() / end.GetZ(), end.GetZ());
		end = center * end;

		dcBuff.SetPen(wxPen(RGB(segment.color.R, segment.color.G, segment.color.B)));
		dcBuff.DrawLine(start.GetX() * width, start.GetY() * height, end.GetX() * width, end.GetY() * height);
	}
}