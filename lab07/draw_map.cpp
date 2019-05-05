#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

constexpr int bitmapSize = 500;
constexpr int maxRGB = 255;

inline float shepard(int N, float d[100][3], const wxRealPoint &point) {

	float numerator = 0., denominator = 0., wk;

	for (int i = 0; i < N; ++i) {

		wk = 1. / fabs(pow(point.x - d[i][0], 2) + pow(point.y - d[i][1], 2));
		numerator += wk * d[i][2];
		denominator += wk;
	}

	return numerator / denominator;
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
	wxMemoryDC memDC;
	memDC.SelectObject(MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	if (!N) return;

	float shepardBitmap[bitmapSize][bitmapSize];
	for (int x = 0; x < bitmapSize; x++) {

		for (int y = 0; y < bitmapSize; y++) {

			wxRealPoint point((y / 100.0) - 2.5, -((x / 100.0) - 2.5));
			shepardBitmap[y][x] = shepard(N, d, point);
		}
	}

	float min, max;
	min = max = d[0][2];
	for (int i = 1; i < N; i++) {

		if (d[i][2] < min) 
			min = d[i][2];
		if (d[i][2] > max) 
			max = d[i][2];
	}

	// mapping type
	for (int x = 0; x < bitmapSize; ++x)

		for (int y = 0; y < bitmapSize; ++y) {

			unsigned char color = (shepardBitmap[y][x] - min) * maxRGB / (max - min);
			switch (MappingType) {

			case 1: { // od niebieskiego do czerwonego 
				memDC.SetPen(wxPen(wxColour(maxRGB - color, 0, color)));
				memDC.DrawPoint(y, x);
				break;
			}

			case 2: { // od niebieskiego przez zielony do czerwonego

				int r = maxRGB - 2 * color;
				int g = 2 * color;
				int b = 2 * (color - 128);

				if (r < 0) 
					r = 0;
				if (g > maxRGB)
					g = 2 * (maxRGB - color);
				if (b < 0) 
					b = 0;

				memDC.SetPen(wxPen(wxColour(r, g, b)));
				memDC.DrawPoint(y, x);
				break;
			}

			case 3: { // w odcieniach szarosci

				memDC.SetPen(wxPen(wxColour(color, color, color)));
				memDC.DrawPoint(y, x);
				break;
			}
				default: break;
			}
		}

	memDC.SetPen(*wxBLACK_PEN);
	memDC.SetBrush(*wxTRANSPARENT_BRUSH);

	if (ShowPoints) {

		for (int i = 0; i < N; ++i) {

			wxPoint point(100 * (d[i][0] + 2.5), 100 * (2.5 - d[i][1]));
			memDC.DrawLine(point.x, point.y + 5, point.x, point.y - 5); // krzyzyki
			memDC.DrawLine(point.x - 5, point.y, point.x + 5, point.y);
		}
	}

	if (Contour) {

		for (int levels = 0; levels < NoLevels; ++levels) {

			float thresholdPoint = min + (levels + 1) * (max - min) / (NoLevels + 1.);

			for (int x = 0; x < bitmapSize; ++x)
				for (int y = 0; y < bitmapSize; ++y)

					if (shepardBitmap[y][x] > thresholdPoint) {

						int thickness = 1;
						for (int i = -thickness; i <= thickness; ++i)
							for (int j = -thickness; j <= thickness; ++j)
								if (i && j && 
									(i + y >= 0) && 
									(j + x >= 0) && 
									(i + y < bitmapSize) && 
									(j + x < bitmapSize) && 
									(shepardBitmap[i + y][j + x] < thresholdPoint))
										memDC.DrawPoint(y, x);
					}
		}
	}
}