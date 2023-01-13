#pragma once
#include <time.h>
#include "Base.hpp"
#include "Maps.hpp"
#include "weapons.hpp"

class PlayerBase
{
protected:
	int m_life;
	int m_player;//用来判断血条位置
	int m_Health;
	int m_Shield;
	pos m_basepos;
	pos m_shootpos;
	int m_attackspeed;
	int m_faceori;
	HitBox m_hbox;
	double m_Xspeed;    //水平速度
	double m_Yspeed;    //垂直速度
	const int m_G;            //重力加速度
	double m_jumpspeed;
	direction m_dir;    //方向可行性参数  
	int m_jumplock;
	int m_Ismovingl;
	int m_Ismovingr;
	int m_Gunheight = 70;
	double m_attacktime = 0;
	int m_attackstate = END_FIRE;
	int m_pblock;

public:
	PlayerBase():m_Ismovingl(0),m_Ismovingr(0), m_pblock(0), m_G(1100), m_jumplock(0) {};
	PlayerBase( pos basepos, HitBox hbox, pos shootpos, int player,double xspeed = 10.000, double jumpspeed = 10, int attackspeed = 10,int health = 100, int shield = 0,int faceori = FACE_LEFT);
	~PlayerBase();
	virtual int Paint();                            //int 返回函数执行情况
	int CalDamage(int damage);      //返回值为检测到的碰撞箱个数
	int CalItemBuff(int type,int value);    //int 返回函数执行情况
	int BeginMoveleft();                         //int 返回函数执行情况
	int BeginMoveright();                        //int 返回函数执行情况
	int EndMoveleft();
	int EndMoveright();
	int CheckDirAccess(MapBase map);        //int 返回函数执行情况
	int Die();                              //int 返回函数执行情况
	int Jump();                             //int 返回函数执行情况
	int Update(clock_t deltaT,MapBase map);
	HitBox GetHitBox();
	int GetLife();
	int GetJumpLock();
	virtual void Updatepos(pos basepos);
	void Getmr();
};

class Shooter :public PlayerBase
{
protected:
	static string m_ID;

public:
	Shooter(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed = 10, double jumpspeed = 1000.0, int attackspeed = 9, int health = 100, int shield = 0, int faceori = FACE_LEFT);
	~Shooter();
	int Paint();
	int BeginAttack();
	int EndAttack();
	int PaintHealthBar();
	void Updatepos(pos basepos);
	Bullet Update(clock_t deltaT,MapBase map);
};

class Mage :public PlayerBase
{
protected:
	static string m_ID;

public:
	Mage(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed = 10, double jumpspeed = 1000.0, int attackspeed = 30,int health = 100, int shield = 0, int faceori = FACE_LEFT);
	~Mage();
	int Paint();
	int BeginAttack();
	int EndAttack();
	int PaintHealthBar();
	void Updatepos(pos basepos);
	MagicBall Update(clock_t deltaT, MapBase map);
};

class Worrior :public PlayerBase
{
protected:
	static string m_ID;

public:
	Worrior();
	Worrior(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed = 25, double jumpspeed = 1000.0, int attackspeed = 33, int health = 100, int shield = 0, int faceori = FACE_LEFT);
	~Worrior();
	int Paint();
	int BeginAttack();
	int EndAttack();
	int PaintHealthBar();
	void Updatepos(pos basepos);
	int GetFace();
	Sword Update(clock_t deltaT, MapBase map);
	pos GetShootpos();
};

PlayerBase::PlayerBase(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed, double jumpspeed, int attackspeed, int health, int shield, int faceori) :m_G(50), m_jumplock(0)
{
	m_dir.right = accessable;
	m_dir.left = accessable;
	m_dir.up = accessable;
	m_dir.down = accessable;
	m_player = player;

	m_Xspeed = xspeed;
	m_attackspeed = attackspeed;
	m_life = alive;
	m_jumplock = 0;
	m_Ismovingl = 0;
	m_Ismovingr = 0;

	m_Health = health;
	m_Shield = shield;

	m_shootpos.x = shootpos.x;
	m_shootpos.y = shootpos.y;

	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_faceori = faceori;
	m_hbox = hbox;

	m_jumpspeed = jumpspeed;
}
PlayerBase::~PlayerBase() {}
int PlayerBase::Paint()
{
	//待定
	//IMAGE img1,img2;
	//loadimage(&img1, L"shooter_l1.png", 50, 100);
	//loadimage(&img2, L"shooter_l2.png", 50, 100);
	//putimage(m_basepos.x, m_basepos.y, &img1, SRCAND);
	//putimage(m_basepos.x, m_basepos.y, &img2, SRCPAINT);

 //   return DONE;
	return 0;
}
int PlayerBase::CalDamage(int damage)
{   
	if (damage - m_Shield < 0)
		m_Shield = 0;
	else if (damage - m_Shield > 0 && (m_Health - (damage - m_Shield)) >= 0)
		m_Health -= (damage - m_Shield);
	else if (damage - m_Shield > 0 && (m_Health - (damage - m_Shield)) < 0)
	{
		m_Health = 0;
		Die();
	}
	return DONE;
}
int PlayerBase::CalItemBuff(int type, int value)
{
	switch (type)
	{
	case heal:
		if (m_Health + value <= 100)
			m_Health += value;
		else if (m_Health + value > 100)
			m_Health = 100;
		break;

	case shield:
		m_Shield += value;
		break;
	case speedup:               //若为减速，则需传入负数
	case speeddown:
		m_Xspeed += value;
		break;
	}
	return DONE;
}
int PlayerBase::CheckDirAccess(MapBase map)
{
	int bnum = map.GetBlockNum();
	int flag = 1;
	pos ULpos, URpos, DRpos, DLpos;
	//地图边框检测，无须检测下边框，因为地图必定有底层block即ground
	//上检测
	if (m_hbox.GetPoint(upleft).y > 0)  //边框检测
	{
		for (int i = 0; i < bnum; i++)
		{
			if (LBHit(m_hbox.GetLine(upline), map.GetBlock(i).GetHBox()))
			{
				m_dir.up = unaccess;
				flag = 0;
				//PullBack(map.GetBlock(i).GetHBox().GetLine(downline),downline);
			}
		}
		if (flag == 1)
		{
			//if (m_dir.up == unaccess)
			//	m_pblock = 0;
			m_dir.up = accessable;

		}
	}
	else
		m_dir.up = unaccess;
	flag = 1;
	//下检测
	if (m_hbox.GetPoint(downleft).y < 600)
	{
		for (int i = 1; i < bnum; i++)  //从 1 开始，用边框代替地板检测
		{

			if (LBHit(m_hbox.GetLine(downline), map.GetBlock(i).GetHBox()))
			{
				m_dir.down = unaccess;
				flag = 0;
				//PullBack(map.GetBlock(i).GetHBox().GetLine(upline), upline);
			}
		}
		if (flag == 1)
		{
			//if (m_dir.down == unaccess)
			//	m_pblock = 0;
			m_dir.down = accessable;
		}

	}
	else
		m_dir.down = unaccess;
	flag = 1;
	//左检测
	if (m_hbox.GetPoint(upleft).x > 0)   //边框检测
	{
		for (int i = 0; i < bnum; i++)                              //地图方块检测
		{

			if (LBHit(m_hbox.GetLine(leftline), map.GetBlock(i).GetHBox()))
			{ 
				m_dir.left = unaccess;
				//cout << "第" << i+1 << "个" << endl;
				flag = 0;
				//PullBack(map.GetBlock(i).GetHBox().GetLine(rightline), rightline);
			}
			if (CheckLineHit(m_hbox.GetLine(upline), map.GetBlock(i).GetHBox().GetLine(rightline)))
			{
				m_dir.right = unaccess;
				flag = 0;
			}
			if (CheckLineHit(m_hbox.GetLine(downline), map.GetBlock(i).GetHBox().GetLine(rightline)))
			{
				m_dir.right = unaccess;
				flag = 0;
			}
		}
		if (flag == 1)
		{
			//if (m_dir.left == unaccess)
			//	m_pblock = 0;
			m_dir.left = accessable;
		}

	}
	else
		m_dir.left = unaccess;
	flag = 1;
	//右检测
	if (m_hbox.GetPoint(upright).x < 1344)   //边框检测
	{
		for (int i = 0; i < bnum; i++)                              //地图方块检测
		{

			if (LBHit(m_hbox.GetLine(rightline), map.GetBlock(i).GetHBox()))
			{
				m_dir.right = unaccess;
				flag = 0;
				//PullBack(map.GetBlock(i).GetHBox().GetLine(leftline), leftline);
			}
			if (CheckLineHit(m_hbox.GetLine(upline), map.GetBlock(i).GetHBox().GetLine(leftline)))
			{
				m_dir.right = unaccess;
				flag = 0;
			}
			if (CheckLineHit(m_hbox.GetLine(downline), map.GetBlock(i).GetHBox().GetLine(leftline)))
			{
				m_dir.right = unaccess;
				flag = 0;
			}
		}
		if (flag == 1)
		{
			//if (m_dir.right == unaccess)
			//	m_pblock = 0;
			m_dir.right = accessable;
		}

	}
	else
		m_dir.right = unaccess;
	flag = 1;

	return DONE;
}
int PlayerBase::BeginMoveleft()
{
	if (m_dir.left == accessable)
		m_Ismovingl = 1;
	m_faceori = FACE_LEFT;
	return DONE;
}
int PlayerBase::BeginMoveright()
{
	if (m_dir.right == accessable)
		m_Ismovingr = 1;
	m_faceori = FACE_RIGHT;
	return DONE;
}
int PlayerBase::EndMoveleft()
{
	m_Ismovingl = 0;
	return DONE;
}
int PlayerBase::EndMoveright()
{
	m_Ismovingr = 0;
	return DONE;
}
int PlayerBase::Jump()
{
	if (m_jumplock == 0 && m_dir.up == accessable)
	{
		m_Yspeed = -1 * m_jumpspeed;
		m_jumplock = 1;
	}
	return DONE;
}
int PlayerBase::Die()
{
	m_life = dead;
	return DONE;
}
int PlayerBase::Update(clock_t deltaT, MapBase map)
{
	//CheckDirAccess(map);
	//m_hbox.Updatepos(m_basepos);
	//if (m_Health <= 0)
	//	Die();
	////第一步：移动/坐标更新
	//	//上下移动/坐标更新
	//if (m_dir.up == accessable)
	//{
	//	if (m_dir.down == accessable)
	//	{
	//		m_Yspeed += (0 * deltaT) / 1000;
	//		m_basepos.y += m_Yspeed * deltaT / 1000;
	//	}
	//	else if (m_dir.down == unaccess)
	//	{
	//		if (m_Yspeed >= 0)
	//		{
	//			m_Yspeed = 0;
	//		}
	//		else if (m_Yspeed < 0)
	//		{
	//			m_Yspeed += (0 * deltaT) / 1000;
	//			m_basepos.y += m_Yspeed * deltaT / 1000;
	//		}
	//	}
	//}
	//else if (m_dir.down == accessable && m_dir.up == unaccess)
	//{
	//	if (m_Yspeed <= 0)
	//	{
	//		m_Yspeed = 0;
	//	}
	//	else if (m_Yspeed > 0)
	//	{
	//		m_Yspeed += (0 * deltaT) / 1000;
	//		m_basepos.y += m_Yspeed * deltaT / 1000;
	//	}
	//}
	////左右移动/坐标更新
	//if (m_dir.left == accessable && m_Ismovingl == 1)
	//{
	//	m_basepos.x -= (m_Xspeed * (double)deltaT) / 50;
	//}
	//if (m_dir.right == accessable && m_Ismovingr == 1)
	//{
	//	m_basepos.x += (m_Xspeed * (double)deltaT) / 50;
	//}
	//if (m_dir.up == accessable && m_Ismovingup == 1)
	//{
	//	m_basepos.y += (m_Xspeed * (double)deltaT) / 50;
	//}

	return DONE;
}
HitBox PlayerBase::GetHitBox()
{
	return m_hbox;
}
int PlayerBase::GetLife()
{
	return m_life;
}
int PlayerBase::GetJumpLock()
{
	return m_jumplock;
}
void PlayerBase::Updatepos(pos basepos)
{
	m_shootpos = basepos;
}
void PlayerBase::Getmr()
{
	cout << m_Ismovingr << endl;
}



string Shooter::m_ID = "Shooter";
Shooter::Shooter(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed, double jumpspeed, int attackspeed, int health, int shield, int faceori)
{
	m_dir.right = accessable;
	m_dir.left = accessable;
	m_dir.up = accessable;
	m_dir.down = accessable;
	m_player = player;

	m_life = alive;
	m_jumplock = 0;
	m_Ismovingl = 0;
	m_Ismovingr = 0;
	cout <<  ' ' << endl;
	cout << ' ' << endl;


	m_Xspeed = xspeed;
	m_attackspeed = attackspeed;

	m_Health = health;
	m_Shield = shield;

	m_shootpos.x = shootpos.x;
	m_shootpos.y = shootpos.y;

	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_faceori = faceori;
	m_hbox = hbox;

	m_Xspeed = xspeed;
	m_jumpspeed = jumpspeed;

	m_jumplock = 0;
}
Shooter::~Shooter() {}
int Shooter::Paint()
{
	//坐标四舍五入机制
	int x, y;
	if (10 * (m_hbox.GetPoint(upleft).x - (int)m_hbox.GetPoint(upleft).x) >= 5)
		x = (int)m_hbox.GetPoint(upleft).x + 1;
	else
		x = (int)m_hbox.GetPoint(upleft).x;
	if (10 * (m_hbox.GetPoint(upleft).y - (int)m_hbox.GetPoint(upleft).y) >= 5)
		y = (int)m_hbox.GetPoint(upleft).y + 1;
	else
		y = (int)m_hbox.GetPoint(upleft).y;
	PaintHealthBar();

	if (m_life == alive)
	{
		if (m_faceori == FACE_LEFT)
		{
			IMAGE img1, img2;
			loadimage(&img1, L".\\resources\\shooter_l1.png", 50, 100);
			loadimage(&img2, L".\\resources\\shooter_l2.png", 50, 100);
			putimage(x, y  , &img1, SRCAND);
			putimage(x, y  , &img2, SRCPAINT);
		}
		else if (m_faceori == FACE_RIGHT)
		{
			IMAGE img1, img2;
			loadimage(&img1, L".\\resources\\shooter_r1.png", 50, 100);
			loadimage(&img2, L".\\resources\\shooter_r2.png", 50, 100);
			putimage(x, y , &img1, SRCAND);
			putimage(x, y , &img2, SRCPAINT);
		}

		return DONE;
	}
}
int Shooter::BeginAttack()
{
	m_attackstate = BEGIN_FIRE;

	return DONE;
}
int Shooter::EndAttack()
{
	m_attacktime = 0;
	m_attackstate = END_FIRE;

	return DONE;
}
void Shooter::Updatepos(pos basepos)
{
	m_shootpos.x = basepos.x;
	m_shootpos.y = basepos.y - m_Gunheight;
}
Bullet Shooter::Update(clock_t deltaT, MapBase map)
{
	if (m_life == alive)
	{
		CheckDirAccess(map);
		m_hbox.Updatepos(m_basepos);
		Updatepos(m_basepos);
		if (m_Health <= 0)
			Die();
		//落地检测，jumplock置零
		if (GetJumpLock() == 1 && m_Yspeed > 0 && m_dir.down == unaccess)
			m_jumplock = 0;
		//第一步：移动/坐标更新
			//上下移动/坐标更新
		if (m_dir.up == accessable)
		{
			if (m_dir.down == accessable)
			{
				m_Yspeed += (m_G * deltaT) / (double)1000;
				m_basepos.y += m_Yspeed * deltaT / (double)1000;
			}
			else if (m_dir.down == unaccess)
			{
				if (m_Yspeed >= 0)
				{
					m_Yspeed = 0;
				}
				else if (m_Yspeed <= 0)
				{
					m_Yspeed += (m_G * deltaT) / (double)1000;
					m_basepos.y += m_Yspeed * deltaT / (double)1000;
				}
			}
		}
		else if (m_dir.down == accessable && m_dir.up == unaccess)
		{
			if (m_Yspeed < 0)
			{
				m_Yspeed = 0;
			}
			else if (m_Yspeed >= 0)
			{
				m_Yspeed += (m_G * deltaT) / (double)1000;
				m_basepos.y += m_Yspeed * deltaT / (double)1000;
			}
		}

		//左右移动/坐标更新
		if (m_dir.left == accessable && m_Ismovingl == 1)
		{
			m_basepos.x -= (m_Xspeed * (double)deltaT) / 50;
		}
		if (m_dir.right == accessable && m_Ismovingr == 1)
		{
			m_basepos.x += (m_Xspeed * (double)deltaT) / 50;
		}
		//攻击更新
		if (m_attackstate == BEGIN_FIRE)
		{

			m_attacktime += 3;//suppose every loop add 3
			int attacktime = m_attacktime;
			if (attacktime % m_attackspeed == 0)
			{
				Bullet* b = new Bullet(m_shootpos, m_faceori);
				return *b;
			}

		}
	}
		Bullet* a = new Bullet(m_shootpos, m_faceori, dead);//无效子弹
		return *a;
	
}
int Shooter::PaintHealthBar()
{
	IMAGE backimg1, backimg2,  bar;

	if (m_player == player1)
	{
		loadimage(&backimg1, L".\\resources\\hbback_shooter_l1.png", 575, 100);


		loadimage(&backimg2, L".\\resources\\hbback_shooter_l2.png", 575, 100);

		putimage(20, 20, &backimg2, SRCAND);
		putimage(20, 20, &backimg1, SRCPAINT);

		if (m_Health >= 60)
		{
			loadimage(&bar, L".\\resources\\Ghealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(188 + (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 60 && m_Health >= 30)
		{
			loadimage(&bar, L".\\resources\\Yhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(188 + (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 30)
		{
			loadimage(&bar, L".\\resources\\Rhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(188 + (double)i * 4, 37.5, &bar);
			}
		}

	}
	else if (m_player == player2)
	{
		loadimage(&backimg1, L".\\resources\\hbback_shooter_r1.png", 570, 100);
		loadimage(&backimg2, L".\\resources\\hbback_shooter_r2.png", 570, 100);

		putimage(765, 20, &backimg2, SRCAND);
		putimage(765, 20, &backimg1, SRCPAINT);

		if (m_Health >= 60)
		{
			loadimage(&bar, L".\\resources\\Ghealthbar.png", 4, 51);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1168 - (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 60 && m_Health >= 30)
		{
			loadimage(&bar, L".\\resources\\Yhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1168 - (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 30)
		{
			loadimage(&bar, L".\\resources\\Rhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1168 - (double)i * 4, 37.5, &bar);
			}
		}
	}
	return DONE;

}



string Mage::m_ID = "Mage";
Mage::Mage(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed, double jumpspeed, int attackspeed, int health, int shield, int faceori)
{
	m_dir.right = accessable;
	m_dir.left = accessable;
	m_dir.up = accessable;
	m_dir.down = accessable;
	m_player = player;

	m_life = alive;
	m_jumplock = 0;
	m_Ismovingl = 0;
	m_Ismovingr = 0;
	cout << ' ' << endl;
	cout << ' ' << endl;

	m_Xspeed = xspeed;
	m_attackspeed = attackspeed;

	m_Health = health;
	m_Shield = shield;

	m_shootpos.x = shootpos.x;
	m_shootpos.y = shootpos.y;

	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_faceori = faceori;

	m_hbox = hbox;

	m_Xspeed = xspeed;
	m_jumpspeed = jumpspeed;
	m_jumplock = 0;
}
Mage::~Mage() {}
int Mage::Paint()
{
	//坐标四舍五入机制
	int x, y;
	if (10 * (m_hbox.GetPoint(upleft).x - (int)m_hbox.GetPoint(upleft).x) >= 5)
		x = (int)m_hbox.GetPoint(upleft).x + 1;
	else
		x = (int)m_hbox.GetPoint(upleft).x;
	if (10 * (m_hbox.GetPoint(upleft).y - (int)m_hbox.GetPoint(upleft).y) >= 5)
		y = (int)m_hbox.GetPoint(upleft).y + 1;
	else
		y = (int)m_hbox.GetPoint(upleft).y;

	if (m_life == alive)
	{
		if (m_faceori == FACE_LEFT)
		{
			IMAGE img1, img2;
			loadimage(&img1, L".\\resources\\wizard_l1.png", 50, 100);
			loadimage(&img2, L".\\resources\\wizard_l2.png", 50, 100);
			putimage(x, y , &img1, SRCAND);
			putimage(x, y , &img2, SRCPAINT);
		}
		else if (m_faceori == FACE_RIGHT)
		{
			IMAGE img1, img2;
			loadimage(&img1, L".\\resources\\wizard_r1.png", 50, 100);
			loadimage(&img2, L".\\resources\\wizard_r2.png", 50, 100);
			putimage(x, y , &img1, SRCAND);
			putimage(x, y, &img2, SRCPAINT);
		}
		PaintHealthBar();
		return DONE;
	}
	PaintHealthBar();
	return DONE;
}
int Mage::BeginAttack()
{
	m_attackstate = BEGIN_FIRE;

	return DONE;
}
int Mage::EndAttack()
{
	m_attackstate = END_FIRE;
	m_attacktime = 0;

	return DONE;
}
MagicBall Mage::Update(clock_t deltaT, MapBase map)
{
	if (m_life == alive)
	{
		CheckDirAccess(map);
		m_hbox.Updatepos(m_basepos);
		Updatepos(m_basepos);
		if (m_Health <= 0)
			Die();
		//落地检测，jumplock置零
		if (GetJumpLock() == 1 && m_Yspeed > 0 && m_dir.down == unaccess)
			m_jumplock = 0;
		//第一步：移动/坐标更新
			//上下移动/坐标更新
		if (m_dir.up == accessable)
		{
			if (m_dir.down == accessable)
			{
				m_Yspeed += (m_G * deltaT) / (double)1000;
				m_basepos.y += m_Yspeed * deltaT / (double)1000;
			}
			else if (m_dir.down == unaccess)
			{
				if (m_Yspeed >= 0)
				{
					m_Yspeed = 0;
				}
				else if (m_Yspeed <= 0)
				{
					m_Yspeed += (m_G * deltaT) / (double)1000;
					m_basepos.y += m_Yspeed * deltaT / (double)1000;
				}
			}
		}
		else if (m_dir.down == accessable && m_dir.up == unaccess)
		{
			if (m_Yspeed < 0)
			{
				m_Yspeed = 0;
			}
			else if (m_Yspeed >= 0)
			{
				m_Yspeed += (m_G * deltaT) / (double)1000;
				m_basepos.y += m_Yspeed * deltaT / (double)1000;
			}
		}

		//左右移动/坐标更新
		if (m_dir.left == accessable && m_Ismovingl == 1)
		{
			m_basepos.x -= (m_Xspeed * (double)deltaT) / 50;
		}
		if (m_dir.right == accessable && m_Ismovingr == 1)
		{
			m_basepos.x += (m_Xspeed * (double)deltaT) / 50;
		}

		//攻击更新
		if (m_attackstate == BEGIN_FIRE)
		{
			m_attacktime += 3;//suppose every loop add 3
			int attacktime = m_attacktime;
			if (attacktime % m_attackspeed == 0)
			{
				MagicBall* b = new MagicBall(m_shootpos, m_faceori);
				return *b;
			}

		}
	}
		MagicBall* a = new MagicBall(m_shootpos, m_faceori, dead);//无效法球
		return *a;
	

}
int Mage::PaintHealthBar()
{
	IMAGE backimg1, backimg2, bar;

	if (m_player == player1)
	{
		loadimage(&backimg1, L".\\resources\\hbback_mage_l1.png", 560, 100);
		loadimage(&backimg2, L".\\resources\\hbback_mage_l2.png", 560, 100);

		putimage(20, 20, &backimg2, SRCAND);
		putimage(20, 20, &backimg1, SRCPAINT);

		if (m_Health >= 60)
		{
			loadimage(&bar, L".\\resources\\Ghealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(171 + (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 60 && m_Health >= 30)
		{
			loadimage(&bar, L".\\resources\\Yhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(171 + (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 30)
		{
			loadimage(&bar, L".\\resources\\Rhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(171 + (double)i * 4, 37.5, &bar);
			}
		}
	}
	else if (m_player == player2)
	{
		loadimage(&backimg1, L".\\resources\\hbback_mage_r1.png", 560, 100);
		loadimage(&backimg2, L".\\resources\\hbback_mage_r2.png", 560, 100);

		putimage(765, 20, &backimg2, SRCAND);
		putimage(765, 20, &backimg1, SRCPAINT);

		if (m_Health >= 60)
		{
			loadimage(&bar, L".\\resources\\Ghealthbar.png",4, 51);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1172 - (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 60 && m_Health >= 30)
		{
			loadimage(&bar, L".\\resources\\Yhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1172 - (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 30)
		{
			loadimage(&bar, L".\\resources\\Rhealthbar.png",4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1172 - (double)i * 4, 37.5, &bar);
			}
		}
	}
	return DONE;
}
void Mage::Updatepos(pos basepos)
{
	m_shootpos.x = basepos.x;
	m_shootpos.y = basepos.y - m_Gunheight;
}


string Worrior::m_ID = "Worrior";
Worrior::Worrior(pos basepos, HitBox hbox, pos shootpos, int player, double xspeed, double jumpspeed, int attackspeed, int health, int shield, int faceori)
{
	m_dir.right = accessable;
	m_dir.left = accessable;
	m_dir.up = accessable;
	m_dir.down = accessable;
	m_player = player;

	m_life = alive;
	m_jumplock = 0;
	m_Ismovingl = 0;
	m_Ismovingr = 0;

	m_attackspeed = attackspeed;

	m_Health = health;
	m_Shield = shield;

	m_shootpos.x = shootpos.x;
	m_shootpos.y = shootpos.y;

	m_basepos.x = basepos.x;
	m_basepos.y = basepos.y;

	m_faceori = faceori;
	m_hbox = hbox;


	m_Xspeed = xspeed;
	m_jumpspeed = jumpspeed;
	m_jumplock = 0;
}
Worrior::~Worrior() {}
int Worrior::Paint()
{
	//坐标四舍五入机制
	int x, y;
	if (10 * (m_basepos.x - (int)m_basepos.x) >= 5)
		x = (int)m_basepos.x + 1;
	else
		x = (int)m_basepos.x;
	if (10 * (m_basepos.y - (int)m_basepos.y) >= 5)
		y = (int)m_basepos.y + 1;
	else
		y = (int)m_basepos.y;

	if (m_life == alive)
	{
		if (m_faceori == FACE_LEFT)
		{
			IMAGE img1, img2;
			loadimage(&img1, L".\\resources\\soldier_l1.png", 50, 100);
			loadimage(&img2, L".\\resources\\soldier_l2.png", 50, 100);
			putimage(x, y - 100, &img1, SRCAND);
			putimage(x, y - 100, &img2, SRCPAINT);
		}
		else if (m_faceori == FACE_RIGHT)
		{
			IMAGE img1, img2;
			loadimage(&img1, L".\\resources\\soldier_r1.png", 50, 100);
			loadimage(&img2, L".\\resources\\soldier_r2.png", 50, 100);
			putimage(x, y - 100, &img1, SRCAND);
			putimage(x, y - 100, &img2, SRCPAINT);
		}
		PaintHealthBar();
		return DONE;
	}
	PaintHealthBar();
}
int Worrior::BeginAttack()
{
	m_attackstate = BEGIN_FIRE;

	return DONE;
}
int Worrior::EndAttack()
{
	m_attackstate = END_FIRE;
	m_attacktime = 0;

	return DONE;
}
int Worrior::PaintHealthBar()
{
	IMAGE backimg1, backimg2, bar;
	if (m_player == player1)
	{
		loadimage(&backimg1, L".\\resources\\hbback_worrior_l1.png", 575, 100);
		loadimage(&backimg2, L".\\resources\\hbback_worrior_l2.png", 575, 100);

		putimage(20, 20, &backimg2, SRCAND);
		putimage(20, 20, &backimg1, SRCPAINT);

		if (m_Health >= 60)
		{
			loadimage(&bar, L".\\resources\\Ghealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(186 + (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 60 && m_Health >= 30)
		{
			loadimage(&bar, L".\\resources\\Yhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(186 + (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 30)
		{
			loadimage(&bar, L".\\resources\\Rhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(186 + (double)i * 4, 37.5, &bar);
			}
		}
	}
	else if (m_player == player2)
	{
		loadimage(&backimg1, L".\\resources\\hbback_worrior_r1.png", 575, 100);
		loadimage(&backimg2, L".\\resources\\hbback_worrior_r2.png", 575, 100);

		putimage(765, 20, &backimg2, SRCAND);
		putimage(765, 20, &backimg1, SRCPAINT);

		if (m_Health >= 60)
		{
			loadimage(&bar, L".\\resources\\Ghealthbar.png", 4, 51);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1172 - (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 60 && m_Health >= 30)
		{
			loadimage(&bar, L".\\resources\\Yhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1172 - (double)i * 4, 37.5, &bar);
			}
		}
		else if (m_Health < 30)
		{
			loadimage(&bar, L".\\resources\\Rhealthbar.png", 4, 52);
			for (int i = 0; i < m_Health; i++)
			{
				putimage(1172 - (double)i * 4, 37.5, &bar);
			}
		}
		
	}
	return DONE;
}
Sword Worrior::Update(clock_t deltaT, MapBase map)
{
	CheckDirAccess(map);
	m_hbox.Updatepos(m_basepos);
	Updatepos(m_basepos);
	if (m_Health <= 0)
		Die();
	//落地检测，jumplock置零
	if (GetJumpLock() == 1 && m_Yspeed > 0 && m_dir.down == unaccess)
		m_jumplock = 0;
	//第一步：移动/坐标更新
	//上下移动/坐标更新
	if (m_dir.up == accessable)
	{
		if (m_dir.down == accessable)
		{
			m_Yspeed += (m_G * deltaT) / (double)1000;
			m_basepos.y += m_Yspeed * deltaT / (double)1000;
		}
		else if (m_dir.down == unaccess)
		{
			if (m_Yspeed >= 0)
			{
				m_Yspeed = 0;
			}
			else if (m_Yspeed <= 0)
			{
				m_Yspeed += (m_G * deltaT) / (double)1000;
				m_basepos.y += m_Yspeed * deltaT / (double)1000;
			}
		}
	}
	else if (m_dir.down == accessable && m_dir.up == unaccess)
	{
		if (m_Yspeed < 0)
		{
			m_Yspeed = 0;
		}
		else if (m_Yspeed >= 0)
		{
			m_Yspeed += (m_G * deltaT) / (double)1000;
			m_basepos.y += m_Yspeed * deltaT / (double)1000;
		}
	}

	//左右移动/坐标更新
	if (m_dir.left == accessable && m_Ismovingl == 1)
	{
		m_basepos.x -= (m_Xspeed * (double)deltaT) / 50;
	}
	if (m_dir.right == accessable && m_Ismovingr == 1)
	{
		m_basepos.x += (m_Xspeed * (double)deltaT) / 50;
	}

	//攻击更新
	if (m_attackstate == BEGIN_FIRE)
	{
		//cout << "attime = " << m_attacktime << endl;
		//cout << "atspeed = " << m_attackspeed << endl;
		m_attacktime += 3;
		int attacktime = m_attacktime;
		if (attacktime % m_attackspeed == 0)
		{
			Sword *b = new Sword(m_shootpos, m_faceori);
			return *b;
		}

	}

	Sword *a = new Sword(m_shootpos, m_faceori, dead);//无效剑气
	return *a;

}
void Worrior::Updatepos(pos basepos)
{
	m_shootpos.x = basepos.x;
	m_shootpos.y = basepos.y - m_Gunheight;
}
int Worrior::GetFace()
{
	return m_faceori;
}
pos Worrior::GetShootpos()
{
	return m_shootpos;
}