#pragma once
#include <iostream>
#include <string.h>
#include <ctime>
#include <Windows.h>
//am thanh
#include "resource.h"
#pragma comment(lib,"winmm.lib")
#define sound(namesound) (PlaySound(MAKEINTRESOURCE(namesound),GetModuleHandle(NULL),SND_RESOURCE | SND_SYNC));
//chinh man console
#define consoleWidth 123
#define consoleHeight 35

struct Table {
	int Dong = 0;
	int Cot = 0;
	int Bom = 0;
	int Co = 0;
	int oDaMo = 0;
};

struct Cell {
	bool CoBom = false;
	bool DaMo = false;
	bool CamCo = false;
	int BomLanCan = 0;
};
extern int page, Choose, index;


void taoMang2Chieu();
void xoaMang2Chieu();
void play(int Dong, int Cot, int SoBom);
void veBang();
void veO(int x, int y, int soMau);
void imBom();
void nhapPhim();
void thietkegiaodien();
void veTieuDe();
void veTrangThai(int trangthai);
void chinhToaDoTable();
void win();
void lose();
void trangthaiBom();
void drawMenu(int numChoose);
void drawLevel(int numChoose);
void drawMenuSelect(int numChoose);
void drawSelectBack(int numChoose);


