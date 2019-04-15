#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow* parent) : MyFrame1(parent)
{
	m_staticText1->SetLabel(_(L"Brightness"));
	m_b_threshold->SetLabel(_(L"Threshold 128"));
	this->SetBackgroundColour(wxColor(192, 192, 192));
	m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
	m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

inline void GUIMyFrame1::m_scrolledWindow_update(wxUpdateUIEvent& event)
{
	Repaint();
}

inline void GUIMyFrame1::m_b_grayscale_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy().ConvertToGreyscale();
}

inline void GUIMyFrame1::m_b_blur_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy().Blur(5);
}

inline void GUIMyFrame1::m_b_mirror_click(wxCommandEvent& event) {

	Img_Cpy = Img_Org.Copy().Mirror();
}

inline void GUIMyFrame1::m_b_replace_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

inline void GUIMyFrame1::m_b_rescale_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy().Rescale(320, 240);
}

inline void GUIMyFrame1::m_b_rotate_click(wxCommandEvent& event)
{
	double angle = 30.0;
	wxPoint rotationPoint = wxPoint(Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2);
	Img_Cpy = Img_Org.Copy().Rotate(angle * M_PI / 180, rotationPoint);
}

inline void GUIMyFrame1::m_b_rotate_hue_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5); // 180 degrees
}

inline void GUIMyFrame1::m_b_mask_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

inline void GUIMyFrame1::m_s_brightness_scroll(wxScrollEvent& event)
{
	Brightness(m_s_brightness->GetValue() - 100);
	Repaint();
}

inline void GUIMyFrame1::m_s_contrast_scroll(wxScrollEvent& event)
{
	Contrast(m_s_contrast->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_b_prewitt_click(wxCommandEvent& event)
{
	// mask
	// -1 0 1
	// -1 0 1
	// -1 0 1

	Img_Cpy = Img_Org.Copy();
	auto previous = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	const unsigned char *previousPixels = previous.GetData();

	auto width = Img_Cpy.GetWidth();
	auto widthTriple = width * 3;
	auto height = Img_Cpy.GetHeight();

	int tmp;

	for (int i = 1; i < height - 1; ++i) {

		for (int j = 1; j < width - 1; ++j) {

			int positive = (j + 1) * 3;
			int negative = (j - 1) * 3;

			for (int c = 0; c < 3; ++c) {

				tmp = 0;
				tmp += previousPixels[c + (i - 1) * widthTriple + positive];
				tmp += previousPixels[c + i * widthTriple + positive];
				tmp += previousPixels[c + (i + 1) * widthTriple + positive];

				tmp += -previousPixels[c + (i - 1) * widthTriple + negative];
				tmp += -previousPixels[c + i * widthTriple + negative];
				tmp += -previousPixels[c + (i + 1) * widthTriple + negative];

				pixels[c + i * widthTriple + j * 3] = abs(tmp) / 3.0;
			}
		}
	}
}

void GUIMyFrame1::m_b_threshold_click(wxCommandEvent& event)
{
	constexpr int threshold = 128;

	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;

	int i = 0;

	while (i < size) {

		if (pixels[i] < threshold) // if less, set color to black
			pixels[i] = 0;
		else
			pixels[i] = 255;
		++i;
	}
}


void GUIMyFrame1::Contrast(int value) // value from -100 to 100
{
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	const double contrast = (value + 100.0) / 100.0;

	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;
	int i = 0, tmp;

	while (i < size) {

		tmp = (pixels[i] - 255.0 / 2) * contrast + 255.0 / 2;

		if (tmp > 255)
			tmp = 255;
		else if (tmp < 0)
			tmp = 0;

		pixels[i++] = tmp;
	}
}

void GUIMyFrame1::Repaint()
{
	wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
	wxBufferedDC dcBuffer(&dc);
	dcBuffer.Clear();				   // Czyscimy aby nie doprowadzic do zmniejszenia FPS
	m_scrolledWindow->DoPrepareDC(dcBuffer); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	dcBuffer.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char * pixels = Img_Cpy.GetData();

	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;
	int i = 0;

	while(i < size) {

		int tmp = pixels[i] + value;

		if (tmp > 255)
			tmp = 255;
		else if (tmp < 0)
			tmp = 0;

		pixels[i++] = tmp;
	}
}