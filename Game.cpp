#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#include <vector>
#include <algorithm>
#include "Items.hpp"
#include "Players.hpp"
#include "Maps.hpp"


using namespace std;

vector<Bullet> p1Bulletlist;
vector<MagicBall> p1MagicBalllist;
vector<Sword> p1Swordlist;

vector<Bullet> p2Bulletlist;
vector<MagicBall> p2MagicBalllist;
vector<Sword> p2Swordlist;

vector<CureHeart> chlist;
vector<Shield> sdlist;
vector<SpeedShoes> sslist;

pc StartMenu()
{
	pc playerchoices;
	playerchoices.player1 = shooter;
	playerchoices.player2 = mage;




	return playerchoices;
}
void GameProgress(pc playerchoices,HWND hwnd)
{


	int x = 100, y = 100;
	int plength = 100, pwidth = 50;

	clock_t t1, t2,deltaT;
	t1 = clock();
	t2 = clock();

	pos p1basepos, p2basepos;
	pos p1shootpos, p2shootpos;
	pos testhbpos;

	//testhbpos.x = 600;
	//testhbpos.y = 600;

	//HitBox hbtest(testhbpos,100,100);

	p1basepos.x = 200;
	p1basepos.y = 655;
	
	p2basepos.x = 1100;
	p2basepos.y = 655;
	
	HitBox p1hbox(p1basepos,plength,pwidth), p2hbox(p2basepos, plength, pwidth);

	p1shootpos.x = p1basepos.x + 50;
	p1shootpos.y = p1basepos.y - 70;

	p2shootpos.x = p2basepos.x + 50;
	p2shootpos.y = p2basepos.y - 70;
	
	if (playerchoices.player1 == shooter && playerchoices.player2 == shooter)//1射2射
	{





















	}
	else if (playerchoices.player1 == shooter && playerchoices.player2 == mage)//1射2法
	{
		Shooter p1(p1basepos, p1hbox, p1shootpos,player1);
		Mage p2(p2basepos, p2hbox, p2shootpos,player2);
		MapBase map1;
		int i = 0;//循环计数器
		int quitflag = 0;
		int keya, keyw, keyd, keyj, keyleft, keyup, keyright, key1,keys;
		keya = keyw = keyd = keyj = keyleft = keyup = keyright = key1= keys =0;

		BeginBatchDraw();
		while (quitflag == 0)
		{
			while (i % 2 == 0) //偶循环
			{
				BeginBatchDraw();

				t2 = clock();
				deltaT = t2 - t1;
				//对象更新
				pos basepos;
				basepos.x = 0;
				basepos.y = 0;
				Bullet b = p1.Update(deltaT, map1);
				MagicBall a = p2.Update(deltaT, map1);
				if (b.m_life != dead)
					p1Bulletlist.push_back(b);
				if (a.m_life != dead)
					p2MagicBalllist.push_back(a);
				map1.Update();
				for (vector<Bullet>::iterator it = p1Bulletlist.begin(); it != p1Bulletlist.end(); it++)//各玩家伤害类更新
				{
					if (it->Update(p2.GetHitBox(), deltaT))
					{
						p2.CalDamage(it->m_damage);
					}
				}
				for (vector<MagicBall>::iterator it = p2MagicBalllist.begin(); it != p2MagicBalllist.end(); it++)
				{
					if (it->Update(p1.GetHitBox(), deltaT))
					{
						p1.CalDamage(it->m_damage);
					}
				}

				for (vector<CureHeart>::iterator it = chlist.begin(); it != chlist.end(); it++)// 物品更新
				{
					it->Update(p1.GetHitBox());
					it->Update(p2.GetHitBox());
				}
				for (vector<Shield>::iterator it = sdlist.begin(); it != sdlist.end(); it++)
				{
					it->Update(p1.GetHitBox());
					it->Update(p2.GetHitBox());
				}
				for (vector<SpeedShoes>::iterator it = sslist.begin(); it != sslist.end(); it++)
				{
					it->Update(p1.GetHitBox());
					it->Update(p2.GetHitBox());
				}

				for (vector<Bullet>::iterator it = p1Bulletlist.begin(); it != p1Bulletlist.end();)
				{

					if (it->m_life == dead)
					{
		
						p1Bulletlist.erase(it);
					}

					else
						it++;
				}
				for (vector<MagicBall>::iterator it = p2MagicBalllist.begin(); it != p2MagicBalllist.end(); it)
				{
					if (it->m_life == dead)
						p2MagicBalllist.erase(it);
					else
						it++;
				}


				//对象绘制
				map1.Draw();
				p1.Paint();
				p2.Paint();

				for (vector<Bullet>::iterator it = p1Bulletlist.begin(); it != p1Bulletlist.end(); it++)//各玩家伤害类绘制
				{
					it->Paint();
				}
				for (vector<MagicBall>::iterator it = p2MagicBalllist.begin(); it != p2MagicBalllist.end(); it++)
				{
					it->Paint();
				}

				for (vector<CureHeart>::iterator it = chlist.begin(); it != chlist.end(); it++)// 物品绘制
				{
					it->Paint();
				}
				for (vector<Shield>::iterator it = sdlist.begin(); it != sdlist.end(); it++)
				{
					it->Paint();
				}
				for (vector<SpeedShoes>::iterator it = sslist.begin(); it != sslist.end(); it++)
				{
					it->Paint();
				}


				//按键系统
							//玩家1
				if (KEY_DOWN(87) && p1.GetJumpLock() == 0 && keyw == 0)//87 - W
				{
					p1.Jump();
					//cout << 'w' << endl;
					keyw = 1;
				}
				else if (KEY_UP(87) && keyw == 1)
				{
					keyw = 0;
				}
				else if (KEY_DOWN(65))//65 - A
				{
					p1.BeginMoveleft();
					//cout << "a down" << endl;
					keya = 1;
				}
				else if (KEY_UP(65) && keya == 1)
				{
					p1.EndMoveleft();
					//cout << "a up" << endl;
					keya = 0;
				}
				else if (KEY_DOWN(68))//68 - D
				{
					p1.BeginMoveright();
					//cout << "d down" << endl;
					keyd = 1;
				}
				else if (KEY_UP(68) && keyd == 1)
				{
					p1.EndMoveright();
					//cout << "d up" << endl;
					keyd = 0;
				}
				else if (KEY_DOWN(74))//74 - J
				{
					p1.BeginAttack();
					//cout << "j" << endl;
					keyj = 1;
				}
				else if (KEY_UP(74) && keyj == 1)
				{
					p1.EndAttack();
					keyj = 0;
				}
				//玩家2
				if (KEY_DOWN(38) && p1.GetJumpLock() == 0 && keyup == 0)//38 - ↑
				{
					p2.Jump();
					//cout << "↑" << endl;
					keyup = 1;
				}
				else if (KEY_UP(38) && keyup == 1)
				{
					keyup = 0;
				}
				else if (KEY_DOWN(37))//37 - ←-
				{
					p2.BeginMoveleft();
					//cout << "← down" << endl;
					keyleft = 1;
				}
				else if (KEY_UP(37) && keyleft == 1)
				{
					p2.EndMoveleft();
					//cout << "← up" << endl;
					keyleft = 0;
				}
				else if (KEY_DOWN(39))//39 - -→
				{
					p2.BeginMoveright();
					//cout << "→ down" << endl;
					keyright = 1;
				}
				else if (KEY_UP(39) && keyright == 1)
				{
					p2.EndMoveright();
					//cout << "→ up" << endl;
					keyright = 0;
				}
				else if (KEY_DOWN(97))//97 - 小键盘1
				{
					p2.BeginAttack();
					//cout << '1' << endl;
					key1 = 1;
				}
				else if (KEY_UP(97) && key1 == 1)
				{
					p2.EndAttack();
					key1 = 0;
				}
				i++;
				if (i == MAXSIZE_INT)   //循环计数器保护机制
				{
					i = 1;
				}
				if (!(p1.GetLife() && p2.GetLife()))
				{
					quitflag = 1;
				}
				FlushBatchDraw();
			}
			EndBatchDraw();
			BeginBatchDraw();


			while (i % 2 == 1) //奇循环
			{
				BeginBatchDraw();

				t1 = clock();
				deltaT = t1 - t2;
				//对象更新
				pos basepos;
				basepos.x = 0;
				basepos.y = 0;
				Bullet b = p1.Update(deltaT, map1);
				MagicBall a = p2.Update(deltaT, map1);
				if (b.m_life != dead)
					p1Bulletlist.push_back(b);
				if (a.m_life != dead)
					p2MagicBalllist.push_back(a);
				map1.Update();
				for (vector<Bullet>::iterator it = p1Bulletlist.begin(); it != p1Bulletlist.end(); it++)//各玩家伤害类更新
				{
					if (it->Update(p2.GetHitBox(), deltaT))
					{
						p2.CalDamage(it->m_damage);
					}
				}
				for (vector<MagicBall>::iterator it = p2MagicBalllist.begin(); it != p2MagicBalllist.end(); it++)
				{
					if (it->Update(p1.GetHitBox(), deltaT))
					{
						p1.CalDamage(it->m_damage);
					}
				}

				for (vector<CureHeart>::iterator it = chlist.begin(); it != chlist.end(); it++)// 物品更新
				{
					it->Update(p1.GetHitBox());
					it->Update(p2.GetHitBox());
				}
				for (vector<Shield>::iterator it = sdlist.begin(); it != sdlist.end(); it++)
				{
					it->Update(p1.GetHitBox());
					it->Update(p2.GetHitBox());
				}
				for (vector<SpeedShoes>::iterator it = sslist.begin(); it != sslist.end(); it++)
				{
					it->Update(p1.GetHitBox());
					it->Update(p2.GetHitBox());
				}

				for (vector<Bullet>::iterator it = p1Bulletlist.begin(); it != p1Bulletlist.end();)
				{

					if (it->m_life == dead)
					{
						p1Bulletlist.erase(it);

			

					}

					else
						it++;
				}
				for (vector<MagicBall>::iterator it = p2MagicBalllist.begin(); it != p2MagicBalllist.end(); )
				{
					if (it->m_life == dead)
						p2MagicBalllist.erase(it);
					else
						it++;
				}

	
				//对象绘制
				map1.Draw();
				p1.Paint();
				p2.Paint();

				for (vector<Bullet>::iterator it = p1Bulletlist.begin(); it != p1Bulletlist.end(); it++)//各玩家伤害类绘制
				{
					it->Paint();
				}
				for (vector<MagicBall>::iterator it = p2MagicBalllist.begin(); it != p2MagicBalllist.end(); it++)
				{
					it->Paint();
				}

				for (vector<CureHeart>::iterator it = chlist.begin(); it != chlist.end(); it++)// 物品绘制
				{
					it->Paint();
				}
				for (vector<Shield>::iterator it = sdlist.begin(); it != sdlist.end(); it++)
				{
					it->Paint();
				}
				for (vector<SpeedShoes>::iterator it = sslist.begin(); it != sslist.end(); it++)
				{
					it->Paint();
				}


				//按键系统
				//玩家1
				if (KEY_DOWN(87) && p1.GetJumpLock() == 0 && keyw == 0)//87 - W
				{
					p1.Jump();
					//cout << 'w' << endl;
					keyw = 1;
				}
				else if (KEY_UP(87) && keyw == 1)
				{
					keyw = 0;
				}
				else if (KEY_DOWN(65))//65 - A
				{
					p1.BeginMoveleft();
					//cout << "a down" << endl;
					keya = 1;
				}
				else if (KEY_UP(65) && keya == 1)
				{
					p1.EndMoveleft();
					//cout << "a up" << endl;
					keya = 0;
				}
				else if (KEY_DOWN(68))//68 - D
				{
					p1.BeginMoveright();
					//cout << "d down" << endl;
					keyd = 1;
				}
				else if (KEY_UP(68) && keyd == 1)
				{
					p1.EndMoveright();
					//cout << "d up" << endl;
					keyd = 0;
				}
				else if (KEY_DOWN(74))//74 - J
				{
					p1.BeginAttack();
					//cout << "j" << endl;
					keyj = 1;
				}
				else if (KEY_UP(74) && keyj == 1)
				{
					p1.EndAttack();
					keyj = 0;
				}
				//玩家2
				if (KEY_DOWN(38) && p1.GetJumpLock() == 0 && keyup == 0)//38 - ↑
				{
					p2.Jump();
					//cout << "↑" << endl;
					keyup = 1;
				}
				else if (KEY_UP(38) && keyup == 1)
				{
					keyup = 0;
				}
				else if (KEY_DOWN(37))//37 - ←-
				{
					p2.BeginMoveleft();
					//cout << "← down" << endl;
					keyleft = 1;
				}
				else if (KEY_UP(37) && keyleft == 1)
				{
					p2.EndMoveleft();
					//cout << "← up" << endl;
					keyleft = 0;
				}
				else if (KEY_DOWN(39))//39 - -→
				{
					p2.BeginMoveright();
					//cout << "→ down" << endl;
					keyright = 1;
				}
				else if (KEY_UP(39) && keyright == 1)
				{
					p2.EndMoveright();
					//cout << "→ up" << endl;
					keyright = 0;
				}
				else if (KEY_DOWN(97))//97 - 小键盘1
				{
					p2.BeginAttack();
					//cout << '1' << endl;
					key1 = 1;
				}
				else if (KEY_UP(97) && key1 == 1)
				{
					p2.EndAttack();
					key1 = 0;
				}
				i++;
				if (i == MAXSIZE_INT)   //循环计数器保护机制
				{
					i = 0;
				}
				if (!(p1.GetLife() && p2.GetLife()))
				{
					quitflag = 1;
				}
;
				FlushBatchDraw();
			}
			EndBatchDraw();
		}
	}
	else if (playerchoices.player1 == shooter && playerchoices.player2 == worrior)//1射2战
	{


	}
	else if (playerchoices.player1 == mage && playerchoices.player2 == shooter)//1法2射
	{
	}
	else if (playerchoices.player1 == mage && playerchoices.player2 == mage)//1法2法
	{
;

	}
	else if (playerchoices.player1 == mage && playerchoices.player2 == worrior)//1法2战
	{

	}
	else if (playerchoices.player1 == worrior && playerchoices.player2 == shooter)//1战2射
	{

	}
	else if (playerchoices.player1 == worrior && playerchoices.player2 == mage)//1战2法
	{


	}
	else if (playerchoices.player1 == worrior && playerchoices.player2 == worrior)//1战2战
	{


	}




}
void EndProgress(HWND hwnd)
{
	MessageBox(hwnd, L"游戏结束！",L"提示", 1);
}
int main()
{
	pc playerchoices;
	HWND hwnd = initgraph(1344, 756);//1344 756
	playerchoices = StartMenu();
	GameProgress(playerchoices, hwnd);
	EndProgress(hwnd);
	return 0;
}