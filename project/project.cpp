// project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

//


#include <iostream>
#include "glut.h"//opengl头文件
#pragma comment(lib,"glut32.lib")//opengl库

#include <windows.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//纹理
GLuint tex_floor;
GLuint tex_picture;
GLuint tex_wall;
GLuint tex_wallside;
GLuint tex_walltop;

//视角控制
float Camera_angle = 0;

//图元绘制指针
GLUquadricObj *quadobj;


//门开关
float door_angle = 0;
bool door_open = false;

//漫游数据
double view[3] = { 0,0,30 };
double look[3] = { 2,2,2 };
float eye_direction[3] = { 0, 0, 1 };

//茶壶状态，1表示平方，其他表示倒茶
int teaPotType = 1;

//椅子高度
float chairHeight = 3;

//光照亮度
float lightPercent = 0.5;

//定义了各种颜色
enum Color
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURSE,
	LIGHTRED,
	GRAY,
	BLACK,
	WHITE
};

//红色的
GLfloat red_ambient[] = { 0.2f, 0.0f, 0.0f }; //环境光
GLfloat red_diffuse[] = { 0.5f, 0.0f, 0.0f }; //扩散光
GLfloat red_specular[] = { 0.7f, 0.6f, 0.6f }; //境面光
GLfloat red_shininess[] = { 32.0f };			//  反射强度

//绿色
GLfloat green_ambient[] = { 0.0f, 0.2f, 0.0f };
GLfloat green_diffuse[] = { 0.0f, 0.5f, 0.0f };
GLfloat green_specular[] = { 0.6f, 0.7f, 0.6f };
GLfloat green_shininess[] = { 32.0f };

//蓝色
GLfloat blue_ambient[] = { 0.0f, 0.0f, 0.2f };
GLfloat blue_diffuse[] = { 0.0f, 0.0f, 0.5f };
GLfloat blue_specular[] = { 0.6f, 0.6f, 0.7f };
GLfloat blue_shininess[] = { 32.0f };

//黄色
GLfloat yellow_ambient[] = { 0.3f, 0.3f, 0.0f };
GLfloat yellow_diffuse[] = { 0.3f, 0.3f, 0.0f };
GLfloat yellow_specular[] = { 0.7f, 0.7f, 0.5f };
GLfloat yellow_shininess[] = { 32.0f };


//紫色
GLfloat purse_ambient[] = { 0.3f, 0.0f, 0.4f }; //环境光
GLfloat purse_diffuse[] = { 0.2f, 0.0f, 0.3f }; //扩散光
GLfloat purse_specular[] = { 0.7f, 0.6f, 0.6f }; //境面光
GLfloat purse_shininess[] = { 50.0f };			//  反射强度


//玫红
GLfloat lightRed_ambient[] = { 0.4f, 0.0f, 0.2f }; //环境光
GLfloat lightRed_diffuse[] = { 0.1f, 0.1f, 0.1f }; //扩散光
GLfloat lightRed_specular[] = { 0.7f, 0.6f, 0.6f }; //境面光
GLfloat lightRed_shininess[] = { 10.0f };			//  反射强度


//灰色
GLfloat grey_ambient[] = { 0.3f, 0.3f, 0.3f };
GLfloat grey_diffuse[] = { 0.3f, 0.3f, 0.3f };
GLfloat grey_specular[] = { 0.7f, 0.7f, 0.5f };
GLfloat grey_shininess[] = { 32.0f };

//黑色
GLfloat black_ambient[] = { 0.0f, 0.0f, 0.0f };
GLfloat black_diffuse[] = { 0.3f, 0.3f, 0.3f };
GLfloat black_specular[] = { 0.2f, 0.2f, 0.2f };
GLfloat black_shininess[] = { 32.0f };


//白色
GLfloat white_ambient[] = { 0.8f, 0.8f, 0.8f };
GLfloat white_diffuse[] = { 0.8f, 0.8f, 0.8f };
GLfloat white_specular[] = { 0.0f, 0.0f, 0.0f };
GLfloat white_shininess[] = { 32.0f };



//设置颜色
void setColor(Color C)
{
	switch (C)
	{
	case RED:
		glMaterialfv(GL_FRONT, GL_AMBIENT, red_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, red_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, red_shininess);
		break;
	case GREEN:
		glMaterialfv(GL_FRONT, GL_AMBIENT, green_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, green_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, green_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, green_shininess);
		break;
	case BLUE:
		glMaterialfv(GL_FRONT, GL_AMBIENT, blue_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blue_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, blue_shininess);
		break;
	case YELLOW:
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellow_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellow_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, yellow_shininess);
		break;
	case GRAY:
		glMaterialfv(GL_FRONT, GL_AMBIENT, grey_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, grey_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, grey_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, grey_shininess);
		break;
	case LIGHTRED:
		glMaterialfv(GL_FRONT, GL_AMBIENT, lightRed_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, lightRed_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, lightRed_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, lightRed_shininess);
		break;
	case PURSE:
		glMaterialfv(GL_FRONT, GL_AMBIENT, purse_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, purse_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, purse_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, purse_shininess);
		break;
	case BLACK:
		glMaterialfv(GL_FRONT, GL_AMBIENT, black_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, black_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, black_shininess);
		break;
	case WHITE:
		glMaterialfv(GL_FRONT, GL_AMBIENT, white_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, white_shininess);
		break;
	default:
		break;
	};
}


//--------------自定义函数---------------------------------------//
//加载纹理图片
unsigned  char *ReadBitmapFile(const char *path, int &width, int &height)
{
	unsigned char *imagedate = NULL;
	FILE *pFile = fopen(path, "rb");
	if (pFile)
	{
		BITMAPFILEHEADER bfh;
		fread(&bfh, sizeof(BITMAPFILEHEADER), 1, pFile);
		if (bfh.bfType = 0x4d42)
		{
			BITMAPINFOHEADER bih;
			fread(&bih, sizeof(BITMAPINFOHEADER), 1, pFile);
			width = bih.biWidth;
			height = bih.biHeight;
			imagedate = new unsigned char[width*height * 3];
			fseek(pFile, bfh.bfOffBits, SEEK_SET);

			fread(imagedate, 1, width*height * 3, pFile);
			fclose(pFile);
		}
	}
	return  imagedate;
}

//读入图片后进行设置纹理绑定
bool  SetTexture(const char *filename, GLuint &texture)	//加载位图文件 方法1
{
	int imageWidth, imageHeight;
	unsigned char * imageDate = ReadBitmapFile(filename, imageWidth, imageHeight);
	glGenTextures(1, &texture); //生成贴图
	glBindTexture(GL_TEXTURE_2D, texture); //贴图生效
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //缩小时线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //扩大时线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imageDate);
	return true;
}

//加载纹理
void LoadTexture()
{

	SetTexture("floor.bmp", tex_floor);//加载第一个图
	SetTexture("wall.bmp", tex_wall);//加载第一个图
	SetTexture("wallside.bmp", tex_wallside);//加载第一个图
	SetTexture("walltop.bmp", tex_walltop);//加载第一个图
	SetTexture("picture.bmp", tex_picture);//加载第一个图
}

//绘制挂画，加上纹理贴图
void DrawPicture()
{
	setColor(BLUE);

	glPushMatrix();
	glTranslatef(14.9, 3.0, 0.0);
	glScalef(0.1, 6.0, 8.0);
	glutSolidCube(1);
	glPopMatrix();


	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);   //texture
	glBindTexture(GL_TEXTURE_2D, tex_picture);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(14.75f, 0.0f, 4.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(14.75f, 0.0f, -4.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(14.75f, 6.0f, -4.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(14.75f, 6.0f, 4.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

//绘制沙发，用两个长方体
void DrawSofa()
{
	//设置表面颜色和材质

	setColor(RED);

	glPushMatrix();

	glPushMatrix();
	glScalef(10.0, 5.0, 1.8);
	glutSolidCube(1);
	glPopMatrix();

	setColor(LIGHTRED);
	glPushMatrix();
	glTranslatef(0.0, -1.8f, 1.8f);
	glScalef(10.1, 2.5, 5.0);
	glutSolidCube(1);
	glPopMatrix();


	setColor(BLUE);
	glPushMatrix();
	glTranslatef(-4.5, -3, 2.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadobj, 0.2, 0.2, 1.0, 20, 20);
	glPopMatrix();

	setColor(BLUE);
	glPushMatrix();
	glTranslatef(4.5, -3, 2.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadobj, 0.2, 0.2, 1.0, 20, 20);
	glPopMatrix();

	setColor(BLUE);
	glPushMatrix();
	glTranslatef(-4.5, -3, -1.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadobj, 0.2, 0.2, 1.0, 20, 20);
	glPopMatrix();

	setColor(BLUE);
	glPushMatrix();
	glTranslatef(4.5, -3, -1.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadobj, 0.2, 0.2, 1.0, 20, 20);
	glPopMatrix();



	glPopMatrix();
}



//绘制桌子，用的是长方体，通过几何变换
void DrawDesk()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, yellow_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, yellow_shininess);

	glPushMatrix();

	glPushMatrix();
	glScalef(2.5, 0.1, 2.5);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();

	glTranslatef(1.0f, -0.5f, -1.0);
	glScalef(0.1, 1.0, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-1.0f, -0.5f, 1.0);
	glScalef(0.1, 1.0, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f, -0.5f, -1.0);
	glScalef(0.1, 1.0, 0.1);

	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0f, -0.5f, 1.0);
	glScalef(0.1, 1.0, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

}


//升降椅子，用的是一个球体加上一个圆锥体
void DrawChair(float height)
{
	setColor(BLUE);
	glPushMatrix();
	glTranslatef(0.0, -3 + height, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 0.4f, 0.8f, height, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glScalef(1.0, 0.3, 1.0);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();
}


//绘制墙面，用的是长方体，加上纹理
void DrawWall()
{
	setColor(WHITE);

	glEnable(GL_TEXTURE_2D);   //texture
	glBindTexture(GL_TEXTURE_2D, tex_wall);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, -10.0f, -14.2f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0f, -10.0f, -14.2f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15.0f, 10.0f, -14.2f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 10.0f, -14.2f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);   //texture
	glBindTexture(GL_TEXTURE_2D, tex_floor);

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, -9.9f, -15.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0f, -9.9f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15.0f, -9.9f, 15.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, -9.9f, 15.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);   //texture
	glBindTexture(GL_TEXTURE_2D, tex_walltop);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 9.9f, -15.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0f, 9.9f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-15.0f, 9.9f, 15.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 9.9f, 15.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	setColor(GRAY);

	//背景墙
	glPushMatrix();
	glTranslatef(0.0, 0.0, -15.0);

	glScalef(30, 20, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	//天花板
	glPushMatrix();
	glTranslatef(0, 10.0, 0.0);
	glScalef(30, 0.1, 30);
	glutSolidCube(1);
	glPopMatrix();


	//底板
	glPushMatrix();
	glTranslatef(0, -10.0, 0.0);
	glScalef(30, 0.1, 30);
	glutSolidCube(1);
	glPopMatrix();

	//右侧墙板
	glPushMatrix();
	glTranslatef(15, 0.0, 0.0);
	glScalef(0.1, 20, 30);
	glutSolidCube(1);
	glPopMatrix();

	//左侧墙板
	glPushMatrix();
	glTranslatef(-15, 0.0, 10.0);
	glScalef(0.1, 20, 10);
	glutSolidCube(1);
	glPopMatrix();


	//左侧墙板
	glPushMatrix();
	glTranslatef(-15, 6.0, 2.0);
	glScalef(0.1, 12, 12);
	glutSolidCube(1);
	glPopMatrix();


	//左侧墙板
	glPushMatrix();
	glTranslatef(-15, -5.0, -5.5);
	glScalef(0.1, 10, 10);
	glutSolidCube(1);
	glPopMatrix();



	//左侧墙板
	glPushMatrix();
	glTranslatef(-15, 8.0, 0);
	glScalef(0.1, 4, 30);
	glutSolidCube(1);
	glPopMatrix();





	//左侧墙板
	glPushMatrix();
	glTranslatef(-15, 0.0, -12.5);
	glScalef(0.1, 20, 5);
	glutSolidCube(1);
	glPopMatrix();


	//绘制门
	setColor(BLUE);

	glPushMatrix();
	glTranslatef(-14.9, -5.0, 0);

	glRotatef(door_angle, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, 2.75);
	glScalef(0.1, 10.5, 6.0);
	glutSolidCube(1);
	glPopMatrix();

	setColor(RED);
	glPushMatrix();
	glTranslatef(0.15, 0, 4.5);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	glPopMatrix();
}

//绘制灯泡
void DrawLightBlob()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, lightRed_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lightRed_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightRed_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, lightRed_shininess);

	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.0f, 0.f);
	glScalef(0.3, 3.0, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	setColor(BLUE);
	glPushMatrix();
	glTranslatef(0.f, -2.0f, 0.f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quadobj, 1.5, 0.3, 1.2, 30, 30);
	glPopMatrix();


	setColor(WHITE);
	glPushMatrix();
	glTranslatef(0, -2.3, 0);
	gluSphere(quadobj, 0.6, 30, 30);
	glPopMatrix();


	glPopMatrix();
}

//绘制茶壶和茶杯
void DrawTeaPot(int type)
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, red_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, red_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, red_shininess);

	glPushMatrix();
	glTranslatef(5.f, -5.0f, 0.f);



	glPushMatrix();

	if (type == 1)
	{
		glTranslatef(2.f, -.3f, 3.f);
		glutSolidTeapot(1.0);
	}
	else
	{

		glTranslatef(0.5, 2.0f, 1.f);
		glRotatef(-45, 0, 0, 1);
		glutSolidTeapot(1.0);
	}


	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, green_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, green_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, green_shininess);
	glPushMatrix();
	glTranslatef(2, -0.5, 1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quadobj, 0.6, 0.8, 1.2, 20, 20);

	glPopMatrix();
	glPopMatrix();
}
//绘制电脑
void DrawComputer()
{
	setColor(BLACK);

	glPushMatrix();
	glScalef(1.4, 1.0, 0.2);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1.3, -0.1);
	setColor(RED);
	glScalef(0.5, 0.7, 0.2);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, -1.6, -0.1);
	setColor(BLUE);
	glScalef(1.0, 0.2, 1.0);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, -1.6, 1.5);
	setColor(GRAY);
	glScalef(2.0, 0.2, 1.0);
	glutSolidCube(1);
	glPopMatrix();


}
void Setlight()
{
	//设置光照
	GLfloat model_ambient[] = { 1.9f, 1.9f,1.9f, 1.0f };//后面的值是默认值
	GLfloat light_position0[] = { 1.0f, 10.0f, 10.0f, 0.0f };
	GLfloat light_color0[] = { lightPercent, lightPercent, lightPercent, lightPercent };

	//环境光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	//光源位置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);//零号光

	//光源颜色
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color0);

	//打开光源
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

//初始化
void init() {

	glEnable(GL_NORMALIZE);
	quadobj = gluNewQuadric();

	LoadTexture();

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//设置背景颜色
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glEnable(GL_NORMALIZE);
}

//绘图函数
void display()
{
	glLoadIdentity();
	Setlight();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//设置视角，可以通过左右键控制
	//gluLookAt(25.0 * sin(Camera_angle), 0.0f, 30.0 * cos(Camera_angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(view[0], view[1], view[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
	//主要绘图函数
	glPushMatrix();
	glTranslatef(0, 0, 2.6f);
	DrawTeaPot(teaPotType);
	glPopMatrix();

	DrawWall();
	DrawPicture();

	//绘制灯泡
	glPushMatrix();
	glTranslatef(0.f, 7.0f, 0.f);
	DrawLightBlob();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(8, -6, 0);
	glScalef(3, 4.5, 7.5);
	DrawDesk();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9, -2, -2);
	glRotatef(-70, 0, 1, 0);
	glScalef(1.5, 2.0, 2.0);
	DrawComputer();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -6, -10);
	DrawSofa();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(3, -8, 1);
	glScalef(1.6, 0.8, 1.6);
	DrawChair(chairHeight);
	glPopMatrix();
	//绘制模型
	glPopMatrix();
	glutSwapBuffers();
}

//窗口缩放后的处理
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

//空闲响应
void myIdle()
{
	if (door_open)
	{
		if (door_angle < 180)
			door_angle += 0.5;
	}
	else
	{
		if (door_angle > 0)
			door_angle -= 0.5;
	}
	glutPostRedisplay();
}
//一般按键响应
//1234控制风扇速度，asdfzx分别控制其他，可以自己尝试
void keyboard(unsigned char key, int x, int y) //键盘事件 
{
	switch (key)
	{

	case 'A':
	case 'a':
		view[0] -= 0.1;
		look[0] = view[0] + eye_direction[0] * 100;
		look[1] = view[1] + eye_direction[1] * 100;
		look[2] = view[2] - eye_direction[2] * 10;
		break;
	case 'S':
	case 's':
		view[2] += 0.1;
		look[0] = view[0] + eye_direction[0] * 100;
		look[1] = view[1] + eye_direction[1] * 100;
		look[2] = view[2] - eye_direction[2] * 10;
		break;
	case 'W':
	case 'w':
		view[2] -= 0.1;
		look[0] = view[0] + eye_direction[0] * 100;
		look[1] = view[1] + eye_direction[1] * 100;
		look[2] = view[2] - eye_direction[2] * 10;
		break;
	case 'D':
	case 'd':
		view[0] += 0.1;
		look[0] = view[0] + eye_direction[0] * 100;
		look[1] = view[1] + eye_direction[1] * 100;
		look[2] = view[2] - eye_direction[2] * 10;
		break;

	case 'z':
	case 'Z':
		teaPotType = 0;
		break;
	case 'x':
	case 'X':
		teaPotType = 1;
		break;

	case 'c':
	case 'C':
		chairHeight += 0.1;
		break;
	case 'v':
	case 'V':
		chairHeight -= 0.1;
		break;

	case 'B':
	case 'b':
		door_open = !door_open;
		break;
	default:
		break;;
	}

	glutPostRedisplay();
}
//计算眼睛朝向
void cal_direction()
{
	eye_direction[0] = sin(Camera_angle);
	eye_direction[1] = 0;
	eye_direction[2] = cos(Camera_angle);
}
//特殊按键响应，上下控制灯光亮暗。左右控制视角
void SpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (lightPercent < 0.8)
			lightPercent += 0.1;
		break;
	case GLUT_KEY_DOWN:
		lightPercent -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		Camera_angle -= 0.003;
		cal_direction();
		look[0] = view[0] + eye_direction[0] * 100;
		look[1] = view[1] + eye_direction[1] * 100;
		look[2] = view[2] - eye_direction[2] * 10;
		break;
	case GLUT_KEY_RIGHT:
		Camera_angle += 0.003;
		cal_direction();
		look[0] = view[0] + eye_direction[0] * 100;
		look[1] = view[1] + eye_direction[1] * 100;
		look[2] = view[2] - eye_direction[2] * 10;
		break;

	default:
		break;
	}
}

//主程序，opengl的都是这样的
int main(int argc, char* argv[])
{
	/* Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	/* Create a window with title specified */
	glutInitWindowSize(640, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MyOffice");
	init();
	glutDisplayFunc(display);//绘图回调
	glutReshapeFunc(reshape);//窗口缩放回调
	glutKeyboardFunc(keyboard);  // 键盘事件
	glutSpecialFunc(SpecialKeys);
	glutIdleFunc(myIdle);//空闲时间回调
	glutMainLoop();//循环
	return 0;
}