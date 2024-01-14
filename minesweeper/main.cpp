#include "main.h"
#include "Console.h"
#include <Windows.h>

Table Bang;
Cell** O;
COORD pointerNow;//vi tri con tro tren man console , mac dinh la (0;0)
bool checkUserClick = false;
int toadox;
int toadoy;
bool trangthaiPlay = false;
int page, Choose, index;

void taoMang2Chieu() {
	O = new Cell * [Bang.Dong];
	for (int i = 0; i < Bang.Dong; i++) {
		O[i] = new Cell[Bang.Cot];
	}
}
void xoaMang2Chieu() {
	for (int i = 0; i < Bang.Dong; i++) {
		delete[]O[i];
	}
	delete[]O;
}
void play(int Dong, int Cot, int Bom) {
	Bang.Dong = Dong;
	Bang.Cot = Cot;
	Bang.Bom = Bom;
	Bang.oDaMo = 0;
	Bang.Co = 0;

	taoMang2Chieu();
	imBom();
	chinhToaDoTable();
	trangthaiPlay = true;
	sound(soundStart);
	veTrangThai(1);
	trangthaiBom();
	veBang();

}
int toaDoX(int x) {
	return x * 2 + toadox;
}
int toaDoY(int y) {
	return y + toadoy;
}
void veBang() {
	for (int i = 0; i < Bang.Dong; i++) {
		for (int j = 0; j < Bang.Cot; j++) {
			if (O[i][j].CamCo) { //ve co
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {//ve o mau chan
					veO(j, i, 10);
				}
				else {
					veO(j, i, 16);
				}

			}
			else if (O[i][j].BomLanCan) {//ve so bom
				veO(j, i, O[i][j].BomLanCan);
			}
			else if (O[i][j].DaMo) {//ve o trong
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {//ve o mau chan
					veO(j, i, 0);
				}
				else {
					veO(j, i, 17);
				}
			}
			else if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {//ve o mau chan
				veO(j, i, 13);
			}
			else {
				veO(j, i, 14);//ve o mau le
			}
			if (checkUserClick) {
				veO(pointerNow.X, pointerNow.Y, 15);
			}
		}
	}
}
void veO(int x, int y, int soMau) {
	switch (soMau) {
	case 0: //ko co bom chan,mau vang light
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 14, "  ");
		break;
	case 1: //text 1, mau xanh duong
		setColorBGTextXY(toaDoX(x), toaDoY(y), 1, 14, " 1");
		break;
	case 2: //text 2, mau vang
		setColorBGTextXY(toaDoX(x), toaDoY(y), 2, 14, " 2");
		break;
	case 3: //text 3, mau do
		setColorBGTextXY(toaDoX(x), toaDoY(y), 4, 14, " 3");
		break;
	case 4: //text 4, mau tim
		setColorBGTextXY(toaDoX(x), toaDoY(y), 13, 14, " 4");
		break;
	case 5: //text 5, mau den
		setColorBGTextXY(toaDoX(x), toaDoY(y), 16, 14, " 5");
		break;
	case 6: //text 6, mau do light
		setColorBGTextXY(toaDoX(x), toaDoY(y), 12, 14, " 6");
		break;
	case 7: //text 7, mau xanh light
		setColorBGTextXY(toaDoX(x), toaDoY(y), 11, 14, " 7");
		break;
	case 8: //text 8, mau xam
		setColorBGTextXY(toaDoX(x), toaDoY(y), 8, 14, " 8");
		break;
	case 9://bom
		setColorBGTextXY(toaDoX(x), toaDoY(y), 16, 12, " *");
		break;
	case 10://Co da cam chan
		setColorBGTextXY(toaDoX(x), toaDoY(y), 4, 2, " !");
		break;
	case 11://Cam co sai
		setColorBGTextXY(toaDoX(x), toaDoY(y), 4, 8, " X");
		break;
	case 12://Cam co dung
		setColorBGTextXY(toaDoX(x), toaDoY(y), 4, 14, " *");
		break;
	case 13://o rong chan
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 2, "  ");
		break;
	case 14://o rong le
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 10, "  ");
		break;
	case 15://con tro
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 3, " ");
		break;
	case 16://Co da cam le
		setColorBGTextXY(toaDoX(x), toaDoY(y), 4, 10, " !");
		break;
	case 17: //ko co bom le ,mau vang light
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 6, "  ");
		break;
	}
}
void imBom() {
	int soBom = Bang.Bom;
	int bi, bj;
	srand(time(NULL));
	while (soBom) {
		bi = rand() % Bang.Dong;
		bj = rand() % Bang.Cot;
		//ko co bom thi tiep tuc vong lap
		if (O[bi][bj].CoBom) {
			continue;
		}
		//co bom thi tru so bom xuong
		O[bi][bj].CoBom = true;
		soBom--;
	}
}
int demBom(int x, int y) {
	int dem = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if ((i < 0 || i >= Bang.Dong) || (j < 0 || j >= Bang.Cot) || (i == x && j == y)) {//bo nhung ô cận rìa
				continue;
			}
			if (O[i][j].CoBom) {
				dem++;
			}

		}
	}
	return dem;
}
void moO(int x, int y) {
	if (O[x][y].DaMo==false && O[x][y].CamCo==false) {
		O[x][y].DaMo = true;
		if (O[x][y].CoBom) {
			lose();
		}
		else {
			Bang.oDaMo++;
			int soBom = demBom(x, y);
			if (soBom) {
				O[x][y].BomLanCan = soBom;
			}
			else {
				for (int i = x - 1; i <= x + 1; i++) {
					for (int j = y - 1; j <= y + 1; j++) {
						if ((i < 0 || i >= Bang.Dong) || (j < 0 || j >= Bang.Cot) || (i == x && j == y)) {
							continue;
						}
						moO(i, j);
					}
				}
			}
		}
	}
}
bool xetThangThua() {
	if (Bang.oDaMo + Bang.Bom == Bang.Dong * Bang.Cot) {
		return true;
	}
	else {
		return false;
	}

}
void bamF(int x, int y) {
	if (Bang.Bom - Bang.Co > 0) {
		if (O[x][y].DaMo==false) {
			sound(soundF);
			if (O[x][y].CamCo) {
				O[x][y].CamCo = false;
				Bang.Co--;
			}
			else {
				O[x][y].CamCo = true;
				Bang.Co++;
			}
			veBang();
			deleteRow(toadoy - 1, 1);
			trangthaiBom();

		}
	}
	else {
		if (O[x][y].DaMo==false) {
			sound(soundF);
			if (O[x][y].CamCo) {
				O[x][y].CamCo = false;
				Bang.Co--;
			}
			veBang();
			deleteRow(toadoy - 1, 1);
			trangthaiBom();

		}

	}

}
void bamD(int x, int y) {
	if (O[x][y].DaMo==false && O[x][y].CamCo==false) {
		moO(x, y);
		if (trangthaiPlay) {
			veBang();
			if (xetThangThua()) {
				win();
			}
			else {
				sound(soundD);
			}
		}
	}

}
void lose() {
	for (int i = 0; i < Bang.Dong; i++) {
		for (int j = 0; j < Bang.Cot; j++) {
			if (O[i][j].CamCo) {//có cắm cờ
				if (O[i][j].CoBom) {
					veO(j, i, 12);
				}
				else {
					veO(j, i, 11);
				}
			}
			else {//ko cắm cờ
				if (O[i][j].CoBom) {
					veO(j, i, 9);
				}
			}
		}
	}
	trangthaiPlay = false;
	sound(soundLose);
	xoaMang2Chieu();
	page = 4;
	deleteRow(0, 3);
	
	veTrangThai(3);
	drawMenuSelect(0);
	

}
void win() {
	trangthaiPlay = false;
	sound(soundWin);
	xoaMang2Chieu();
	page = 4;
	deleteRow(0, 3);
	veTrangThai(2);
	drawMenuSelect(0);

}
//1.MENU
//2.LEVEL
//3.PLAY
//4.REPLAY/BACK
//5.BACK
void nhapPhim() {
	while (true) {
		/*Giá trị 0x8000 đại diện cho trạng thái bật của một phím.
		& 0x8000 được sử dụng để kiểm tra xem bit thứ 15 có được thiết lập (bằng 1) hay không.
		Nếu kết quả của phép AND là khác 0, điều này có nghĩa là bit thứ 15 đã được thiết lập, tức là phím đang được nhấn.*/


		// Kiểm tra trạng thái các phím mũi tên
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			switch (page) {
			case 1://menu

				if (index == 4) {
					if (Choose == 0) {
						Choose = index - 1;
					}
					else {
						Choose--;
					}

				}
				drawMenu(Choose);
				break;
			case 2://level

				if (index == 4) {
					if (Choose == 0) {
						Choose = index - 1;
					}
					else {
						Choose--;
					}

				}
				drawLevel(Choose);
				break;
			case 3://play
				if (trangthaiPlay) {
					checkUserClick = true;
					if (pointerNow.Y == 0) {
						pointerNow.Y = Bang.Dong - 1;
					}
					else {
						pointerNow.Y = pointerNow.Y - 1;
					}
					veBang();
				}
				break;
			case 4:// replay/back
				if (index == 2) {
					if (Choose == 0) {
						Choose = index - 1;
					}
					else {
						Choose--;
					}

				}
				drawMenuSelect(Choose);
				break;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			switch (page) {
			case 1://menu
				if (index == 4) {
					if (Choose == index - 1) {
						Choose = 0;
					}
					else {
						Choose++;
					}
				}
				drawMenu(Choose);
				break;
			case 2://level

				if (index == 4) {
					if (Choose == index - 1) {
						Choose = 0;
					}
					else {
						Choose++;
					}
				}
				drawLevel(Choose);
				break;
			case 3://play
				if (trangthaiPlay) {
					checkUserClick = true;
					if (pointerNow.Y == Bang.Dong - 1) {
						pointerNow.Y = 0;
					}
					else {
						pointerNow.Y = pointerNow.Y + 1;
					}
					veBang();
				}
				break;
			case 4:// replay/back
				if (index == 2) {
					if (Choose == index - 1) {
						Choose = 0;
					}
					else {
						Choose++;
					}
				}
				drawMenuSelect(Choose);
				break;
			}

		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (trangthaiPlay) {
				checkUserClick = true;
				if (pointerNow.X == 0) {
					pointerNow.X = Bang.Cot - 1;
				}
				else {
					pointerNow.X = pointerNow.X - 1;
				}
				veBang();
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (trangthaiPlay) {
				checkUserClick = true;
				if (pointerNow.X == Bang.Cot - 1) {
					pointerNow.X = 0;
				}
				else {
					pointerNow.X = pointerNow.X + 1;
				}
				veBang();
			}
		}

		else if (GetAsyncKeyState(0x46) & 0x8000) {
			bamF(pointerNow.Y, pointerNow.X);
		}
		else if (GetAsyncKeyState(0x44) & 0x8000) {
			bamD(pointerNow.Y, pointerNow.X);
		}

		else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			sound(soundEnter);
			switch (page) {
			case 1:
				if (Choose == 0) {//play
					page = 2;
					deleteRow(0, 35);
					veTieuDe();
					thietkegiaodien();
					drawLevel(0);

				}
				else if (Choose == 1) {//rules
					deleteRow(0, 35);
					//text rules
					for (int i = 0; i <= 82; i++) {
						setColor(3);
						Sleep(10);
						gotoXY(i, 3);
						std::cout << char(196);
						gotoXY(i, 26);
						std::cout << char(196);
					}
					for (int i = 3; i <= 26; i++) {
						setColor(3);
						Sleep(20);
						gotoXY(0, i);
						std::cout << char(179);
						gotoXY(82, i);
						std::cout << char(179);
					}
					gotoXY(0, 3);
					std::cout << char(218);
					gotoXY(82, 3);
					std::cout << char(191);
					gotoXY(0, 26);
					std::cout << char(192);
					gotoXY(82, 26);
					std::cout << char(217);
					//text keys
					for (int i = 89; i <= 119; i++) {

						setColor(3);
						Sleep(10);
						gotoXY(i, 3);
						std::cout << char(196);
						gotoXY(i, 9);
						std::cout << char(196);
					}
					for (int i = 3; i <= 9; i++) {
						setColor(3);
						Sleep(10);
						gotoXY(89, i);
						std::cout << char(179);
						gotoXY(119, i);
						std::cout << char(179);
					}
					gotoXY(89, 3);
					std::cout << char(218);
					gotoXY(119, 3);
					std::cout << char(191);
					gotoXY(89, 9);
					std::cout << char(192);
					gotoXY(119, 9);
					std::cout << char(217);

					//text signs
					for (int i = 89; i <= 119; i++) {

						setColor(3);
						Sleep(10);
						gotoXY(i, 11);
						std::cout << char(196);
						gotoXY(i, 26);
						std::cout << char(196);
					}
					for (int i = 11; i <= 26; i++) {
						setColor(3);
						Sleep(10);
						gotoXY(89, i);
						std::cout << char(179);
						gotoXY(119, i);
						std::cout << char(179);
					}
					gotoXY(89, 11);
					std::cout << char(218);
					gotoXY(119, 11);
					std::cout << char(191);
					gotoXY(89, 26);
					std::cout << char(192);
					gotoXY(119, 26);
					std::cout << char(217);


					setColorBGTextXY(1, 4, 14, 0, "1.Muc tieu cua tro choi:");
					setColorBGTextXY(2, 5, 15, 0, "- Mo tat ca cac o trong tren bang ma khong cham vao bat ki min nao.");
					setColorBGTextXY(1, 7, 14, 0, "2.Bang tro choi:");
					setColorBGTextXY(2, 8, 15, 0, "- Bang tro choi la mot luoi o vuong, moi o co the chua mot min hoac khong.");
					setColorBGTextXY(2, 9, 15, 0, "- So luong min va kich thuoc cua bang duoc xac dinh tu cau hinh tro choi.");
					setColorBGTextXY(1, 11, 14, 0, "3.Mo o:");
					setColorBGTextXY(2, 12, 15, 0, "- Nguoi choi bat dau bang viec mo mot o bat ki tren bang.");
					setColorBGTextXY(2, 13, 15, 0, "- Neu o mo la mot min, tro choi ket thuc voi that bai.");
					setColorBGTextXY(1, 15, 14, 0, "4.So tren cac o:");
					setColorBGTextXY(2, 16, 15, 0, "- O khong co min se hien thi mot so (1-8) the hien so luong min xung quanh o do.");
					setColorBGTextXY(1, 18, 14, 0, "5.Danh dau o:");
					setColorBGTextXY(2, 19, 15, 0, "- Nguoi choi co the danh dau o ma ho nghi ngo chua min bang cach su dung co.");
					setColorBGTextXY(1, 21, 14, 0, "6.Chien thang:");
					setColorBGTextXY(2, 22, 15, 0, "- Nguoi choi thang khi tat ca cac o khong chua min duoc mo.");
					setColorBGTextXY(1, 24, 14, 0, "7.That bai:");
					setColorBGTextXY(2, 25, 15, 0, "- Nguoi choi that bai neu mo mot o chua min.");

					setColorBGTextXY(92, 4, 15, 0, "- Su dung cac phim ");
					setColorBGTextXY(94, 5, 15, 0, "mui ten de di chuyen ");
					setColorBGTextXY(92, 6, 15, 0, "- Phim D de mo 1 o");
					setColorBGTextXY(92, 7, 15, 0, "- Phim F de cam co");
					setColorBGTextXY(92, 8, 15, 0, "- Phim Esc de thoat");

					//ko co bom chan,mau vang light
					setColorBGTextXY(92, 12, 0, 14, "  ");
					setColorBGTextXY(95, 12, 0, 6, "  ");
					setColorBGTextXY(97, 12, 15, 0, ": O rong da mo");
					setColorBGTextXY(92, 14, 0, 2, "  ");
					setColorBGTextXY(95, 14, 0, 10, "  ");
					setColorBGTextXY(97, 14, 15, 0, ": O rong chua mo");
					//text 1, mau xanh duong
					setColorBGTextXY(92, 16, 1, 14, " 1");

					//text 2, mau vang
					setColorBGTextXY(94, 16, 2, 14, " 2");

					//text 3, mau do
					setColorBGTextXY(96, 16, 4, 14, " 3");

					//text 4, mau tim
					setColorBGTextXY(98, 16, 13, 14, " 4");

					//text 5, mau den
					setColorBGTextXY(100, 16, 16, 14, " 5");

					//text 6, mau do light
					setColorBGTextXY(102, 16, 12, 14, " 6");

					//text 7, mau xanh light
					setColorBGTextXY(104, 16, 11, 14, " 7");

					//text 8, mau xam
					setColorBGTextXY(106, 16, 8, 14, " 8");
					setColorBGTextXY(108, 16, 15, 0, ": O co bom");
					setColorBGTextXY(110, 17, 15, 0, "lan can");

					////bom
					setColorBGTextXY(92, 19, 16, 12, " *");
					setColorBGTextXY(94, 19, 15, 0, ": O co bom");

					////Co da cam 
					setColorBGTextXY(92, 21, 4, 2, " !");
					setColorBGTextXY(94, 21, 15, 0, ": O cam co");

					////Cam co sai/dung
					setColorBGTextXY(92, 23, 4, 8, " X");
					setColorBGTextXY(95, 23, 4, 14, " *");
					setColorBGTextXY(97, 23, 15, 0, ": O cam co sai/dung");

					////con tro
					setColorBGTextXY(92, 25, 0, 3, " ");
					setColorBGTextXY(94, 25, 15, 0, ": con tro");

					drawSelectBack(0);
					page = 5;
				}
				else if (Choose == 2) {//infor
					deleteRow(0, 35);
					for (int i = 44; i <= 87; i++) {
						setColor(3);
						Sleep(20);
						gotoXY(i, 11);
						std::cout << char(196);
						gotoXY(i, 22);
						std::cout << char(196);
					}
					for (int i = 11; i <= 22; i++) {
						setColor(3);
						Sleep(20);
						gotoXY(44, i);
						std::cout << char(179);
						gotoXY(87, i);
						std::cout << char(179);
					}
					gotoXY(44, 11);
					std::cout << char(218);
					gotoXY(87, 11);
					std::cout << char(191);
					gotoXY(44, 22);
					std::cout << char(192);
					gotoXY(87, 22);
					std::cout << char(217);
					setColorBGTextXY(46, 35 / 2 - 5, 15, 0, "UNIVERSITY OF TRANSPORT HO CHI MINH CITY ");
					setColorBGTextXY(46, 35 / 2 - 4, 15, 0, "CLASS: CN2303CLCA");
					setColorBGTextXY(46, 35 / 2 - 3, 15, 0, "ID GROUP: BT46");
					setColorBGTextXY(50, 35 / 2 - 2, 15, 0, "------------------------------");
					setColorBGTextXY(46, 35 / 2 - 1, 15, 0, "Member 1: Nguyen Ngoc Van Khanh");
					setColorBGTextXY(46, 35 / 2, 15, 0, "Id: 075305008123");
					setColorBGTextXY(46, 35 / 2 + 1, 15, 0, "Member 2: Huynh Dang Yen Nhi");
					setColorBGTextXY(46, 35 / 2 + 2, 15, 0, "Id: 060305003490");
					setColorBGTextXY(46, 35 / 2 + 3, 15, 0, "Member 3: Nguyen Thi Tuyet Nhung");
					setColorBGTextXY(46, 35 / 2 + 4, 15, 0, "Id: 066305012320");
					drawSelectBack(0);
					page = 5;
				}
				else {
					deleteRow(0, 35);
					setColor(15);

					for (int i = 59; i <= 75; i++) {
						setColor(3);
						Sleep(20);
						gotoXY(i, 2);
						std::cout << char(196);
						gotoXY(i, 4);
						std::cout << char(196);
					}
					for (int i = 2; i <= 4; i++) {
						setColor(3);
						Sleep(20);
						gotoXY(59, i);
						std::cout << char(179);
						gotoXY(75, i);
						std::cout << char(179);
					}
					gotoXY(59, 2);
					std::cout << char(218);
					gotoXY(75, 2);
					std::cout << char(191);
					gotoXY(59, 4);
					std::cout << char(192);
					gotoXY(75, 4);
					std::cout << char(217);
					gotoXY(123 / 2, 3);
					std::cout << "by Group BT46\n" << std::endl;
					exit(0);
				}

				break;
			case 2:
				if (Choose == 0) {//beginner
					deleteRow(0, 35);
					page = 3;
					play(9, 9, 10);

				}
				else if (Choose == 1) {//inter

					page = 3;
					deleteRow(0, 35);
					play(16, 16, 40);
				}
				else if (Choose == 2) {//expert

					page = 3;
					deleteRow(0, 35);
					play(30, 30, 99);
				}
				else {
					deleteRow(0, 35);
					page = 1;
					veTieuDe();
					thietkegiaodien();
					drawMenu(0);
				}
				break;
			case 4:// replay/back
				if (Choose == 1) {
					page = 1;
					deleteRow(0, 35);
					veTieuDe();
					thietkegiaodien();
					drawMenu(0);
				}
				else {
					page = 3;
					deleteRow(0, 35);
					if (Bang.Dong == 9) {
						Choose = 0;
					}
					else if (Bang.Dong == 16) {
						Choose = 1;
					}
					else if (Bang.Dong == 30) {
						Choose = 2;
					}
					play(Bang.Dong, Bang.Cot, Bang.Bom);
				}
				break;
			case 5://back
				deleteRow(0, 35);
				page = 1;
				veTieuDe();
				thietkegiaodien();
				drawMenu(0);
			}
		}
		// Kiểm tra nút ESC để thoát vòng lặp
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			deleteRow(0, 35);
			setColor(3);

			for (int i = 59; i <= 75; i++) {
				setColor(3);
				Sleep(20);
				gotoXY(i, 2);
				std::cout << char(196);
				gotoXY(i, 4);
				std::cout << char(196);
			}
			for (int i = 2; i <= 4; i++) {
				setColor(3);
				Sleep(20);
				gotoXY(59, i);
				std::cout << char(179);
				gotoXY(75, i);
				std::cout << char(179);
			}
			gotoXY(59, 2);
			std::cout << char(218);
			gotoXY(75, 2);
			std::cout << char(191);
			gotoXY(59, 4);
			std::cout << char(192);
			gotoXY(75, 4);
			std::cout << char(217);
			gotoXY(123 / 2, 3);
			std::cout << "by Group BT46\n" << std::endl;
			exit(0);
		}

		// Tạm dừng để giảm tải CPU
		Sleep(60);
	}
}
void thietkegiaodien() {
	setColor(4);
	std::string vebom[23] =
	{
		"                                //",
		"                               //",
		"                              ||",
		"                     _________||_______",
		"                    |                  |",
		"               ..___|                  |___..",
		"              /                              \\",
		"             /                                \\",
		"            /                                  \\",
		"           /    /                               \\",
		"          /    /                                 \\",
		"          |   |                                  |",
		"          |   |                                  |",
		"          |   |                                  |",
		"          |   |                                  |",
		"  _____   |   |                                  |",
		"  \\   /   |   \\                                  |",
		"   \\ /  -|-.   \\                                /",
		"    \\ /     \\   \\                              / ",
		"     \\|     |    \\                            / ",
		"      \\     /\\                               / ",
		"       '---'  \\                             / ",
		"               '---------------------------'",
	};


	int x = 73;
	int y = 8;
	for (int i = 0; i < 23; i++) {
		setColor(4);
		gotoXY(x, y);
		std::cout << vebom[i];
		y++;
	}
	

}
void veTieuDe() {
	std::string vetieude[7] =
	{
		" __          __   _   __      _   _____   ______   _          __           _  _____   _____   _______   _____  ________",
		"|  \\        /  | | | |  \\    | | | ____| | _____) \\ \\        /  \\        / / | ____| | ____| |  ____ | | ____| |  ____  \\",
		"|   \\      /   | | | |   \\   | | | |___  | |____   \\ \\      / /\\ \\      / /  | |___  | |___  | |____|| | |___  | |____| /",
		"| |\\ \\    / /| | | | | |\\ \\  | | |  ___| |_____  \\  \\ \\    / /  \\ \\    / /   |  ___| |  ___| |  _____| |  ___| |  ___  /",
		"| | \\ \\  / / | | | | | | \\ \\ | | | |           | |   \\ \\  / /    \\ \\  / /    | |     | |     | |       | |     | |   \\ \\",
		"| |  \\ \\/ /  | | | | | |  \\ \\| | | |___   _____| |    \\ \\/ /      \\ \\/ /     | |___  | |___  | |       | |___  | |    \\ \\",
		"|_|   \\__/   |_| |_| |_|   \\___| |_____| (_______|     \\__/        \\__/      |_____| |_____| |_|       |_____| |_|     \\_\\",
	};
	int a = 1;
	int b = 0;
	for (int i = 0; i < 7; i++) {
		gotoXY(a, b);
		std::cout << vetieude[i];
		b++;
	}
}
void chinhToaDoTable() {
	if (Choose == 0) {
		toadox = (consoleWidth / 2) - (Bang.Dong / 2) - 10;
		toadoy = (consoleHeight / 2) - (Bang.Cot / 2) - 4;
	}
	else if (Choose == 1) {
		toadox = (consoleWidth / 2) - (Bang.Dong / 2) - 10;
		toadoy = (consoleHeight / 2) - (Bang.Cot / 2) - 5;
	}
	else if (Choose == 2) {
		toadox = (consoleWidth / 2) - (Bang.Dong / 2) - 10;
		toadoy = (consoleHeight / 2) - (Bang.Cot / 2) + 2;
	}
}
void trangthaiBom() {
	setColorBGTextXY(toadox, toadoy - 1, 15, 0, "Bom:%d", Bang.Bom - Bang.Co);
}
void veTrangThai(int trangthai) {
	//khung cho map va bom
	setBackgroundColor(0);
	for (int i = 9; i <= 25; i++) {
		setColor(5);
		Sleep(10);
		gotoXY(i, 4);
		std::cout << char(196);
		gotoXY(i, 7);
		std::cout << char(196);
	}
	for (int i = 4; i <= 7; i++) {
		setColor(5);
		Sleep(10);
		gotoXY(9, i);
		std::cout << char(179);
		gotoXY(25, i);
		std::cout << char(179);
	}
	gotoXY(9, 4);
	std::cout << char(218);
	gotoXY(25, 4);
	std::cout << char(191);
	gotoXY(9, 7);
	std::cout << char(192);
	gotoXY(25, 7);
	std::cout << char(217);
	setBackgroundColor(0);
	//khung cho guide
	for (int i = 5; i <= 30; i++) {

		setColor(5);
		Sleep(10);
		gotoXY(i, 10);
		std::cout << char(196);
		gotoXY(i, 17);
		std::cout << char(196);
	}
	for (int i = 10; i <= 17; i++) {
		setColor(5);
		Sleep(10);
		gotoXY(5, i);
		std::cout << char(179);
		gotoXY(30, i);
		std::cout << char(179);
	}
	gotoXY(5, 10);
	std::cout << char(218);
	gotoXY(30, 10);
	std::cout << char(191);
	gotoXY(5, 17);
	std::cout << char(192);
	gotoXY(30, 17);
	std::cout << char(217);
	setBackgroundColor(0);
	//map va so bom
	setColorBGTextXY(11, 5, 15, 0, "Map:%dx%d", Bang.Dong, Bang.Cot);
	setColorBGTextXY(11, 6, 15, 0, "Bom:%d", Bang.Bom);
	//guide
	setColorBGTextXY(7, 11, 15, 0, "- Su dung cac phim ");
	setColorBGTextXY(9, 12, 15, 0, "mui ten de di chuyen ");
	setColorBGTextXY(7, 14, 15, 0, "- Phim D de mo 1 o");
	setColorBGTextXY(7, 16, 15, 0, "- Phim F de cam co");


	//trang thai
	if (trangthai == 1) {
		setColorBGTextXY(consoleWidth - 15, 1, 15, 0, "Playing...");
	}
	else if (trangthai == 2) {
		setColorBGTextXY(consoleWidth - 13, 1, 3, 0, "WIN");
	}
	else if (trangthai == 3) {
		setColorBGTextXY(consoleWidth - 13, 1, 4, 0, "LOSE");
	}
	
	for (int i = consoleWidth - 20; i <= consoleWidth - 2; i++) {
		setColor(5);

		gotoXY(i, 0);
		std::cout << char(196);
		gotoXY(i, 2);
		std::cout << char(196);
	}
	for (int i = 0; i <= 2; i++) {
		setColor(5);
		Sleep(10);
		gotoXY(consoleWidth - 20, i);
		std::cout << char(179);
		gotoXY(consoleWidth - 2, i);
		std::cout << char(179);
	}
	gotoXY(consoleWidth - 20, 0);
	std::cout << char(218);
	gotoXY(consoleWidth - 2, 0);
	std::cout << char(191);
	gotoXY(consoleWidth - 20, 2);
	std::cout << char(192);
	gotoXY(consoleWidth - 2, 2);
	std::cout << char(217);



}
void drawMenu(int numChoose) {
	Choose = numChoose;

	index = 4;
	for (int i = (consoleWidth / 2) - 10; i <= 75; i++) {
		setColor(5);
		Sleep(1);
		gotoXY(i, 10);
		std::cout << char(196);
		gotoXY(i, 15);
		std::cout << char(196);
	}
	setColorBGTextXY((consoleWidth / 2), 11, ((numChoose == 0) ? 2 : 15), 0, "PLAY");

	setColorBGTextXY((consoleWidth / 2), 12, ((numChoose == 1) ? 2 : 15), 0, "RULES");

	setColorBGTextXY((consoleWidth / 2), 13, ((numChoose == 2) ? 2 : 15), 0, "INFO");

	setColorBGTextXY((consoleWidth / 2), 14, ((numChoose == 3) ? 2 : 15), 0, "QUIT");
}
void drawLevel(int numChoose) {
	Choose = numChoose;
	index = 4;
	setColorBGTextXY((consoleWidth / 2) - 6, 9, 14, 0, "CHOOSE LEVEL");

	for (int i = (consoleWidth / 2) - 15; i <= 75; i++) {
		setColor(5);
		Sleep(1);
		gotoXY(i, 10);
		std::cout << char(196);
		gotoXY(i, 15);
		std::cout << char(196);
	}
	setColorBGTextXY((consoleWidth / 2) - 7, 11, ((numChoose == 0) ? 2 : 15), 0, "BEGINNER (9X9)");

	setColorBGTextXY((consoleWidth / 2) - 10, 12, ((numChoose == 1) ? 2 : 15), 0, "INTERMEDIATE (16X16)");

	setColorBGTextXY((consoleWidth / 2) - 7, 13, ((numChoose == 2) ? 2 : 15), 0, "EXPERT (30X30)");

	setColorBGTextXY((consoleWidth / 2) - 2.5, 14, ((numChoose == 3) ? 2 : 15), 0, "BACK");
}
void drawMenuSelect(int numChoose) {
	Choose = numChoose;
	index = 2;
	setColorBGTextXY(11, 20, ((numChoose == 0) ? 2 : 15), 0, "REPLAY");
	setColorBGTextXY(11, 21, ((numChoose == 1) ? 2 : 15), 0, "BACK");
	for (int i = 9; i <= 18; i++) {
		setColor(5);
		gotoXY(i, 19);
		std::cout << char(196);
		gotoXY(i, 22);
		std::cout << char(196);
	}
	for (int i = 19; i <= 22; i++) {
		setColor(5);
		gotoXY(9, i);
		std::cout << char(179);
		gotoXY(18, i);
		std::cout << char(179);
	}
	gotoXY(9, 19);
	std::cout << char(218);
	gotoXY(18, 19);
	std::cout << char(191);
	gotoXY(9, 22);
	std::cout << char(192);
	gotoXY(18, 22);
	std::cout << char(217);

}
void drawSelectBack(int numChoose) {
	Choose = numChoose;
	index = 1;
	setColorBGTextXY(55, 30, ((numChoose == 1) ? 2 : 15), 0, "'press Enter to back'");

}
int main() {
	SetConsoleTitle(TEXT("MINESWEEPER - BT46"));
	resizeConsole(consoleWidth, consoleHeight);

	Cursor(false);
	veTieuDe();
	thietkegiaodien();
	drawMenu(0);
	page = 1;
	nhapPhim();

	setColor(0);
	std::cout << "\n";
	system("pause");

	return 0;
}

