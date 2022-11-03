#pragma once
#include <easyx.h>
#include <time.h>
#include "Base.hpp"
#include "Maps.hpp"



class Bullet
{
public:
	pos m_basepos;      //发射坐标
	int m_width;
	int m_length;
	HitBox m_hbox;       //攻击范围
	int m_damage;
	double m_speed;         //弹道速度
	int m_life = alive;
	int m_face;
	Bullet(pos basepos, int face, int life = alive,int length = 20,int width = 20,int damage = 3,double speed = 1);
	Bullet(const Bullet& a);
	~Bullet();
	int Update(HitBox plhbox, clock_t deltaT);
	int Paint();
};

class MagicBall
{
public:
	pos m_basepos;      //发射坐标
	int m_width;
	int m_length;
	HitBox m_hbox;       //攻击范围
	int m_damage;
	double m_speed;
	int m_life = alive;
	int m_face;
	MagicBall(pos basepos, int face, int life = alive,int length = 60, int width = 60 , int damage = 5 , double speed = 1);
	MagicBall(const MagicBall& a);
	~MagicBall();
	int Update(HitBox plhbox, clock_t deltaT);
	int Paint();
};

class Sword
{
public:
	pos m_basepos;
	int m_length;
	int m_width;
	HitBox m_hbox;
	int m_damage;
	int m_life = alive;
	Sword(pos basepos, int face, int life = alive,int length = 120, int width = 70, int damage = 30);
	Sword(const Sword& a);
	~Sword();
	int Update(HitBox plhbox, clock_t deltaT);
	int Paint();
};


Bullet::Bullet(pos basepos, int face, int life , int length, int width, int damage, double speed)
{
	m_basepos = basepos;
	m_length = length;
	m_width = width;
	HitBox hbox(basepos, length, width);
	m_hbox = hbox;
	m_damage = damage;
	m_speed = speed;
	m_face = face;
	m_life = life;
}
Bullet::Bullet(const Bullet& a)
{
	m_basepos = a.m_basepos;
	m_length = a.m_length;
	m_width = a.m_width;
	m_hbox = a.m_hbox;
	m_damage = a.m_damage;
	m_speed = a.m_speed;
	m_face = a.m_face;
	m_life = a.m_life;
}
Bullet::~Bullet() {};
int Bullet::Update(HitBox plhbox, clock_t deltaT)
{
	m_hbox.Updatepos(m_basepos);
	cout << plhbox.GetPoint(upleft).x << ' ' << plhbox.GetPoint(upright).x << ' ' << plhbox.GetPoint(upleft).y << ' ' << plhbox.GetPoint(downleft).y << endl;
	if (m_life == alive)
	{

		if (plhbox.CheckPBHit(m_hbox.GetPoint(downleft)) == true)
		{
			m_life = dead;
			cout << "HIT!" << endl;
			return HIT;
		}
		if (m_hbox.GetPoint(upleft).x >= 1344 || m_hbox.GetPoint(upright).x <= 0)
		{
			m_life = dead;
		}
		if (m_life == alive)
		{
			if (m_face == FACE_RIGHT)
				m_basepos.x += m_speed * deltaT;
			else if (m_face == FACE_LEFT)
				m_basepos.x -= m_speed * deltaT;
		}
		return MISS;
	}
	else 
	    return MISS;
}
int Bullet::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;        //子弹图片     图片大小用碰撞箱里的长宽
		loadimage(&img1, L".\\resources\\Bullet1.png", m_width, m_length);
		loadimage(&img2, L".\\resources\\Bullet2.png", m_width, m_length);
		putimage(m_basepos.x, m_basepos.y, &img2, SRCAND);
		putimage(m_basepos.x, m_basepos.y, &img1, SRCPAINT);
		return DONE;
	}
}


//int Bullet::g_attack()
//{
//	loadimage(&zidan, L"zidan.png", g_range.m_length, g_range.m_height);
//	static DWORD t1 = 0, t2 = 0;
//	if ((GetAsyncKeyState('J') || GetAsyncKeyState('1')) && (t2 - t1) > g_interval)
//	{
//		BeginBatchDraw();
//		while (1)
//		{
//			//判定方向！
//			putimage(g_handpos.x, g_handpos.y, &zidan);
//			g_handpos.x += g_speed;
//
//			FlushBatchDraw();
//			if (g_range.CheckHitBoxHit(Mage.m_hbox) || g_range.CheckHitBoxHit(Worrior.m_hbox)|| g_range.CheckHitBoxHit(Block.m_hbox))
//			{
//				break;
//			}
//		}
//		EndBatchDraw();
//		t1 = t2;
//		if (g_range.CheckHitBoxHit(Mage.m_hbox) || g_range.CheckHitBoxHit(Worrior.m_hbox))
//		{
//			PlayerBase.m_life -= g_damage;
//		}
//	}
//	t2 = GetTickCount();
//}



MagicBall::MagicBall(pos basepos, int face, int life ,int length, int width, int damage, double speed)
{
	m_basepos = basepos;
	m_length = length;
	m_width = width;
	HitBox hbox(basepos, length, width);
	m_hbox = hbox;
	m_damage = damage;
	m_speed = speed;
	m_face = face;
	m_life = life;

}
MagicBall::MagicBall(const MagicBall& a)
{
	m_basepos = a.m_basepos;
	m_length = a.m_length;
	m_width = a.m_width;
	m_hbox = a.m_hbox;
	m_damage = a.m_damage;
	m_speed = a.m_speed;
	m_face = a.m_face;
	m_life = a.m_life;
}
MagicBall::~MagicBall() {};
int MagicBall::Update(HitBox plhbox, clock_t deltaT)
{
	m_hbox.Updatepos(m_basepos);
	if (m_life == alive)
	{
		if (m_hbox.CheckBoxHit(plhbox) == true)
		{
			m_life = dead;
			cout << "HIT!!!!" << endl;
			return HIT;
		}
		if (m_hbox.GetPoint(upleft).x >= 1344 || m_hbox.GetPoint(upright).x <= 0)
		{
			m_life = dead;
		}
		if (m_life == alive)
		{
			if (m_face == FACE_RIGHT)
				m_basepos.x += m_speed * deltaT;
			else if (m_face == FACE_LEFT)
				m_basepos.x -= m_speed * deltaT;
		}
		return MISS;
	}
	else
		return MISS;
}
int MagicBall::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;        //法球图片     图片大小用碰撞箱里的长宽
		loadimage(&img1, L".\\resources\\MagicBall1.png", m_width, m_length);
		loadimage(&img2, L".\\resources\\MagicBall2.png", m_width, m_length);
		putimage(m_basepos.x, m_basepos.y, &img2, SRCAND);
		putimage(m_basepos.x, m_basepos.y, &img1, SRCPAINT);
		return DONE;
	}
}



//int MagicBall::w_attack()
//{
//	static DWORD t1 = 0, t2 = 0;
//	if ((GetAsyncKeyState('J') || GetAsyncKeyState('1')) && (t2 - t1) > g_interval)
//	{
//		while (1)
//		{
//			//判定方向！
//			w_handpos.x += w_speed;
//
//			if (g_range.CheckHitBoxHit(Mage.m_hbox) || g_range.CheckHitBoxHit(Worrior.m_hbox) || g_range.CheckHitBoxHit(Block.m_hbox))
//			{
//				break;
//			}
//		}
//		t1 = t2;
//		if (g_range.CheckHitBoxHit(Mage.m_hbox) || g_range.CheckHitBoxHit(Worrior.m_hbox))
//		{
//			PlayerBase.m_life -= w_damage;
//		}
//	}
//	t2 = GetTickCount();
//}




Sword::Sword(pos basepos, int face, int life ,int length, int width, int damage)
{
	if (face == FACE_RIGHT)
	{
		m_basepos.x = basepos.x + 50;
		m_basepos.y = basepos.y;
	}
	else if (face == FACE_LEFT)
	{
		m_basepos.x = basepos.x - 50;
		m_basepos.y = basepos.y;
	}
	m_length = length;
	m_width = width;
	HitBox hbox(basepos, length, width);
	m_hbox = hbox;
	m_damage = damage;
	m_life = life;

}
Sword::Sword(const Sword& a)
{
	m_basepos = a.m_basepos;
	m_length = a.m_length;
	m_width = a.m_width;
	m_hbox = a.m_hbox;
	m_damage = a.m_damage;
	m_life = a.m_life;
}
Sword::~Sword() {};
int Sword::Update(HitBox plhbox, clock_t deltaT)
{
	if (m_hbox.CheckBoxHit(plhbox) == true)
		m_life = dead;
	return DONE;
}
int Sword::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;        //剑气图片     图片大小用碰撞箱里的长宽
		loadimage(&img1, L".\\resources\\Sword1.png", m_width, m_length);
		loadimage(&img2, L".\\resources\\Sword2.png", m_width, m_length);
		putimage(m_basepos.x, m_basepos.y, &img2, SRCAND);
		putimage(m_basepos.x, m_basepos.y, &img1, SRCPAINT);
	}
	return DONE;
}



//int Sword::s_attack()
//{
//	static DWORD t1 = 0, t2 = 0;
//	if ((GetAsyncKeyState('J') || GetAsyncKeyState('1')) && (t2 - t1) > g_interval)
//	{
//		while (1)
//		{
//			//判定方向
//
//			if (s_range.CheckHitBoxHit(Mage.m_hbox) || s_range.CheckHitBoxHit(Worrior.m_hbox) || s_range.CheckHitBoxHit(Block.m_hbox))
//			{
//				break;
//			}
//		}
//		t1 = t2;
//		if (s_range.CheckHitBoxHit(Mage.m_hbox) || s_range.CheckHitBoxHit(Worrior.m_hbox))
//		{
//			PlayerBase.m_life -= s_damage;
//		}
//	}
//	t2 = GetTickCount();
//}

