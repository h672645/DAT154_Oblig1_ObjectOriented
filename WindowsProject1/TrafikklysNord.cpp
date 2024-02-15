#include <iostream>
#include <Windows.h>
using namespace std;

class TrafikklysNord {
private:
	int teller;

public:
	TrafikklysNord(int teller) {
		this->teller = teller;
	}
	
	void draw(HWND hWnd, HDC hdc, bool* nordlystRodt) {
		HBRUSH trafikkLysNord = CreateSolidBrush(RGB(0, 0, 0));
		HGDIOBJ hOrgBrush = SelectObject(hdc, trafikkLysNord);
		

		HBRUSH rod = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH gul = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH gronn = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH graa = CreateSolidBrush(RGB(128, 128, 128));

		RECT rect;
		GetClientRect(hWnd, &rect);
		Rectangle(hdc, rect.right / 2 + 50, rect.bottom/2 - 200, rect.right / 2 + 100, rect.bottom / 2 - 50);

		int tilstand;

		
		if (teller < 9) {
			//Rødt
			tilstand = 0;
			*nordlystRodt = true;
		}
		else if (teller >= 9 && teller < 12) {
			//RØDT+GULT
			tilstand = 1;
			*nordlystRodt = true;
		}
		else if (teller >= 12 && teller < 21) {
			//GRØNN
			tilstand = 2;
			*nordlystRodt = false;
		}
		else {
			//GULT
			tilstand = 3;
			*nordlystRodt = true;
		}

		switch (tilstand) {
		case 0:
			SelectObject(hdc, rod);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 200, rect.right / 2 + 100, rect.bottom / 2 - 150);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 150, rect.right / 2 + 100, rect.bottom / 2 - 100);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 100, rect.right / 2 + 100, rect.bottom / 2 - 50);
			break;

		case 1:
			SelectObject(hdc, rod);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 200, rect.right / 2 + 100, rect.bottom / 2 - 150);

			SelectObject(hdc, gul);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 150, rect.right / 2 + 100, rect.bottom / 2 - 100);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 100, rect.right / 2 + 100, rect.bottom / 2 - 50);
			break;

		case 2:
			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 200, rect.right / 2 + 100, rect.bottom / 2 - 150);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 150, rect.right / 2 + 100, rect.bottom / 2 - 100);

			SelectObject(hdc, gronn);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 100, rect.right / 2 + 100, rect.bottom / 2 - 50);
			break;

		case 3:
			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 200, rect.right / 2 + 100, rect.bottom / 2 - 150);

			SelectObject(hdc, gul);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 150, rect.right / 2 + 100, rect.bottom / 2 - 100);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 100, rect.right / 2 + 100, rect.bottom / 2 - 50);
			break;
		}

		SelectObject(hdc, hOrgBrush);
		DeleteObject(trafikkLysNord);
		DeleteObject(rod);
		DeleteObject(gronn);
		DeleteObject(graa);
		DeleteObject(gul);
	}
};