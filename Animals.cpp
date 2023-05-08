
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include<iostream>
#include<math.h>
#include<random>

#include"Animals.h"
#include "GlobalData.h"

using namespace std;



int Animal::isCry()
{
	if (DoNo < 50)
		return 1;
	return 0;
}
int Animal::isDie()
{
	if (DoNo < 10 || tuoi == TuoiDoi)
		return 1;
	return 0;
}
void Animal::SetPos(int x, int y)
{
	pos_x = x;
	pos_y = y;
}



Sheep::Sheep()
{
	maso = 2;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(12, 15);//tu 15- 20 tuoi

	auto n = uni(rng);
	TuoiDoi = n;
	DoNo = 50;

	this->SetTrongLuong();//chọn ngẫu nhiên Trong Luong
	this->SetTuoi();//Chon ngau nhien tuoi

	str_TuoiDoi = to_string(TuoiDoi);
	str_DoNo = to_string((int)DoNo);
	str_TrongLuong = to_string((int)TrongLuong);
	str_tuoi = to_string(tuoi);
};

void Sheep::SetTrongLuong()
{
	//Random Trong Luong
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(20, 52);//Trong luong Cuu 20 -52kg
	auto n = uni(rng);
	this->TrongLuong = n;
}
void Sheep::SetTuoi()
{
	//Random Tuoi
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(100, 3000);//Tuoi tu 100->3000 ngày
	auto n = uni(rng);
	this->tuoi = n;
}
//thay doi do no theo thoi gian
void Sheep::ThayDoiDoNo(int t)
{
	double a = t / 60;
	this->DoNo = this->DoNo * pow(0.84, (a / 8));
	str_DoNo = to_string((int)DoNo);
}


//thay doi do no theo thu an
void Sheep::An(LMouseMode &mouse)
{
	double x = 0;
	switch (mouse)
	{
	case MOUSE_MODE_FOOD_ALL_0_1KG:
	case MOUSE_MODE_FOOD_0_1KG: 
	{
		x = 0.1;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_0_5KG:
	case MOUSE_MODE_FOOD_0_5KG : 
	{
		x = 0.5;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_1KG:
	case MOUSE_MODE_FOOD_1KG :
	{
		x = 1;
		break;
	}
	default:
		break;
	}
	this->DoNo = this->DoNo * pow(1.2, (x / 1));//do no tăng lên 20% sau khi ăn 1 kg
	if (this->DoNo > 100)
	{
		this->DoNo = 100;
	}
		str_DoNo = to_string((int)DoNo);

	ThayDoiTrongLuong();
}
//thay doi trong luong sau 1 bua an(tra ve 1 neu tang)
int Sheep::ThayDoiTrongLuong()
{
	if (this->DoNo < 100)
		return 0;
	else
	{
		//sau bữa ăn nếu đo no=100% thì Cừu sẽ tăng tuef 1-2 kg
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution <int> uni(1, 2);//

		auto n = uni(rng);
		this->TrongLuong += (double)n;
		str_TrongLuong = to_string((int)DoNo);
		return 1;
	}
}
//thay doi vi tri muon thay doi==> thay đổi độ no
void Sheep::ThayDoiViTri(int x, int y)
{
	double x1 = pos_x / 100;
	double y1 = pos_y / 100;

	double x2 = x / 100;
	double y2 = y / 100;

	int S = sqrt((double)(pow(x1 - x2, 2) + pow(y1 - y2, 2)));

	this->DoNo = this->DoNo * pow(0.94, S);//độ no giảm 6%/m
	str_DoNo = to_string((int)DoNo);

	pos_x = x;
	pos_y = y;

}

//**********=======chiken===============*********




Chicken::Chicken()
{
	maso = 4;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(7, 8);//tu 7- 8 (năm)

	auto n = uni(rng);
	TuoiDoi = n;

	this->SetTrongLuong();//chọn ngẫu nhiên Trong Luong
	this->SetTuoi();//Chon ngau nhien tuoi

	DoNo = 50;

	str_TuoiDoi = to_string(TuoiDoi);
	str_DoNo = to_string((int)DoNo);
	str_TrongLuong = to_string((int)TrongLuong);
	str_tuoi = to_string(tuoi);

}




void Chicken::SetTrongLuong()
{
	//Random Trong Luong
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(0.5, 2.8);//Trong luong Gà truong thành 0.5-2.8kg
	auto n = uni(rng);
	this->TrongLuong = n;
}
void Chicken::SetTuoi()
{
	//Random Tuoi
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(100, 2000);//Tuoi tu 100->2000 ngày
	auto n = uni(rng);
	this->tuoi = n;
}
//thay doi do no theo thoi gian
void Chicken::ThayDoiDoNo(int t)
{
	double a = t / 60;
	this->DoNo = this->DoNo * pow(0.9, (a / 12));
	str_DoNo = to_string((int)DoNo);

}
//thay doi do no theo thức ăn
void Chicken::An(LMouseMode &mouse)
{
	double x = 0;
	switch (mouse)
	{
	case MOUSE_MODE_FOOD_ALL_0_1KG:
	case MOUSE_MODE_FOOD_0_1KG:
	{
		x = 0.1;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_0_5KG:
	case MOUSE_MODE_FOOD_0_5KG:
	{
		x = 0.5;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_1KG:
	case MOUSE_MODE_FOOD_1KG:
	{
		x = 1;
		break;
	}
	default:
		break;
	}
	this->DoNo = this->DoNo * pow(2, (x / 0.2));//gà độ nô=100%/0,2 kg lương thực
	if (this->DoNo > 100)
	{
		this->DoNo = 100;
	}
	str_DoNo = to_string((int)DoNo);
	ThayDoiTrongLuong();
}
//thay doi trong luong sau 1 bua an(tra ve 1 neu tang)
int Chicken::ThayDoiTrongLuong()
{
	if (this->DoNo < 100)
		return 0;
	else
	{
		//sau bữa ăn nếu đo no=100% thì Chicken tăng từ 0.01-0.2 (kg)
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution <int> uni(0.01, 0.2);

		auto n = uni(rng);
		this->TrongLuong += (double)n;
		str_TrongLuong = to_string((int)TrongLuong);
		return 1;
	}
}
//thay doi vi tri muon thay doi==> thay đổi độ no
void Chicken::ThayDoiViTri(int x, int y)
{
	double x1 = pos_x / 100;
	double y1 = pos_y / 100;

	double x2 = x / 100;
	double y2 = y / 100;

	int S = sqrt((double)(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
	this->DoNo = this->DoNo * pow(0.9, S);//độ no giảm 10%/m
	str_DoNo = to_string((int)DoNo);

	pos_x = x;
	pos_y = y;

}

//********========PIG=========********



Pig::Pig()
{
	maso = 3;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(5, 10);//tu 5- 10 (năm)

	auto n = uni(rng);
	TuoiDoi = n;

	this->SetTrongLuong();//chọn ngẫu nhiên Trong Luong
	this->SetTuoi();//Chon ngau nhien tuoi

	DoNo = 50;

	str_TuoiDoi = to_string(TuoiDoi);
	str_DoNo = to_string((int)DoNo);
	str_TrongLuong = to_string((int)TrongLuong);
	str_tuoi = to_string(tuoi);
}

void Pig::SetTrongLuong()
{
	//Random Trong Luong 
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(50, 240);//Trong luong Heo 50-240kg
	auto n = uni(rng);
	this->TrongLuong = n;
}
void Pig::SetTuoi()
{
	//random tuoi
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(100, 3000);//Tuoi tu 100->3000 ngày
	auto n = uni(rng);
	this->tuoi = n;
}
//thay doi do no theo thoi gian t(h)
void Pig::ThayDoiDoNo(int t)
{//độ no giảm 7%/8 giờ
	double a = t / 60;
	this->DoNo = this->DoNo * pow(0.93, (a / 8));
	str_DoNo = to_string((int)DoNo);

}
//thay doi do no theo thức ăn x(kg)
void Pig::An(LMouseMode &mouse)
{
	double x = 0;
	switch (mouse)
	{
	case MOUSE_MODE_FOOD_ALL_0_1KG:
	case MOUSE_MODE_FOOD_0_1KG:
	{
		x = 0.1;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_0_5KG:
	case MOUSE_MODE_FOOD_0_5KG:
	{
		x = 0.5;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_1KG:
	case MOUSE_MODE_FOOD_1KG:
	{
		x = 1;
		break;
	}
	default:
		break;
	}
	this->DoNo = this->DoNo * pow(1.3, (x / 1));//Lợn tăng 30%/1 kg
	if (this->DoNo > 100)
		this->DoNo = 100;
	str_DoNo = to_string((int)DoNo);
	ThayDoiTrongLuong();
}
//thay doi trong luong sau 1 bua an(tra ve 1 neu tang)
int Pig::ThayDoiTrongLuong()
{
	if (this->DoNo < 100)
		return 0;
	else
	{
		//sau bữa ăn nếu đo no=100% thì Pig tăng từ 1-2 (kg)
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution <int> uni(1 , 2);

		auto n = uni(rng);
		this->TrongLuong += (double)n;
		str_TrongLuong = to_string((int)TrongLuong);
		return 1;
	}
}
//thay doi vi tri muon thay doi==> thay đổi độ no
void Pig::ThayDoiViTri(int x , int y)
{
	double x1 = pos_x / 100;
	double y1 = pos_y / 100;

	double x2 = x / 100;
	double y2 = y / 100;

	int S = sqrt((double)(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
	this->DoNo = this->DoNo * pow(0.93, S);//độ no giảm 7%/m
	str_DoNo = to_string((int)DoNo);

	pos_x = x;
	pos_y = y;
}

//*****=====COW======**********



Cow::Cow()
{
	maso = 1;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(18, 20);//tu 5- 10 (năm)

	auto n = uni(rng);
	TuoiDoi = n;

	this->SetTrongLuong();//chọn ngẫu nhiên Trong Luong
	this->SetTuoi();//Chon ngau nhien tuoi

	DoNo = 50;

	str_TuoiDoi = to_string(TuoiDoi);
	str_DoNo = to_string((int)DoNo);
	str_TrongLuong = to_string((int)TrongLuong);
	str_tuoi = to_string(tuoi);
}


void Cow::SetTrongLuong()
{
	//Random Trong Luong
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(100, 800);//Trong luong Bo truong thành 100-800 kg
	auto n = uni(rng);
	this->TrongLuong = n;
}
void Cow::SetTuoi()
{
	//Random Tuoi
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution <int> uni(100, 3000);//Tuoi tu 1000->3000 ngày
	auto n = uni(rng);
	this->tuoi = n;
}

//thay doi do no theo thoi gian t(h)
void Cow::ThayDoiDoNo(int t)
{//độ no giảm 5%/8 giờ
	double a = t / 60;
	this->DoNo = this->DoNo * pow(0.95, (a / 8));
	str_DoNo = to_string((int)DoNo);

}
//thay doi do no theo thức ăn x(kg)
void Cow::An(LMouseMode &mouse)
{
	double x = 0;
	switch (mouse)
	{
	case MOUSE_MODE_FOOD_ALL_0_1KG:
	case MOUSE_MODE_FOOD_0_1KG:
	{
		x = 0.1;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_0_5KG:
	case MOUSE_MODE_FOOD_0_5KG:
	{
		x = 0.5;
		break;
	}
	case MOUSE_MODE_FOOD_ALL_1KG:
	case MOUSE_MODE_FOOD_1KG:
	{
		x = 1;
		break;
	}
	default:
		break;
	}
	this->DoNo = this->DoNo * pow(1.2,(x / 1));//Bò tăng 20%/1 kg
	if (this->DoNo > 100)
		this->DoNo = 100;
	str_DoNo = to_string((int)DoNo);
	ThayDoiTrongLuong();
}
//thay doi trong luong sau 1 bua an(tra ve 1 neu tang)
int Cow::ThayDoiTrongLuong()
{
	if (this->DoNo < 100)
		return 0;
	else
	{
		//sau bữa ăn nếu đo no=100% thì Cow tăng từ 1-3 (kg)
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution <int> uni(1, 3);

		auto n = uni(rng);
		this->TrongLuong += (double)n;
		str_TrongLuong = to_string((int)TrongLuong);
		return 1;
	}
}
//thay doi vi tri muon thay doi==> thay đổi độ no
void Cow::ThayDoiViTri(int x, int y)
{
	double x1 = pos_x / 100;
	double y1 = pos_y / 100;

	double x2 = x / 100;
	double y2 = y / 100;

	int S = sqrt((double)(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
	this->DoNo = this->DoNo * pow(0.95, S);//độ no giảm 5%/m
	str_DoNo = to_string((int)DoNo);

	pos_x = x;
	pos_y = y;

}

