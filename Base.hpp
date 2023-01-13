#pragma once
#include <iostream>                             //你可以不看这个头文件
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
//本头文件用于存放一些全局通用的结构体和预处理宏定义

#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0:1)
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0)

//宏定义（不采用#define，保证安全性）
const int FACE_LEFT = 0;     //人物面部朝向
const int FACE_RIGHT = 1;

const int DONE = 1;          //函数运行状态
const int FAILED = 0;

const int heal = 0;          //物品效果类型
const int shield = 1;
const int speedup = 2;
const int speeddown = 3;

const int alive = 1;       //人物生死
const int dead = 0;

const int accessable = 1;    //方向是否通行
const int unaccess = 0;

const int Xdir = 0;
const int Ydir = 1;        //移动块总行动方向，沿X轴方向或沿Y轴方向

const int upleft = 0;       //四角坐标
const int upright = 1;
const int downleft = 2;
const int downright = 3;

const int shooter = 0;
const int mage = 1;
const int worrior = 2;

const int basewid = 100;      //block基础宽度

const int MAXSIZE_INT = 2147483647;

const int BEGIN_FIRE = 1;
const int END_FIRE = 0;

const int upline = 0;
const int downline = 1;
const int leftline = 2;
const int rightline = 3;  //hbox线条方向

const int ud = 0;
const int lr = 1;   //线段水平与垂直

const int COMPENSATE_PARAM = 15; //碰撞补偿参数

const int HIT = 1;
const int MISS = 0; //子弹碰撞返回值

const int player1 = 1;
const int player2 = 2;   //玩家一玩家二
//全局通用结构体

typedef struct Position  //坐标结构
{
	double x;
	double y;
}pos;
struct Line //线段结构，仅限水平或垂直线段
{
	pos pos1;
	pos pos2;
};
typedef struct ItPosition
{
	double x;
	double y;
	int value;//1表示可用 0表示已被占用
}ipos;

typedef struct DirectionAccess
{
	int up;
	int down;
	int left;
	int right;
}direction;

typedef struct PlayerChoices
{
	int player1;
	int player2;
}pc;//玩家职业选择

int CheckLineDir(Line l1)                //检查线段走向
{
	if (l1.pos1.x == l1.pos2.x)
		return ud;
	else if (l1.pos1.y == l1.pos2.y)
		return lr;
}
bool CheckPLHit(pos p1, Line l1)         //检查点线碰撞
{
	if (CheckLineDir(l1) == lr)
	{
		double minx, maxx;
		if (l1.pos1.x > l1.pos2.x)
		{
			maxx = l1.pos1.x;
			minx = l1.pos2.x;
		}
		else
		{
			maxx = l1.pos2.x;
			minx = l1.pos1.x;
		}
		if (p1.x > minx + COMPENSATE_PARAM && p1.x < maxx - COMPENSATE_PARAM && p1.y >= l1.pos1.y - COMPENSATE_PARAM && p1.y <= l1.pos1.y + COMPENSATE_PARAM)//应该加入补偿参数
			return true;
		else
			return false;
	}
	else if (CheckLineDir(l1) == ud)
	{
		{
			double miny, maxy;
			if (l1.pos1.y > l1.pos2.y)
			{
				maxy = l1.pos1.y;
				miny = l1.pos2.y;
			}
			else
			{
				maxy = l1.pos2.y;
				miny = l1.pos1.y;
			}
			if (p1.y > miny + COMPENSATE_PARAM && p1.y < maxy - COMPENSATE_PARAM && p1.x >= l1.pos1.x - COMPENSATE_PARAM && p1.x <= l1.pos1.x + COMPENSATE_PARAM)//应该加入补偿参数
				return true;
			else
				return false;
		}
	}
}
bool CheckLineHit(Line l1, Line l2)      //检查线线碰撞
{
	int l1dir, l2dir;
	l1dir = CheckLineDir(l1);
	l2dir = CheckLineDir(l2);
	if (l1dir == lr && l2dir == lr)                                      
	{
		if (CheckPLHit(l2.pos1, l1) || CheckPLHit(l2.pos2, l1))           //待重做，需加上补偿参数
			return true;
		else if (CheckPLHit(l1.pos1, l2) || CheckPLHit(l1.pos2, l2))
			return true;
		else
			return false;
	}
	else if (l1dir == ud && l2dir == ud)
	{
		if (CheckPLHit(l2.pos1, l1) || CheckPLHit(l2.pos2, l1))
			return true;
		else if (CheckPLHit(l1.pos1, l2) || CheckPLHit(l1.pos2, l2))
			return true;
		else
			return false;
	}
	else if (l1dir == lr && l2dir == ud)
	{
		double miny, maxy;
		if (l2.pos1.y > l2.pos2.y)
		{
			maxy = l2.pos1.y;
			miny = l2.pos2.y;
		}
		else
		{
			maxy = l2.pos2.y;
			miny = l2.pos1.y;
		}
		if (l1.pos1.y > miny + COMPENSATE_PARAM && l1.pos1.y < maxy - COMPENSATE_PARAM)
		{
			double minx, maxx;
			if (l1.pos1.x > l1.pos2.x)
			{
				maxx = l1.pos1.x;
				minx = l1.pos2.x;
			}
			else
			{
				maxx = l1.pos2.x;
				minx = l1.pos1.x;
			}
			if (l2.pos1.x > minx + COMPENSATE_PARAM && l2.pos1.x < maxx - COMPENSATE_PARAM)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else if (l1dir == ud && l2dir == lr)
	{
		double miny, maxy;
		if (l1.pos1.y > l1.pos2.y)
		{
			maxy = l2.pos1.y;
			miny = l2.pos2.y;
		}
		else
		{
			maxy = l2.pos2.y;
			miny = l2.pos1.y;
		}
		if (l2.pos1.y > miny + COMPENSATE_PARAM && l2.pos1.y < maxy - COMPENSATE_PARAM)
		{
			double minx, maxx;
			if (l2.pos1.x > l2.pos2.x)
			{
				maxx = l2.pos1.x;
				minx = l2.pos2.x;
			}
			else
			{
				maxx = l2.pos2.x;
				minx = l2.pos1.x;
			}
			if (l1.pos1.x > minx + COMPENSATE_PARAM  && l1.pos1.x < maxx - COMPENSATE_PARAM)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}


class HitBox              //碰撞箱类
{
private:
	pos m_UpLeft;         //左上右下坐标
	pos m_DownRight;
	pos m_UpRight;        //剩余两个坐标通过构造函数计算而得
	pos m_DownLeft;
	pos m_Basepos;        //以左下角为基础坐标
	int m_length;         //长度宽度
	int m_width;

public:
	HitBox();                                  //允许无参构造
	HitBox(pos upleftpos, pos downrightpos);
	HitBox(pos basepos, int length, int width);
	HitBox(const HitBox* hbox);
	~HitBox();
	pos GetPoint(int point);
	int Updatepos(pos basepos);
	int Assignment(pos upleftpos, pos downrightpos);   //赋值函数
	int Assignment(pos basepos, int length, int width);
	bool CheckPBHit(pos targetpos);                   //检查点箱碰撞
	bool CheckLBHit(Line l1);                         //检查线箱碰撞
	bool CheckBoxHit(HitBox targethbox);              //检查箱箱碰撞
	void DrawHbox();
	Line GetLine(int line);
};



HitBox::HitBox(pos upleftpos, pos downrightpos)
{
	m_length = downrightpos.y - upleftpos.y;
	m_width = downrightpos.x - upleftpos.x;

	m_UpLeft.x = upleftpos.x;
	m_UpLeft.y = upleftpos.y;

	m_DownRight.x = downrightpos.x;
	m_DownRight.y = downrightpos.y;

	m_Basepos.x = upleftpos.x;
	m_Basepos.y = downrightpos.y;

	m_UpRight.x = downrightpos.x;
	m_UpRight.y = upleftpos.y;

	m_DownLeft.x = upleftpos.x;
	m_DownLeft.y = downrightpos.y;
}
HitBox::HitBox(pos basepos, int length, int width)
{
	m_length = length;
	m_width = width;

	m_Basepos.x = basepos.x;
	m_Basepos.y = basepos.y;

	m_UpLeft.x = basepos.x;
	m_UpLeft.y = basepos.y - length;

	m_DownRight.x = basepos.x + width;
	m_DownRight.y = basepos.y;

	m_DownLeft.x = basepos.x;
	m_DownLeft.y = basepos.y;

	m_UpRight.x = basepos.x + width;
	m_UpRight.y = basepos.y - length;
}
HitBox::HitBox()
{
	pos initpos;
	initpos.x = 0;
	initpos.y = 0;

	m_length = 0;
	m_width = 0;

	m_Basepos.x = initpos.x;
	m_Basepos.y = initpos.y;

	m_UpLeft.x = initpos.x;
	m_UpLeft.y = initpos.y;

	m_UpRight.x = initpos.x;
	m_UpRight.y = initpos.y;

	m_DownLeft.x = initpos.x;
	m_DownLeft.y = initpos.y;

	m_DownRight.x = initpos.x;
	m_DownRight.y = initpos.y;

}
HitBox::HitBox(const HitBox* hbox)
{
	m_Basepos.x = hbox->m_Basepos.x;
	m_Basepos.y = hbox->m_Basepos.y;

	m_UpLeft.x = hbox->m_UpLeft.x;
	m_UpLeft.y = hbox->m_UpLeft.y;

	m_DownRight.x = hbox->m_DownRight.x;
	m_DownRight.y = hbox->m_DownRight.y;

	m_UpRight.x = hbox->m_UpRight.x;
	m_UpRight.y = hbox->m_UpRight.y;

	m_DownLeft.x = hbox->m_DownLeft.x;
	m_DownLeft.y = hbox->m_DownLeft.y;

	m_length = hbox->m_length;
	m_width = hbox->m_width;
}
HitBox::~HitBox() {}
pos HitBox::GetPoint(int point)
{
	if (point == upleft)
		return m_UpLeft;
	else if (point == upright)
		return m_UpRight;
	else if (point == downleft)
		return m_DownLeft;
	else if (point == downright)
		return m_DownRight;
}
int HitBox::Assignment(pos upleftpos, pos downrightpos)
{
	m_length = downrightpos.y - upleftpos.y;
	m_width = downrightpos.x - upleftpos.x;

	m_UpLeft.x = upleftpos.x;
	m_UpLeft.y = upleftpos.y;

	m_DownRight.x = downrightpos.x;
	m_DownRight.y = downrightpos.y;

	m_Basepos.x = upleftpos.x;
	m_Basepos.y = downrightpos.y;

	m_UpRight.x = downrightpos.x;
	m_UpRight.y = upleftpos.y;

	m_DownLeft.x = upleftpos.x;
	m_DownLeft.y = downrightpos.y;

	return DONE;
}
int HitBox::Assignment(pos basepos, int length, int width)
{
	m_length = length;
	m_width = width;

	m_Basepos.x = basepos.x;
	m_Basepos.y = basepos.y;

	m_UpLeft.x = basepos.x;
	m_UpLeft.y = basepos.y + length;

	m_DownRight.x = basepos.x + width;
	m_DownRight.y = basepos.y;

	m_DownLeft.x = basepos.x;
	m_DownLeft.y = basepos.y;

	m_UpRight.x = basepos.x + width;
	m_UpRight.y = basepos.y + length;

	return DONE;
}
int HitBox::Updatepos(pos basepos)
{
	m_Basepos.x = basepos.x;
	m_Basepos.y = basepos.y;

	m_UpLeft.x = m_Basepos.x;
	m_UpLeft.y = m_Basepos.y - m_length;

	m_UpRight.x = m_Basepos.x + m_width;
	m_UpRight.y = m_Basepos.y - m_length;

	m_DownLeft.x = m_Basepos.x;
	m_DownLeft.y = m_Basepos.y;

	m_DownRight.x = m_Basepos.x + m_width;
	m_DownRight.y = m_Basepos.y;

	return DONE;
}
bool HitBox::CheckPBHit(pos targetpos)
{

	if (targetpos.x > m_UpLeft.x && targetpos.x < m_UpRight.x)
	{
		if (targetpos.y > m_UpLeft.y && targetpos.y < m_DownLeft.y)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool HitBox::CheckLBHit(Line l1)
{
	if (CheckLineHit(GetLine(upline), l1) || CheckLineHit(GetLine(downline), l1) || CheckLineHit(GetLine(leftline), l1) || CheckLineHit(GetLine(rightline), l1))
		return true;
	else
	{
		if (CheckPBHit(l1.pos1) || CheckPBHit(l1.pos2))
			return true;
		else
			return false;
	}
}
bool HitBox::CheckBoxHit(HitBox targethbox)
{
	if (CheckLBHit(targethbox.GetLine(upline)) || CheckLBHit(targethbox.GetLine(downline)) || CheckLBHit(targethbox.GetLine(leftline)) || CheckLBHit(targethbox.GetLine(rightline)))
		return true;
	else if (targethbox.CheckLBHit(GetLine(upline)) || targethbox.CheckLBHit(GetLine(downline)) || targethbox.CheckLBHit(GetLine(leftline)) || targethbox.CheckLBHit(GetLine(rightline)))
		return true;
	else
		return false;
}
void HitBox::DrawHbox()
{
	setlinecolor(RGB(60, 255, 80));
	line(m_UpLeft.x, m_UpLeft.y, m_UpRight.x, m_UpRight.y);
	line(m_UpRight.x, m_UpRight.y, m_DownRight.x, m_DownRight.y);
	line(m_DownRight.x, m_DownRight.y, m_DownLeft.x, m_DownLeft.y);
	line(m_DownLeft.x, m_DownLeft.y,m_UpLeft.x, m_UpLeft.y);
}
Line HitBox::GetLine(int line)
{
	Line line1;
	if (line == upline)
	{
		line1.pos1 = m_UpLeft;
		line1.pos2 = m_UpRight;
		return line1;
	}
	else if (line == downline)
	{
		line1.pos1 = m_DownLeft;
		line1.pos2 = m_DownRight;
		return line1;
	}
	else if (line == leftline)
	{
		line1.pos1 = m_UpLeft;
		line1.pos2 = m_DownLeft;
		return line1;
	}
	else if (line == rightline)
	{
		line1.pos1 = m_UpRight;
		line1.pos2 = m_DownRight;
		return line1;
	}
}


bool PBHit(pos targetpos, HitBox hbox)
{
	if (targetpos.x > hbox.GetPoint(upleft).x && targetpos.x < hbox.GetPoint(upright).x)
	{
		if (targetpos.y > hbox.GetPoint(upleft).y && targetpos.y < hbox.GetPoint(downleft).y)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool LBHit(Line l1, HitBox hbox)
{
	if (CheckLineHit(hbox.GetLine(upline), l1) || CheckLineHit(hbox.GetLine(downline), l1) || CheckLineHit(hbox.GetLine(leftline), l1) || CheckLineHit(hbox.GetLine(rightline), l1))
		return true;
	else
	{
		if (hbox.CheckPBHit(l1.pos1) || hbox.CheckPBHit(l1.pos2))
			return true;
		else
			return false;
	}
}
bool BBHit(HitBox hbox1, HitBox hbox2)
{
	if (hbox1.CheckLBHit(hbox2.GetLine(upline)) || hbox1.CheckLBHit(hbox2.GetLine(downline)) || hbox1.CheckLBHit(hbox2.GetLine(leftline)) || hbox1.CheckLBHit(hbox2.GetLine(rightline)))
		return true;
	else if (hbox2.CheckLBHit(hbox1.GetLine(upline)) || hbox2.CheckLBHit(hbox1.GetLine(downline)) || hbox2.CheckLBHit(hbox1.GetLine(leftline)) || hbox2.CheckLBHit(hbox1.GetLine(rightline)))
		return true;
	else
		return false;
}

