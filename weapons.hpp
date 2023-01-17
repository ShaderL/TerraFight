#pragma once
#include <easyx.h>
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
	Bullet(pos basepos, int face, int life = alive,int length = 20,int width = 20,int damage = 5,double speed = 1);
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
	MagicBall(pos basepos, int face, int life = alive,int length = 60, int width = 60 , int damage = 15 , double speed = 1);
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
	int m_step;
	int m_time;
	int m_face;
	int m_hit = 0;
	Sword();
	Sword(pos basepos, int face, int life = alive,int length = 120, int width = 70, int damage = 30);
	Sword(const Sword& a);
	~Sword();
	bool Update(HitBox plhbox, pos shotpos,int face);
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
	if (m_life == alive)
	{
		if (m_face == FACE_RIGHT)
			m_basepos.x += m_speed * deltaT;
		else if (m_face == FACE_LEFT)
			m_basepos.x -= m_speed * deltaT;

		if (plhbox.CheckPBHit(m_hbox.GetPoint(downleft)) == true)
		{
			m_life = dead;
			return HIT;
		}
		if (m_hbox.GetPoint(upright).x >= 1344 || m_hbox.GetPoint(upleft).x <= 0)
		{
			m_life = dead;
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

Sword::Sword()
{

	m_basepos.x = 50;
	m_basepos.y = 0;

	m_length = 0;
	m_width = 0;
	HitBox hbox(m_basepos,0, 0);
	m_hbox = hbox;
	m_damage = 0;
	m_life = 0;
	m_step = 0;
	m_time = 0;
}
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
	m_step = 0;
	m_time = 0;
}
Sword::Sword(const Sword& a)
{
	m_basepos = a.m_basepos;
	m_length = a.m_length;
	m_width = a.m_width;
	m_hbox = a.m_hbox;
	m_damage = a.m_damage;
	m_life = a.m_life;
	m_time = a.m_time;
	m_step = a.m_step;
}
Sword::~Sword() {};
bool Sword::Update(HitBox plhbox,pos shotpos,int face)
{
	m_basepos = shotpos;
	m_hbox.Updatepos(shotpos);//update positions

	m_face = face;//update face direction

	m_time += 3;       //update animation step
	if (m_time > 6 && m_time < 12)
		m_step = 1;
	else if (m_time >= 12)
	{
		m_life = dead;
	}


	if (m_hbox.CheckBoxHit(plhbox))//return hb hit
		return true;
	else 
        return false;
}
int Sword::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;        //剑气图片     图片大小用碰撞箱里的长宽
		int xpl = 65, yp = 40, xpr = 45;//坐标偏移量
		if (m_step == 0)
		{

			if (m_face == FACE_LEFT)
			{
				loadimage(&img1, L".\\resources\\Sword1l.png", m_width, m_length);
				loadimage(&img2, L".\\resources\\Sword11l.png", m_width, m_length);
				putimage(m_basepos.x - xpl, m_basepos.y - yp, &img2, SRCAND);
				putimage(m_basepos.x - xpl, m_basepos.y - yp, &img1, SRCPAINT);
			}
			else if (m_face == FACE_RIGHT)
			{
				loadimage(&img1, L".\\resources\\Sword1r.png", m_width, m_length);
				loadimage(&img2, L".\\resources\\Sword11r.png", m_width, m_length);
				putimage(m_basepos.x + xpr, m_basepos.y - yp, &img2, SRCAND);
				putimage(m_basepos.x + xpr, m_basepos.y - yp, &img1, SRCPAINT);
			}
		}
		else if (m_step == 1)
		{

			if (m_face == FACE_LEFT)
			{
				loadimage(&img1, L".\\resources\\Sword2l.png", m_width, m_length);
				loadimage(&img2, L".\\resources\\Sword22l.png", m_width, m_length);
				putimage(m_basepos.x - xpl, m_basepos.y - yp, &img2, SRCAND);
				putimage(m_basepos.x - xpl, m_basepos.y - yp, &img1, SRCPAINT);
			}
			else if (m_face == FACE_RIGHT)
			{
				loadimage(&img1, L".\\resources\\Sword2r.png", m_width, m_length);
				loadimage(&img2, L".\\resources\\Sword22r.png", m_width, m_length);
				putimage(m_basepos.x + xpr, m_basepos.y - yp, &img2, SRCAND);
				putimage(m_basepos.x + xpr, m_basepos.y - yp, &img1, SRCPAINT);
			}
		}
	}
	return DONE;
}

//V1.0