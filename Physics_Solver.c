/*
 * Physics_Solver.c
 *
 *  Created on: Oct 25, 2014
 *      Author: Joseph Marques
 */

#define USE_TI89
#define SAVE_SCREEN
//#define USE_TI92PLUS
//#define USE_V200

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <tigcclib.h>
#define ce chooseEquation(a, x, va, vi, vf, t, u);
#define ua u[0]
#define ux u[1]
#define uva u[2]
#define uvi u[3]
#define uvf u[4]
#define ut u[5]

float findxfrom_va_t(float va, float t) {
	return va * t;
}
//
float findtfrom_x_va(float x, float va) {
	return x / va;
}
//
float findvafrom_x_t(float x, float t) {
	return x / t;
}
//
float findvafrom_vi_vf(float vi, float vf) {
	return (vi + vf) / 2;
}
//
float findvifrom_va_vf(float va, float vf) {
	return (2 * va) - vf;
}
//
float findvffrom_va_vi(float va, float vi) {
	return (2 * va) - vi;
}
//
float findafrom_vf_vi_t(float vf, float vi, float t) {
	return (vf - vi) / t;
}
//
float findvffrom_a_vi_t(float a, float vi, float t) {
	return vi + (a * t);
}
//
float findvifrom_a_vf_t(float a, float vf, float t) {
	return vf - (a * t);
}

float findtfrom_a_vi_vf(float a, float vi, float vf) {
	return (vf - vi) / a;
}

float findxfrom_a_vi_t(float a, float vi, float t) {
	return (vi * t) + ((a * (t * t)) / 2);
}

float findtfrom_a_vi_x(float a, float vi, float x) {
	return ((sqrt(fabs((2 * a * x) + (vi * vi))) + vi) / a);
}

float findxfrom_vi_vf_a(float vi, float vf, float a) {
	return ((vf * vf) - vi * vi) / (2 * a);
}

float findafrom_x_vi_vf(float x, float vi, float vf) {
	return ((vf * vf) - vi * vi) / (2 * x);
}

float findvffrom_a_vi_x(float a, float vi, float x) {
	return sqrt(fabs((2 * a * x) + (vi * vi)));
}

float findvifrom_a_vf_x(float a, float vf, float x) {
	return sqrt(fabs((-2 * a * x) + (vf * vf)));
}

void chooseEquation(float a/*0*/, float x/*1*/, float va/*2*/, float vi/*3*/,
		float vf/*4*/, float t/*5*/, short u[10]) {

	if (uva&&ut&&!(ux)) {

		x=findxfrom_va_t(va, t);
		ux=1;
		ce
	} else if(ux&&uva&&!(ut)) {

		t=fabs(findtfrom_x_va(x,va));
		ut=1;
		ce
	} else if(ux&&ut&&!(uva)) {

		va=findvafrom_x_t(x,t);
		uva=1;
		ce
	} else if(uvi&&uvf&&!(uva)) {

		va=findvafrom_vi_vf(vi, vf);
		uva=1;
		ce
	} else if(uva&&uvi&&!(uvf)) {

		vf=findvffrom_va_vi(va, vi);
		uvf=1;
		ce
	} else if(uva&&uvf&&!(uvi)) {

		vi=findvifrom_va_vf(va, vf);
		uvi=1;
		ce
	} else if(uvi&&uvf&&ut&&!ua) {

		a=findafrom_vf_vi_t(vf, vi, t);
		ua=1;
		ce
	} else if(ua&&uvi&&ut&&!uvf) {

		vf=findvffrom_a_vi_t(a, vi, t);
		uvf=1;
		ce
	} else if(ua&&uvf&&ut&&!uvi) {

		vi=findvifrom_a_vf_t(a, vf, t);
		uvi=1;
		ce
	} else if(ua&&uvi&&uvf&&!ut) {

		t=fabs(findtfrom_a_vi_vf(a, vi, vf));
		ut=1;
		ce
	} else if(ua&&uvi&&uvf&&!ux) {

		x=findxfrom_a_vi_t(a, vi, t);
		ux=1;
		ce
	} else if(ua&&uvi&&ux&&!ut) {

		t=fabs(findtfrom_a_vi_x(a, vi, x));
		ut=1;
		ce
	} else if(uvi&&uvf&&ua&&!ux) {

		x=findxfrom_vi_vf_a(vi, vf, a);
		ux=1;
		ce
	} else if(ux&&uvi&&uvf&&!ua) {

		a=findafrom_x_vi_vf(x, vi, vf);
		ua=1;
		ce
	} else if(ua&&uvf&&ux&&!uvi) {

		vi=findvifrom_a_vf_x(a, vf, x);
		uvi=1;
		ce
	} else if(ua&&uvi&&ux&&!uvf) {

		vf=findvffrom_a_vi_x(a, vi, x);
		uvf=1;
		ce
	} else {
		ua ? printf("Acceleration= %f m/sec^2\n", a) : printf("UNKNOWN ACCELERATION\n");
		ux ? printf("Displacement= %f m\n", x) : printf("UNKNOWN DISPLACEMENT\n");
		uva ? printf("Average Velocity= %f m/sec\n", va) : printf("UNKNOWN AVERAGE VELOCITY\n");
		uvi ? printf("Initial Velocity= %f m/sec\n", vi) : printf("UNKNOWN INITIAL VELOCITY\n");
		uvf ? printf("Final Velocity= %f m/sec\n", vf) : printf("UNKNOWN FINAL VELOCITY\n");
		ut ? printf("Time= %f sec\n", t) : printf("UNKOWN TIME\n");

	}

}

int main() {
	//clrscr();
	//("test");
	float a;

	char str[10];
	short u[10];

	printf("If you don't know a value, enter u.\n");
	printf("Please enter the acceleration: ");
	scanf("%s", str);
	printf("\n");
	if (str[0] == 'u') {
		u[0] = 0;
	} else {
		u[0] = 1;
		a = atof(str);
	}
	float x;
	float va;
	float vi;
	float vf;
	float t;
	printf("Please enter the displacement: ");
	scanf("%s", str);
	printf("\n");
	if (str[0] == 'u') {
		u[1] = 0;
	} else {
		u[1] = 1;
		x = atof(str);
	}
	printf("Please enter the average velocity: ");
	scanf("%s", str);
	printf("\n");
	if (str[0] == 'u') {
		u[2] = 0;
	} else {
		u[2] = 1;
		va = atof(str);
	}
	printf("Please enter the initial velocity: ");
	scanf("%s", str);
	printf("\n");
	if (str[0] == 'u') {
		u[3] = 0;
	} else {
		u[3] = 1;
		vi = atof(str);
	}
	printf("Please enter the final velocity: ");
	scanf("%s", str);
	printf("\n");
	if (str[0] == 'u') {
		u[4] = 0;
	} else {
		u[4] = 1;
		vf = atof(str);
	}
	printf("Please enter the time: ");
	scanf("%s", str);
	printf("\n");
	if (str[0] == 'u') {
		u[5] = 0;
	} else {
		u[5] = 1;
		t = atof(str);
	}

	chooseEquation(a, x, va, vi, vf, t, u);
	//ngetchx();
	//("DONE");
	return 0;
}

