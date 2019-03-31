#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <winbgim.h>
#include "qam.h"
#include "complex.h"
using namespace std;

vector<int> inputBinSeq(){				// Nhap chuoi bit vao tu ban phim
	vector<int> binSeq;
	cout << "Nhap chuoi bit: " << endl;
	char key;
	while (true){
		key = _getch();
		if (key == '0' || key == '1'){      // Neu ki tu nhap vao la 0 hoac 1 thi chap nhan
			binSeq.push_back(key - '0');
			cout << key;
		}
		else if (key == 8 && binSeq.size() > 0){	// Xoa ki tu
			binSeq.pop_back();
			cout << "\b \b";
		}
		else if (key == 13) {			// Neu nhan Enter thi ket thuc viec nhap
			break;
		}
	}
	cout << endl;
	if (binSeq.size() % 4){				// Neu chieu dai chuoi bit khong chia het cho 4 thi chen them cac bit 0 vao cuoi
		int padLen = 4 - binSeq.size() % 4;
		for (int i = 0; i < padLen; i++)
			binSeq.push_back(0);		// Chen them cac bit 0 vao cuoi
	}
	return binSeq;
}

int main(){
	srand(time(NULL));
	int choice;
	// Lua chon kieu tao chuoi bit
	cout << "Moi ban chon:" << endl;
	cout << " 1. Tao chuoi bit ngau nhien" << endl;
	cout << " 2. Nhap chuoi bit tu ban phim" << endl;
	cout << "Lua chon cua ban: ";
	cin >> choice;
	cout << endl;
	vector<int> binSeq;
	if (choice == 1){	// Tao chuoi bit ngau nhien voi do dai nhap vao tu ban phim
		int binLen;
		cout << "Nhap do dai chuoi bit: ";
		cin >> binLen;	
		cout << "Dang sinh ra chuoi bit ngau nhien co do dai " << binLen << " ..." << endl;
		for (int i = 0; i < binLen; i++){
			binSeq.push_back(rand() % 2);	// Tao cac bit ngau nhien
		}
	}
	else if (choice == 2){	// Nhap chuoi bit tu ban phim
		binSeq = inputBinSeq();
	}
	//--------------------------------------------------------------------------------------------------
	// Hien thi chuoi bit da tao
	cout << endl;
	cout << "Chuoi bit da tao:" << endl;
	for (int i = 0; i < binSeq.size(); i++){
		cout << binSeq[i];
	}
	cout << endl;
	fstream file;
	file.open("../02 Receiver/qamSig.dat", ios::out);
	//--------------------------------------------------------------------------------------------------
	// Thuc hien dieu che QAM16
	vector<complex> qamSig = qamMod(binSeq);
	//--------------------------------------------------------------------------------------------------
	initwindow(1350,350);
	setwindowtitle("QAM16 Modulation");
	setbkcolor(15);	// background color is white
	cleardevice();
	setcolor(12);
	moveto(250, 50);
	settextstyle(4, HORIZ_DIR, 5);
	outtext("QAM16 MODULATION");
	setcolor(0);		// color is black
	moveto(20, 100);
	lineto(20, 300);
	moveto(10, 200);
	lineto(1340, 200);
	moveto(20,200);
	setcolor(1); 		// color is blue
	setlinestyle(0, 0, 2);
	for(int i = 0; i < qamSig.size(); i++){
		for(int j = 0; j <= 100; j++){
			lineto(20 + 100 * i + j, 200 - (int) ((60 * qamSig[i].module()) * sin(qamSig[i].argument() + j * PI / 25.0)));
		}
		file << qamSig[i].module() << " " << qamSig[i].argument() << endl;
	}
	file.close();
	getch();
}
