#include <iostream>
#include <Windows.h>
using namespace std;

class Lyskryss {
private:
	int xGrense;
	int yGrense;

public:
	Lyskryss(int xGrense, int yGrense) {
		this->xGrense = xGrense;
		this->yGrense = yGrense;
	}

	void draw(HWND hWnd, HDC hdc) {

		HBRUSH veiBrush = CreateSolidBrush(RGB(128, 128, 128));
		HGDIOBJ hOrgBrush = SelectObject(hdc, veiBrush);

		RECT rect, nord, vest;
		GetClientRect(hWnd, &rect);

		vest = {0, rect.bottom / 2 - 50, rect.right, rect.bottom / 2 + 50};
		FillRect(hdc, &vest, veiBrush);
		
		nord = {rect.right / 2 - 50, 0, rect.right / 2 + 50, rect.bottom };
		FillRect(hdc, &nord, veiBrush);

		SelectObject(hdc, hOrgBrush);
		DeleteObject(veiBrush);
	}
};