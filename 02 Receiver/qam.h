#ifndef _QAM_H
#define _QAM_H

#include <vector>
#include "complex.h"
using namespace std;

#ifndef PI
#define PI 3.141592653589793238460
#endif

float amp[16]   = {1.0, 0.75, 1.0, 0.75, 0.75, 0.33, 0.75, 0.33, 1.0, 0.75, 1.0, 0.75, 0.75, 0.33, 0.75, 0.33};
float phase[16] = {0.75, 0.917, 1.25, 1.083, 0.583, 0.75, 1.417, 1.25, 0.25, 0.083, 1.75, 1.917, 0.417, 0.25, 1.583, 1.75};

complex mean(vector<complex> v){		// Tinh gia tri trung binh cua mot day so phuc
	complex t;
	for (int i = 0; i < v.size(); i++){
		t = t + v[i];
	}
	return t / v.size();
}

float stdDev(vector<complex> v){		// Tinh do lech chuan mau
	complex _mean = mean(v);
	float s = 0;
	for (int i = 0; i < v.size(); i++){
		float mod = (v[i] - _mean).module();
		s += mod * mod;
	}
	return sqrt(s / (v.size() - 1));
}

vector<complex> qamMod(vector<int> binSeq){		// Dieu che QAM16
	complex tmp;
	vector<complex> qamSig;
	int hexVal;
	for (int i = 0; i < binSeq.size(); i += 4){		// Lay tung nhom 4 bit de xu ly
		hexVal = binSeq[i] * 8 + binSeq[i + 1] * 4 + binSeq[i + 2] * 2 + binSeq[i + 3];	
		tmp.setPole(amp[hexVal], phase[hexVal] * PI);	// Anh xa toa do tren do thi chom sao
		qamSig.push_back(tmp);
	}
	return qamSig;
}

vector<int> qamDemod(vector<complex> qamSig){	// Giai dieu che QAM16
	vector<int> binSeq;
	int tmp;
	for (int i = 0; i < qamSig.size(); i++){	// Lay tung tin hieu QAM de giai dieu che ra 4 bit
		// Kiem tra vi tri tren do thi chom sao de xac dinh ra 4 bit
		if (qamSig[i].argument() >= 0 && qamSig[i].argument() < PI / 6){
			tmp = 9;
		}
		else if (qamSig[i].argument() >= PI / 6 && qamSig[i].argument() < PI / 3){
			tmp = qamSig[i].module() >= 0.67 ? 8 : 13;
		}
		else if (qamSig[i].argument() >= PI / 3 && qamSig[i].argument() < PI / 2){
			tmp = 12;
		}
		else if (qamSig[i].argument() >= PI / 2 && qamSig[i].argument() < 2 * PI / 3){
			tmp = 4;
		}
		else if (qamSig[i].argument() >= 2 * PI / 3 && qamSig[i].argument() < 5 * PI / 6){
			tmp = qamSig[i].module() >= 0.67 ? 0 : 5;
		}
		else if (qamSig[i].argument() >= 5 * PI / 6 && qamSig[i].argument() < PI){
			tmp = 1;
		}
		else if (qamSig[i].argument() >= PI && qamSig[i].argument() < 7 * PI / 6){
			tmp = 3;
		}
		else if (qamSig[i].argument() >= 7 * PI / 6 && qamSig[i].argument() < 4 * PI / 3){
			tmp = qamSig[i].module() >= 0.67 ? 2 : 7;
		}
		else if (qamSig[i].argument() >= 4 * PI / 3 && qamSig[i].argument() < 3 * PI / 2){
			tmp = 6;
		}
		else if (qamSig[i].argument() >= 3 * PI / 2 && qamSig[i].argument() < 5 * PI / 3){
			tmp = 14;
		}
		else if (qamSig[i].argument() >= 5 * PI / 3 && qamSig[i].argument() < 11 * PI / 6){
			tmp = qamSig[i].module() >= 0.67 ? 10 : 15;
		}
		else if (qamSig[i].argument() >= 11 * PI / 6 && qamSig[i].argument() < 2 * PI){
			tmp = 11;
		}
		// Sau khi xac dinh duoc vi tri thi chen 4 bit vao chuoi bit ben thu
		binSeq.push_back(tmp & 8 ? 1 : 0);	// bit thu nhat
		binSeq.push_back(tmp & 4 ? 1 : 0);	// bit thu hai
		binSeq.push_back(tmp & 2 ? 1 : 0);	// bit thu ba
		binSeq.push_back(tmp & 1 ? 1 : 0);	// bit thu tu
	}
	return binSeq;
}

#endif
