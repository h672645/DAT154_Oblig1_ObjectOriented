#include <iostream>
#include <Windows.h>
using namespace std;

struct Farge {
	int red;
	int green;
	int blue;
};

class Bil {
public:
	int xPos;
	int yPos;
	Farge farge;

	Bil(int xPos, int yPos) {
		this->xPos = xPos;
		this->yPos = yPos;
		farge.red = rand() % 256;
		farge.green = rand() % 256;
		farge.blue = rand() % 256;
	};

	void drawBilVest(HWND hwnd, HDC hdc, POINT retning, bool trafikklys) {
		HBRUSH biltegnerbrush = CreateSolidBrush(RGB(farge.red, farge.green, farge.blue));
		HGDIOBJ hOrgBrush = SelectObject(hdc, biltegnerbrush);

		RECT rect = { xPos, yPos, xPos+20, yPos + 10 };
		FillRect(hdc, &rect, biltegnerbrush);

		RECT client;
		GetClientRect(hwnd, &client);
		
		if (xPos > (client.right / 2 - 90) && xPos < (client.right / 2 - 70) && trafikklys == true) {
			xPos = xPos;
		}
		else {
			xPos += retning.x;
		}

		SelectObject(hdc, hOrgBrush);
		DeleteObject(biltegnerbrush);
	};

	void drawBilNord(HWND hwnd, HDC hdc, POINT retning, bool trafikklys) {
		HBRUSH biltegnerbrush = CreateSolidBrush(RGB(farge.red, farge.green, farge.blue));
		HGDIOBJ hOrgBrush = SelectObject(hdc, biltegnerbrush);

		RECT rect = { xPos, yPos, xPos + 10, yPos +20};
		FillRect(hdc, &rect, biltegnerbrush);

		RECT client;
		GetClientRect(hwnd, &client);

		if (yPos > (client.bottom / 2 + 50) && yPos < (client.bottom / 2 + 70) && trafikklys == true) {
			yPos = yPos;
		}
		else {
			yPos -= retning.y;
		}
		
		SelectObject(hdc, hOrgBrush);
		DeleteObject(biltegnerbrush);
	}
};