#pragma once
#include <stdio.h>
#include <iostream> 
#include <easyx.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include "Base.hpp"
#pragma comment(lib,"winmm.lib")
using namespace std;

pc switch_job()
{
	IMAGE job1, job2, shooter, warrior, wizard, bk;
	IMAGE bsho, bwar, bwiz;//大图标
	IMAGE charap1, charap2, chara11, chara12, chara21, chara22,charam1,charam2;
	IMAGE arrow1, arrow2;
	IMAGE csho1, cwar1, cwiz1,csho2,cwar2,cwiz2;//选择后显示

	int p1 = 0, p2 = 0;
	pc choice;
	MOUSEMSG msg = { 0 };
	loadimage(&job1, L".\\resources\\switchjob1.png", 1344, 756);
	loadimage(&job2, L".\\resources\\switchjob2.png", 1344, 756);
	loadimage(&shooter, L".\\resources\\switchshooter.png", 165, 90);
	loadimage(&warrior, L".\\resources\\switchwarrior.png", 165, 90);
	loadimage(&wizard, L".\\resources\\switchwizard.png", 165, 90);
	loadimage(&bk, L".\\resources\\bk.png", 1700, 960);

	loadimage(&bsho, L".\\resources\\bigshooter.png", 220, 119);
	loadimage(&bwar, L".\\resources\\bigwarrior.png", 220, 119);
	loadimage(&bwiz, L".\\resources\\bigwizard.png", 220, 119);

	loadimage(&charap1, L".\\resources\\chara_p1.png", 134, 115);//p
	loadimage(&charap2, L".\\resources\\chara_p2.png", 134, 115);
	loadimage(&chara11, L".\\resources\\chara_11.png", 121, 115);//1
	loadimage(&chara12, L".\\resources\\chara_12.png", 121, 115);
	loadimage(&chara21, L".\\resources\\chara_21.png", 125, 121);//2
	loadimage(&chara22, L".\\resources\\chara_22.png", 125, 121);
	loadimage(&charam1, L".\\resources\\chara_m1.png", 125, 121);//:
	loadimage(&charam2, L".\\resources\\chara_m2.png", 125, 121);

	loadimage(&arrow1, L".\\resources\\arrow1.png", 125, 121);//↓
	loadimage(&arrow2, L".\\resources\\arrow2.png", 125, 121);

	loadimage(&csho1, L".\\resources\\csho1.png", 332, 141);//shooter
	loadimage(&csho2, L".\\resources\\csho2.png", 332, 141);
	loadimage(&cwar1, L".\\resources\\cwar1.png", 332, 141);//warrior
	loadimage(&cwar2, L".\\resources\\cwar2.png", 332, 141);
	loadimage(&cwiz1, L".\\resources\\cwiz1.png", 332, 141);//wizard
	loadimage(&cwiz2, L".\\resources\\cwiz2.png", 332, 141);


	BeginBatchDraw();
	while (1)
	{
		msg = GetMouseMsg();

		putimage(-230, -220, &bk);

		putimage(0, 0, &job2, SRCAND);
		putimage(0, 0, &job1, SRCPAINT);

		putimage(150, 504, &wizard);
		putimage(600, 504, &warrior);
		putimage(1050, 504, &shooter);

		putimage(70, 150, &charap2, SRCAND);
		putimage(70, 150, &charap1, SRCPAINT);
		putimage(170, 150, &chara12, SRCAND);
		putimage(170, 150, &chara11, SRCPAINT);
		putimage(260, 160, &charam2, SRCAND);
		putimage(260, 160, &charam1, SRCPAINT);

		putimage(750, 150, &charap2, SRCAND);
		putimage(750, 150, &charap1, SRCPAINT);
		putimage(850, 150, &chara22, SRCAND);
		putimage(850, 150, &chara21, SRCPAINT);
		putimage(930, 160, &charam2, SRCAND);
		putimage(930, 160, &charam1, SRCPAINT);

		if (p1 == 0)
		{
			putimage(170, 30, &arrow2, SRCAND);
			putimage(170, 30, &arrow1, SRCPAINT);
		}
		if (p1 != 0 && p2 == 0)
		{
			putimage(880, 30, &arrow2, SRCAND);
			putimage(880, 30, &arrow1, SRCPAINT);
		}


		if (msg.x >= 150 && msg.x <= 315 && msg.y >= 504 && msg.y <= 594)//图标变大
		{
			putimage(122, 493, &bwiz);
		}
		if (msg.x >= 600 && msg.x <= 765 && msg.y >= 504 && msg.y <= 594)//图标变大
		{
			putimage(572, 493, &bwar);
		}
		if (msg.x >= 1050 && msg.x <= 1215 && msg.y >= 504 && msg.y <= 594)//图标变大
		{
			putimage(1022, 493, &bsho);
		}

		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (msg.x >= 150 && msg.x <= 315 && msg.y >= 504 && msg.y <= 594)//法师
			{
				if (p1 == 0)
				{
					p1 = 1;
				}
				else if (p1 != 0 && p2 == 0)
				{
					p2 = 1;
				}
			}
			if (msg.x >= 600 && msg.x <= 765 && msg.y >= 504 && msg.y <= 594)//战士
			{
				if (p1 == 0)
				{
					p1 = 2;
				}
				else if (p1 != 0 && p2 == 0)
				{
					p2 = 2;
				}
			}
			if (msg.x >= 1050 && msg.x <= 1215 && msg.y >= 504 && msg.y <= 594)//射手
			{
				if (p1 == 0)
				{
					p1 = 3;
				}
				else if (p1 != 0 && p2 == 0)
				{
					p2 = 3;
				}
			}
		}

		if (p1 == 1)
		{
			putimage(330, 130, &cwiz2, SRCAND);
			putimage(330, 130, &cwiz1, SRCPAINT);
		}
		else if (p1 == 2)
		{
			putimage(330, 150, &cwar2, SRCAND);
			putimage(330, 150, &cwar1, SRCPAINT);
		}
		else if (p1 == 3)
		{
			putimage(330, 150, &csho2, SRCAND);
			putimage(330, 150, &csho1, SRCPAINT);
		}

		if (p2 == 1)
		{
			putimage(1000, 130, &cwiz2, SRCAND);
			putimage(1000, 130, &cwiz1, SRCPAINT);
		}
		else if (p2 == 2)
		{
			putimage(1000, 150, &cwar2, SRCAND);
			putimage(1000, 150, &cwar1, SRCPAINT);
		}
		else if (p2 == 3)
		{
			putimage(1000, 150, &csho2, SRCAND);
			putimage(1000, 150, &csho1, SRCPAINT);
		}

        if (p1 != 0 && p2 != 0)
            break;
		FlushBatchDraw();
	}
	EndBatchDraw();
	Sleep(1000);//作用为调控选择完成后的时间长短
	
	choice.player1 = p1;
	choice.player2 = p2;

	return choice;
}

pc draw_start(HWND hwnd) //绘制开始界面
{
	mciSendString(L"open .\\resources\\bgm.mp3 alias BGM", 0, 0, 0);//bgm加载语句，根据情况选择
	IMAGE start, title1, title2;

	MOUSEMSG msg = { 0 };

	loadimage(&start,L".\\resources\\mainstart.png", 1344, 756);

	mciSendString(L"play BGM repeat", 0, 0, 0);//bgm播放语句，根据情况选择
	mciSendString(L"setaudio BGM volume to 100", 0, 0, 0);
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, &start);

		settextcolor(RGB(153,217,234));
		settextstyle(80, 0, L"微软雅黑");
		setbkmode(TRANSPARENT);
		outtextxy(470, 550, L"请按任意键继续");

		settextcolor(WHITE);
		settextstyle(40, 0, L"微软雅黑");
		setbkmode(TRANSPARENT);
		outtextxy(30, 700, L"Version: 1.0");

		loadimage(&title1, L".\\resources\\title1.png", 1000, 91);
		loadimage(&title2, L".\\resources\\title2.png", 1000, 91);
		putimage(180, 100, &title1, SRCAND);
		putimage(180, 100, &title2, SRCPAINT);

		msg = GetMouseMsg();

		FlushBatchDraw();
		
	        switch (msg.uMsg)
	        {
	        case WM_LBUTTONDOWN:
			{
				return switch_job();
				break;
			}
	        }
	}
	EndBatchDraw();
	
}

