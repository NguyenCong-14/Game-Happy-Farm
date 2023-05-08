#ifndef ANIMAL_H
#define ANIMAL_H


#pragma once
#include<string>
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <random>

#include "GlobalData.h"
#include "LTexture.h"
#include "Button.h"

using namespace std;

class Animal
{
protected:
	// Data
	int maso;
	int tuoi;
	double TrongLuong;
	int TuoiDoi;
	double DoNo;

	// Position
	int pos_x;
	int pos_y;

	string str_tuoi;
	string str_TuoiDoi;
	string str_TrongLuong;
	string str_DoNo;

public:
	
	Animal()
	{
		maso = 0;
		tuoi = 0;
		TrongLuong = 0;
		TuoiDoi = 0;
		DoNo = 0;

		pos_x = 0;
		pos_y = 0;

	};
	~Animal()
	{
		maso = 0;
		tuoi = 0;
		TrongLuong = 0;
		TuoiDoi = 0;
		DoNo = 0;

		pos_x = 0;
		pos_y = 0;
	};

	virtual void ThayDoiDoNo(int t)=0;//thay đổi độ no theo thời gian
	virtual void An(LMouseMode &mouse )=0;//thay đổi độ no sau khi ăn X(kg) thức ăn
	virtual int ThayDoiTrongLuong()=0;//nếu độ no con vật=100%==>Thay đổi trọng lượng
	virtual void ThayDoiViTri(int,int) = 0;//thay doi do no sau khi di chuyển từ(x1,y1)->(x2,y2)

	void SetPos(int x, int y);
	int isDie();//nếu độ no<10% con vật sẽ chết Trả veef1 nếu con vật chết
	int isCry();//neu độ no <50% con vật kêu Trả về 1 nếu con vật đói
	int Code() {return this->maso;}
	string get_tuoi() { return str_tuoi; }
	string get_TuoiDoi() { return str_TuoiDoi; }
	string get_DoNo() { return str_DoNo; }
	string get_TrongLuong() { return str_TrongLuong; }
	int get_posx() { return pos_x; }
	int get_posy() { return pos_y; }
	void set_TrongLuong(int x) { TrongLuong = x; }
	void set_Tuoi(int x) { tuoi = x; }
};
//------------------
class Sheep :public Animal
{
public:


	Sheep();

	void ThayDoiDoNo(int t);//thay đổi độ no theo thời gian
	void An(LMouseMode &mouse);//thay đổi độ no sau khi ăn X(kg) thức ăn
	int ThayDoiTrongLuong();//nếu độ no con vật=100%==>Thay đổi trọng lượng
	void ThayDoiViTri(int , int );//thay đổi độ no sau khi di chuyển 1 khoảng cách
	void SetTrongLuong();
	void SetTuoi();
};
//------------
class Chicken :public Animal
{
public:


	Chicken();

	void ThayDoiDoNo(int t);//thay đổi độ no theo thời gian
	void An(LMouseMode &mouse);//thay đổi độ no sau khi ăn X(kg) thức ăn
	int ThayDoiTrongLuong();//nếu độ no con vật=100%==>Thay đổi trọng lượng
	void ThayDoiViTri(int , int);//thay đổi độ no sau khi di chuyển 1 khoảng cách
	void SetTrongLuong();
	void SetTuoi();
};

//--------------------
class Pig :public Animal
{
public:


	Pig();

	void ThayDoiDoNo(int t);//thay đổi độ no theo thời gian
	void An(LMouseMode &mouse);//thay đổi độ no sau khi ăn X(kg) thức ăn
	int ThayDoiTrongLuong();//nếu độ no con vật=100%==>Thay đổi trọng lượng
	void ThayDoiViTri(int , int);//thay doi do no sau khi di chuyển từ(x1,y1)->(x2,y2)
	void SetTrongLuong();
	void SetTuoi();
};
//---------------
class Cow :public Animal
{
public:

	Cow();

	void ThayDoiDoNo(int t);//thay đổi độ no theo thời gian
	void An(LMouseMode &mouse);//thay đổi độ no sau khi ăn X(kg) thức ăn
	int ThayDoiTrongLuong();//nếu độ no con vật=100%==>Thay đổi trọng lượng
	void ThayDoiViTri(int, int);//thay doi do no sau khi di chuyển từ(x1,y1)->(x2,y2)
	void SetTrongLuong();
	void SetTuoi();
};

#endif // !ANIMAL_H

