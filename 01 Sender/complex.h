#pragma once

#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <cmath>

#ifndef PI
#define PI 3.141592653589793238460
#endif

class complex
{
public:
	float re, im;
public:
	complex(float a = 0, float b = 0) : re(a), im(b) {};
	complex(const complex& c) : re(c.re), im(c.im) {};
public:
	complex operator + (complex c);
	complex operator - (complex c);
	complex operator * (complex c);
	complex operator * (float c);
	complex operator / (complex c);
	complex operator / (float c);
public:
	void setPole(float r, float phi);
	void setVal(float a, float b);
	float getRe();
	float getIm();
	float module();
	float argument();
	complex conj();
};

#include "complex.h"

void complex::setPole(float r, float phi){
	this->re = r * cos(phi);
	this->im = r * sin(phi);
}

void complex::setVal(float a, float b){
	this->re = a;
	this->im = b;
}

complex complex::operator + (complex c){
	return complex(this->re + c.re, this->im + c.im);
}

complex complex::operator - (complex c){
	return complex(this->re - c.re, this->im - c.im);
}

complex complex::operator * (complex c){
	return complex(this->re * c.re - this->im * c.im, this->re * c.im + this->im * c.re);
}

complex complex::operator * (float c){
	return complex(this->re * c, this->im * c);
}

complex complex::operator / (complex c){
	float m = c.re*c.re + c.im*c.im;
	return complex((this->re * c.re + this->im * c.im) / m, (-this->re * c.im + this->im * c.re) / m);
}

complex complex::operator / (float c){
	return complex(this->re / c, this->im / c);
}

complex complex::conj(){
	return complex(this->re, - this->im);
}

float complex::getRe(){
	return this->re;
}

float complex::getIm(){
	return this->im;
}

float complex::module(){
	return sqrt(this->re * this->re + this->im * this->im);
}

float complex::argument(){
	float arg = atan(this->im / this->re);
	if (this->re >= 0){
		if (this->im < 0){
			arg += 2 * PI;
		}
	}
	else {
		arg += PI;
	}
	return arg;
}

#endif
