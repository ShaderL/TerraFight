#pragma once
#include "Base.hpp"
#include "Maps.hpp"
#include "easyx.h"

class ItemBase                       //道具类基类
{
public:
	pos m_basepos;
	HitBox m_hbox;
	int m_life = alive;
	int m_value = dead;
	int m_posnum = 0;

	ItemBase() {};
	ItemBase(pos basepos,HitBox hboxps,int value);
	~ItemBase(){};
};

class CureHeart:public ItemBase
{
private:
	static string m_ID;
public:
	CureHeart(pos basepos, HitBox hbox,int value);
	CureHeart(pos basepos, HitBox hbox, int life, int value);
	CureHeart(const CureHeart &a);
	~CureHeart() {};
	int Paint();
	bool Update(HitBox plhbox, MapBase &map);
};

class Shield :public ItemBase
{
private:
	static string m_ID;
public:
	Shield(pos basepos, HitBox hbox, int value);
	Shield(pos basepos, HitBox hbox, int life,int value);
	Shield(const Shield& a);
	~Shield() {};
	int Paint();
	bool Update(HitBox plhbox, MapBase &map);
};

class SpeedShoes :public ItemBase
{
private:
	static string m_ID;
public:
	SpeedShoes(pos basepos, HitBox hbox, int value);
	SpeedShoes(pos basepos, HitBox hbox, int life,int value);
	SpeedShoes(const SpeedShoes& a);
	~SpeedShoes() {};
	int Paint();
	bool Update(HitBox plhbox, MapBase &map);
};


class ItemsCreator
{
private:
	int m_shoetime = 0;
	int m_hearttime = 0;
	int m_shieldtime = 0;
	int m_shoegap;
	int m_heartgap;
	int m_shieldgap;

public:
	ItemsCreator(int shoegap = 900,int heartgap = 90,int shieldgap = 6000);//改gap请去Game.cpp
	~ItemsCreator(){};
	SpeedShoes CreateShoes(MapBase &map);
	Shield CreateShields(MapBase &map);
	CureHeart CreateHearts(MapBase &map);

};



ItemBase::ItemBase(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = alive;
}


CureHeart::CureHeart(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;

	m_life == dead;
}
CureHeart::CureHeart(pos basepos, HitBox hbox, int life, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = life;
}
CureHeart::CureHeart(const CureHeart& a)
{
	m_basepos = a.m_basepos;
	m_hbox = a.m_hbox;
	m_value = a.m_value;
	m_life = a.m_life;
	m_posnum = a.m_posnum;
}
int CureHeart::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;
		loadimage(&img1, L".\\resources\\CureHeart1.jpg", 60, 60);
		loadimage(&img2, L".\\resources\\CureHeart2.jpg", 60, 60);
		putimage(m_basepos.x, m_basepos.y - 60, &img2, SRCAND);
		putimage(m_basepos.x, m_basepos.y - 60, &img1, SRCPAINT);
		//m_hbox.DrawHbox();
	}
	return DONE;
}
bool CureHeart::Update(HitBox plhbox, MapBase &map)
{

	if (m_hbox.CheckBoxHit(plhbox) && m_life == alive)
	{
		m_life = dead;
		cout << '6' << endl;
		cout << m_posnum << endl;
		map.Changeposvalue(m_posnum, 1);
		return true;
	}
	return false;
}


Shield::Shield(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;

	m_life == dead;
}
Shield::Shield(pos basepos, HitBox hbox, int life, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = life;
}
Shield::Shield(const Shield& a)
{
	m_basepos = a.m_basepos;
	m_hbox = a.m_hbox;
	m_value = a.m_value;
	m_life = a.m_life;
	m_posnum = a.m_posnum;
}
int Shield::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;
		loadimage(&img1, L".\\resources\\Shield1.jpg", 60, 60);
		loadimage(&img2, L".\\resources\\Shield2.jpg", 60, 60);
		putimage(m_basepos.x, m_basepos.y - 60, &img2, SRCAND);
		putimage(m_basepos.x, m_basepos.y - 60, &img1, SRCPAINT);
		//m_hbox.DrawHbox();
	}
	return DONE;
}
bool Shield::Update(HitBox plhbox, MapBase &map)
{
	m_hbox.DrawHbox();
	if (m_hbox.CheckBoxHit(plhbox) && m_life == alive)
	{
		m_life = dead;
		map.Changeposvalue(m_posnum, 1);
		return true;
	}
	return false;
}


SpeedShoes::SpeedShoes(pos basepos, HitBox hbox, int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;

	m_life == dead;
}
SpeedShoes::SpeedShoes(pos basepos, HitBox hbox, int life,int value)
{
	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_value = value;
	m_life = life;
}
SpeedShoes::SpeedShoes(const SpeedShoes& a)
{
	m_basepos = a.m_basepos;
	m_hbox = a.m_hbox;
	m_value = a.m_value;
	m_life = a.m_life;
	m_posnum = a.m_posnum;
}
int SpeedShoes::Paint()
{
	if (m_life == alive)
	{
		IMAGE img1, img2;
		loadimage(&img1, L".\\resources\\SpeedShoes1.jpg", 60, 60);
		loadimage(&img2, L".\\resources\\SpeedShoes2.jpg", 60, 60);
		putimage(m_basepos.x, m_basepos.y - 60, &img2, SRCAND);
		putimage(m_basepos.x, m_basepos.y - 60, &img1, SRCPAINT);
		//m_hbox.DrawHbox();
	}
	return DONE;
}
bool SpeedShoes::Update(HitBox plhbox,MapBase &map)
{
	
	if (m_hbox.CheckBoxHit(plhbox) && m_life == alive)
	{
		m_life = dead;
		map.Changeposvalue(m_posnum, 1);
		return true;
	}
	return false;
}



ItemsCreator::ItemsCreator(int shoegap, int heartgap, int shieldgap)
{
	m_shoegap = shoegap;
	m_heartgap = heartgap;
	m_shieldgap = shieldgap;
}
SpeedShoes ItemsCreator::CreateShoes(MapBase &map)
{
	srand((unsigned)time(NULL));
	int posnum;
	pos pos1,uselesspos;
	m_shoetime += 3;

	uselesspos.x = 0;
	uselesspos.y = 0;

	HitBox unshoehbox(uselesspos, 60, 60);           //创建无效item
	SpeedShoes unshoe(uselesspos, unshoehbox, dead, 5);

	if (m_shoetime % m_shoegap == 0)
	{
		m_shoetime = 0;
		posnum = rand() % 4;
		if (posnum == 0)
		{
			pos1.x = map.Getposas(0).x;
			pos1.y = map.Getposas(0).y;

			if (map.Getposas(0).value == 1)
			{
				HitBox shoehbox(pos1, 60, 60);
				SpeedShoes shoe(pos1, shoehbox, 10);
				shoe.m_posnum = 0;
				map.Changeposvalue(0, 0);
				return shoe;
			}
			else
				return unshoe;
		}
		else if (posnum == 1)
		{
			pos1.x = map.Getposas(1).x;
			pos1.y = map.Getposas(1).y;

			if (map.Getposas(1).value == 1)
			{
				HitBox shoehbox(pos1, 60,60);
				SpeedShoes shoe(pos1, shoehbox, 10);
				shoe.m_posnum = 1;
				map.Changeposvalue(1, 0);
				return shoe;
			}
			else
				return unshoe;
		}
		else if (posnum == 2)
		{
			pos1.x = map.Getposas(2).x;
			pos1.y = map.Getposas(2).y;

			if (map.Getposas(2).value == 1)
			{
				HitBox shoehbox(pos1, 60, 60);
				SpeedShoes shoe(pos1, shoehbox, 10);
				shoe.m_posnum = 2;
				map.Changeposvalue(2, 0);
				return shoe;
			}
			else
				return unshoe;
		}
		else if (posnum == 3)
		{
			pos1.x = map.Getposas(3).x;
			pos1.y = map.Getposas(3).y;

			if (map.Getposas(3).value == 1)
			{
				HitBox shoehbox(pos1, 60, 60);
				SpeedShoes shoe(pos1, shoehbox, 10);
				shoe.m_posnum = 3;
				map.Changeposvalue(3, 0);
				return shoe;
			}
			else
				return unshoe;
		}
		else
		{
			return unshoe;
		}
	}
	else
	{
		return unshoe;
	}
}
Shield ItemsCreator::CreateShields(MapBase &map)
{
	srand((unsigned)time(NULL));
	int posnum;
	pos pos1, uselesspos;
	m_shieldtime += 3;

	uselesspos.x = 0;
	uselesspos.y = 0;

	HitBox unshieldhbox(uselesspos, 60, 60);           //创建无效item
	Shield unshield(uselesspos, unshieldhbox, dead, 10);

	if (m_shieldtime % m_shieldgap == 0)
	{
		m_shieldtime = 0;
		posnum = rand() % 4;
		if (posnum == 0)
		{
			pos1.x = map.Getposas(0).x;
			pos1.y = map.Getposas(0).y;

			if (map.Getposas(0).value == 1)
			{
				HitBox shieldhbox(pos1, 60, 60);
				Shield shield(pos1, shieldhbox, 10);
				shield.m_posnum = 0;
				map.Changeposvalue(0, 0);
				return shield;
			}
			else
				return unshield;
		}
		else if (posnum == 1)
		{
			pos1.x = map.Getposas(1).x;
			pos1.y = map.Getposas(1).y;

			if (map.Getposas(1).value == 1)
			{
				HitBox shieldhbox(pos1, 60, 60);
				Shield shield(pos1, shieldhbox, 10);
				shield.m_posnum = 1;
				map.Changeposvalue(1, 0);
				return shield;
			}
			else
				return unshield;
		}
		else if (posnum == 2)
		{
			pos1.x = map.Getposas(2).x;
			pos1.y = map.Getposas(2).y;

			if (map.Getposas(2).value == 1)
			{
				HitBox shieldhbox(pos1, 60, 60);
				Shield shield(pos1, shieldhbox, 10);
				shield.m_posnum = 2;
				map.Changeposvalue(2, 0);
				return shield;
			}
			else
				return unshield;
		}
		else if (posnum == 3)
		{
			pos1.x = map.Getposas(3).x;
			pos1.y = map.Getposas(3).y;

			if (map.Getposas(3).value == 1)
			{
				HitBox shieldhbox(pos1, 60, 60);
				Shield shield(pos1, shieldhbox, 10);
				shield.m_posnum = 3;
				map.Changeposvalue(3, 0);
				return shield;
			}
			else
				return unshield;
		}
		else
		{
			return unshield;
		}
	}
	else
	{
		return unshield;
	}
}
CureHeart ItemsCreator::CreateHearts(MapBase &map)
{
	srand((unsigned)time(NULL));
	int posnum;
	pos pos1, uselesspos;
	m_hearttime += 3;

	uselesspos.x = 0;
	uselesspos.y = 0;

	HitBox uncurehearthbox(uselesspos, 60, 60);           //创建无效item
	CureHeart uncureheart(uselesspos, uncurehearthbox, dead, 40);


	if (m_hearttime % m_heartgap == 0)
	{
		m_hearttime = 0;
		posnum = rand() % 4;
		if (posnum == 0)
		{
			pos1.x = map.Getposas(0).x;
			pos1.y = map.Getposas(0).y;

			if (map.Getposas(0).value == 1)
			{
				HitBox curehearthbox(pos1, 60, 60);
				CureHeart cureheart(pos1, curehearthbox, 10);
				cureheart.m_posnum = 0;
				map.Changeposvalue(0, 0);
				return cureheart;
			}
			else
				return uncureheart;
		}
		else if (posnum == 1)
		{
			pos1.x = map.Getposas(1).x;
			pos1.y = map.Getposas(1).y;

			if (map.Getposas(1).value == 1)
			{
				HitBox curehearthbox(pos1, 60, 60);
				CureHeart cureheart(pos1, curehearthbox, 30);
				cureheart.m_posnum = 1;
				map.Changeposvalue(1, 0);
				return cureheart;
			}
			else
				return uncureheart;
		}
		else if (posnum == 2)
		{
			pos1.x = map.Getposas(2).x;
			pos1.y = map.Getposas(2).y;

			if (map.Getposas(2).value == 1)
			{
				HitBox curehearthbox(pos1, 60, 60);
				CureHeart cureheart(pos1, curehearthbox, 30);
				cureheart.m_posnum = 2;
				map.Changeposvalue(2, 0);
				return cureheart;
			}
			else
				return uncureheart;
		}
		else if (posnum == 3)
		{
			pos1.x = map.Getposas(3).x;
			pos1.y = map.Getposas(3).y;

			if (map.Getposas(3).value == 1)
			{
				HitBox curehearthbox(pos1, 60, 60);
				CureHeart cureheart(pos1, curehearthbox, 30);
				cureheart.m_posnum = 3;
				map.Changeposvalue(3, 0);
				return cureheart;
			}
			else
				return uncureheart;
		}
		else
		{
			return uncureheart;
		}
	}
	else
	{
		return uncureheart;
	}
}