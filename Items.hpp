#pragma once
#include "Base.hpp"

class ItemBase                       //道具类基类
{
protected:
	pos m_basepos;
	HitBox m_hbox;
	int m_life;
	int m_value;
public:
	ItemBase() {};
	ItemBase(pos basepos,HitBox hboxps,int value);
	~ItemBase(){};
	int Update(HitBox plhbox);
};

class CureHeart:public ItemBase
{
private:
	static string m_ID;
public:
	CureHeart(pos basepos, HitBox hbox,int value);
	~CureHeart() {};
	int Paint();
};

class Shield :public ItemBase
{
private:
	static string m_ID;
public:
	Shield(pos basepos, HitBox hbox, int value);
	~Shield() {};
	int Paint();
};

class SpeedShoes :public ItemBase
{
private:
	static string m_ID;
public:
	SpeedShoes(pos basepos, HitBox hbox, int value);
	~SpeedShoes() {};
	int Paint();
};



ItemBase::ItemBase(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = alive;
}
int ItemBase::Update(HitBox plhbox)
{
	if (m_hbox.CheckBoxHit(plhbox) == true)
		m_life = dead;
	return DONE;
}


string CureHeart::m_ID = "CureHeart";
CureHeart::CureHeart(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = alive;
}
int CureHeart::Paint()
{
	return DONE;
}

string Shield::m_ID = "Shield";
Shield::Shield(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = alive;
}
int Shield::Paint()
{
	return DONE;
}

string SpeedShoes::m_ID = "SpeedShoes";
SpeedShoes::SpeedShoes(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = alive;
}
int SpeedShoes::Paint()
{
	return DONE;
}