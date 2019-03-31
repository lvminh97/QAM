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

float randn(){
	return (rand() % 19999 - 9999) / 10000.0;
}

float BER(vector<int> seq1, vector<int> seq2){	// Tinh ti le loi bit BER
	int cnt = 0;
	for (int i = 0; i < seq1.size(); i++){
		cnt += seq1[i] != seq2[i] ? 1 : 0;
	}
	return (float)cnt / seq1.size();
}

int main(){
	srand(time(NULL));
	cout << "Nhap ten file chua data: ";
	char fName[50];
	fflush(stdin);
	cin.getline(fName, 49);
	cout << "Nhap ti so SNR = ";
	float SNR;
	cin >> SNR;
	cout << endl;
	//--------------------------------------------------------------------------------------------------
	vector<complex> qamSig;
	complex tmp;
	float mod, arg;
	fstream file;
	file.open(fName, ios::in);
	
	while(!file.eof()){
		file >> mod >> arg;
		tmp.setPole(mod, arg);
		qamSig.push_back(tmp);
	}
	qamSig.pop_back();
	//--------------------------------------------------------------------------------------------------
	// Tao nhieu trang Gauss va cho tin hieu dieu che di qua nhieu Gauss
	float Es = stdDev(qamSig);
	Es *= Es;
	float gauss = sqrt(Es / SNR / 2);
	for (int i = 0; i < qamSig.size(); i++){
		qamSig[i] = qamSig[i] + complex(randn(), randn()) * gauss;
	}
	//--------------------------------------------------------------------------------------------------
	// Thuc hien giai dieu che QAM16
	vector<int> binSeq = qamDemod(qamSig);
	//--------------------------------------------------------------------------------------------------
	initwindow(1350,350);
	setwindowtitle("QAM16 Demodulation");
	setbkcolor(15);	// background color is white
	cleardevice();
	setcolor(12);
	moveto(250, 50);
	settextstyle(4, HORIZ_DIR, 5);
	outtext("QAM16 DEMODULATION");
	setcolor(0);		// color is black
	moveto(20, 100);
	lineto(20, 300);
	moveto(10, 200);
	lineto(1340, 200);
	moveto(20,200);
	setcolor(1); 		// color is blue
	setlinestyle(0, 0, 2);
	for(int i = 0; i < binSeq.size(); i++){
		lineto(20 + 25 * i, 200 - 50 * binSeq[i]);
		lineto(20 + 25 * i + 25, 200 - 50 * binSeq[i]);
	}
	getch();
}
