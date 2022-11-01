#pragma once
#include <vector>
#include <easyx.h>
#include "Base.hpp"

class Block                                                 //请看这里
{
protected:
	pos m_basepos;
	HitBox m_hbox;
	int m_life;
	int m_width;//必须为basewid的整数倍
	static int m_height;

public:
	Block(){};
	Block(pos basepos,HitBox hbox,int length);
	~Block();
	virtual int Draw();                                      //请在cpp文件里实现Draw函数
	int Delete();
	int Update();
	HitBox GetHBox();
};
class MovingBlock:public Block                         //忽略这个类
{
private:
	int m_speed;
	pos m_beginpos;
	pos m_endpos;
	int m_dir;   //当前移动方向
	int m_totaldir;

public:
	MovingBlock(pos basepos,HitBox hbox,int speed,pos beginpos,pos endpos);
	~MovingBlock();
	int Paint();
	int Move();
};

class MapBase                                         //这是地图类，可以把贴图的路径写到 m_sourcepath.sourcepath 里。（去Maps.cpp里的Mapbase构造函数里写）
{
protected:
	int m_blocknum;
	vector<Block> m_blocklist;

public:
	MapBase();
	~MapBase();
	int Update();
	int Draw();                                  //请在Maps.cpp里实现Draw函数（画block时直接调用block.draw()就行（你刚刚实现的））
	int GetBlockNum();
	Block GetBlock(int num);
};




Block::Block(pos basepos, HitBox hbox, int width)
{
	m_hbox = hbox;
	m_width = width;

	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_life = alive;
	m_hbox = hbox;
}
int Block::m_height = 100;
Block::~Block() {}
int Block::Draw()                        //实现后请直接翻到最下面看MapBase的构造函数和MapBase::Draw()
{
	//检测方块是否可用，可用再绘制
	if (m_life == alive)
	{   //在这里面写
		IMAGE block;
		int num = m_width / basewid;

		loadimage(&block, L".\\resources\\block3.png", basewid, m_height);
		for (int i = 1; i <= num; i++)
		{
			putimage(m_basepos.x + basewid * (i - 1), m_basepos.y , &block);
		}
		m_hbox.DrawHbox();
	}
	return DONE;
}
int Block::Update()
{
	if (m_life == dead)
	{
		Delete();
	}
	return DONE;
}
int Block::Delete()
{
	m_life = dead;
	return DONE;
}
HitBox Block::GetHBox()
{
	return m_hbox;
}



MovingBlock::MovingBlock(pos basepos, HitBox hbox, int speed, pos beginpos, pos endpos)
{
	m_life = alive;

	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_hbox = hbox;
	m_speed = speed;

	m_beginpos.x = beginpos.x;
	m_beginpos.y = beginpos.y;

	m_endpos.x = endpos.x;
	m_endpos.y = endpos.y;

	if (m_beginpos.x == m_endpos.x)
		m_totaldir = Ydir;
	else if (m_beginpos.y == m_endpos.y)
		m_totaldir = Xdir;
}
MovingBlock::~MovingBlock() {}
int MovingBlock::Paint()
{
	//
}
int MovingBlock::Move()
{
	if (m_basepos.x == m_beginpos.x && m_basepos.y == m_beginpos.y)
	{

	}
	else if (m_basepos.x == m_endpos.x && m_basepos.y == m_endpos.y)
	{

	}
	else
	{

	}
}



MapBase::MapBase()
{
	pos posground, posflyblock1, posflyblock2;
	HitBox hboxg, hboxf1, hboxf2;

	m_blocknum = 3;

	posground.x = 0;                            //三个方块的基础坐标（基础坐标就是方块的左下角坐标）
	posground.y = 654;                          //地板方块
	posflyblock1.x = 150;                       //浮空方块1
	posflyblock1.y = 300;
	posflyblock2.x = 900;                       //浮空方块2
	posflyblock2.y = 300;

	hboxg.Assignment(posground, 100, 1400);      //三个方块的碰撞箱，括号里的内容是（基础坐标，高度，宽度）
	hboxf1.Assignment(posflyblock1, 100, 300);
	hboxf2.Assignment(posflyblock2, 100, 300);


	Block groundblock(posground, hboxg, 1400);     //创建三个方块对应的Block对象，括号里参数分别为（贴图路径，基础坐标，碰撞箱，block总长度）
	Block Flyingblock(posflyblock1, hboxf1, 300);
	Block Flyingblock2(posflyblock2, hboxf2, 300);

	m_blocklist.push_back(groundblock);            //往MapBase类里的vector<Block>容器里插入元素
	m_blocklist.push_back(Flyingblock);
	m_blocklist.push_back(Flyingblock2);
}
MapBase::~MapBase() {};
int MapBase::Draw()
{
	//在这里写地图的绘制函数
	IMAGE p1, p2, p3, p4, p5, p6, p7, p8, p9;

	loadimage(&p1, L".\\resources\\p1.jpg", 448, 252);
	putimage(0, 0, &p1);

	loadimage(&p2, L".\\resources\\p2.jpg", 448, 252);
	putimage(448, 0, &p2);

	loadimage(&p3, L".\\resources\\p3.jpg", 448, 252);
	putimage(896, 0, &p3);

	loadimage(&p4, L".\\resources\\p4.jpg", 448, 252);
	putimage(0, 252, &p4);

	loadimage(&p5, L".\\resources\\p5.jpg", 448, 252);
	putimage(448, 252, &p5);

	loadimage(&p6, L".\\resources\\p6.jpg", 448, 252);
	putimage(896, 252, &p6);

	loadimage(&p7, L".\\resources\\p7.jpg", 448, 252);
	putimage(0, 504, &p7);

	loadimage(&p8, L".\\resources\\p8.jpg", 448, 252);
	putimage(448, 504, &p8);

	loadimage(&p9, L".\\resources\\p9.jpg", 448, 252);
	putimage(896, 504, &p9);

	for (vector<Block>::iterator it = m_blocklist.begin(); it != m_blocklist.end(); it++)
	{
		it->Draw();
	}
	return DONE;
}
int MapBase::GetBlockNum()
{
	return m_blocknum;
}
Block MapBase::GetBlock(int num)
{
	vector<Block>::iterator it = m_blocklist.begin();

	for (int i = 0; i < num; i++)
	{
		it++;
	}
	return *it;
}
int MapBase::Update()
{
	for (vector<Block>::iterator it = m_blocklist.begin(); it != m_blocklist.end(); it++)
	{
		it->Update();
		return DONE;
	}
}
