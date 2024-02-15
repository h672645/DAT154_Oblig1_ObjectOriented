#include <iostream>
#include <Windows.h>
using namespace std;

class TrafikklysVest {
private:
	int teller;

public:
	TrafikklysVest(int teller) {
		this->teller = teller;
	}

	void draw(HWND hWnd, HDC hdc, bool* vestlystRodt) {
		HBRUSH trafikkLysNord = CreateSolidBrush(RGB(0, 0, 0));
		HGDIOBJ hOrgBrush = SelectObject(hdc, trafikkLysNord);


		HBRUSH rod = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH gul = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH gronn = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH graa = CreateSolidBrush(RGB(128, 128, 128));

		RECT rect;
		GetClientRect(hWnd, &rect);
		Rectangle(hdc, rect.right / 2 - 50, rect.bottom / 2 + 50, rect.right / 2 - 200, rect.bottom / 2 + 100);

		int tilstand;
		if (teller < 9) {
			//GRØNN
			tilstand = 0;
			*vestlystRodt = false;
		}
		else if (teller >= 9 && teller < 12) {
			//GULT
			tilstand = 1;
			*vestlystRodt = true;
		}
		else if (teller >= 12 && teller < 21) {
			//RØDT
			tilstand = 2;
			*vestlystRodt = true;
		}
		else {
			//RØDT + GULT
			tilstand = 3;
			*vestlystRodt = true;
		}

		switch (tilstand) {
		case 2:

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 200, rect.bottom / 2 + 50, rect.right / 2 - 150, rect.bottom / 2 + 100);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 150, rect.bottom / 2 + 50, rect.right / 2 - 100, rect.bottom / 2 + 100);

			SelectObject(hdc, rod);
			Ellipse(hdc, rect.right / 2 - 100, rect.bottom / 2 + 50, rect.right / 2 - 50, rect.bottom / 2 + 100);
			break;

		case 3:
			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 200, rect.bottom / 2 + 50, rect.right / 2 - 150, rect.bottom / 2 + 100);

			SelectObject(hdc, gul);
			Ellipse(hdc, rect.right / 2 - 150, rect.bottom / 2 + 50, rect.right / 2 - 100, rect.bottom / 2 + 100);

			SelectObject(hdc, rod);
			Ellipse(hdc, rect.right / 2 - 100, rect.bottom / 2 + 50, rect.right / 2 - 50, rect.bottom / 2 + 100);
			break;

		case 0:
			SelectObject(hdc, gronn);
			Ellipse(hdc, rect.right / 2 - 200, rect.bottom / 2 + 50, rect.right / 2 - 150, rect.bottom / 2 + 100);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 150, rect.bottom / 2 + 50, rect.right / 2 - 100, rect.bottom / 2 + 100);

			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 100, rect.bottom / 2 + 50, rect.right / 2 - 50, rect.bottom / 2 + 100);
			break;

		case 1:
			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 200, rect.bottom / 2 + 50, rect.right / 2 - 150, rect.bottom / 2 + 100);
			
			SelectObject(hdc, gul);
			Ellipse(hdc, rect.right / 2 - 150, rect.bottom / 2 + 50, rect.right / 2 - 100, rect.bottom / 2 + 100);
			
			SelectObject(hdc, graa);
			Ellipse(hdc, rect.right / 2 - 100, rect.bottom / 2 + 50, rect.right / 2 - 50, rect.bottom / 2 + 100);
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