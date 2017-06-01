/** 
 * 太陽系を表示するプログラム
 * ===============================
 * File name : solar_system.c
 * Author    : Hayato Doi
 * License   : CC0
 * ===============================
 * -------------------------------
 * @myKeyboard() キーボードを制御する
 * -------------------------------
 * Copyright (c) 2017, Hayato Doi
 */

#include <stdlib.h>
#include <GL/glut.h>

typedef struct _planet_t planet_t;
struct _planet_t{
	//以下変数はすべて地球との比
	GLdouble size;			//サイズ
	GLdouble distance;		//公転半径(太陽とどれだけ離れているか)
	GLdouble period;		//公転周期(日)
	int rad_revolution;
};
static planet_t earth = {0.2,10,365};//地球のサイズ
planet_t planet[] = {
	{0.383, 0.38, 0.241,0},//水星
	{0.95, 0.72, 0.615,0},//金星
	{0.53, 1.52, 1.88,0},//火星
	{10.97, 5.20, 11.86,0},//木星
};

static int day = 0;
static int samplingTime = 50;//めっちゃ回せ!!

void myInit(){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1300, 700); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow("GuruGuru planet!");
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 1.0, 1.0);

	glPushMatrix();
		glutWireSphere(1.0, 20, 16);//太陽
		glRotated((double) earth.rad_revolution, 0.0, 1.0, 0.0);
		glTranslated(earth.distance, 0.0, 0.0);
		glRotated((double) day, 0.0, 1.0, 0.0);
		glutWireSphere(earth.size, 10, 8);//地球
		glPushMatrix();
			glTranslated(0.5, 0.0, 0.0);
			glRotated((double) day, 0.0, 1.0, 0.0);
			glutWireSphere(earth.size * 0.272, 10, 8);//月
		glPopMatrix();
	glPopMatrix();
	//惑星のカキカキ
	for(int i = 0; i < sizeof(planet); i++){
		glPushMatrix();
			glRotated((double) planet[i].rad_revolution, 0.0, 1.0, 0.0);
			glTranslated(earth.distance * planet[i].distance, 0.0, 0.0);		//中心からどれだけ離れているか。
			glRotated((double) day, 0.0, 1.0, 0.0);
			glutWireSphere(earth.size * planet[i].size, 10, 8);//惑星
		glPopMatrix();
	}
	/* glPushMatrix(); */
	/* 	glRotated((double) year, 0.0, 1.0, 0.0); */
	/* 	glTranslated(2.5, 0.0, 0.0);		//中心からどれだけ離れているか。 */
	/* 	glRotated((double) day, 0.0, 1.0, 0.0); */
	/* 	glutWireSphere(earth_size * 0.383, 10, 8);//水星 */
	/* glPopMatrix(); */
	/* glPushMatrix(); */
	/* 	glRotated((double) year, 0.0, 1.0, 0.0); */
	/* 	glTranslated(3.0, 0.0, 0.0);		//中心からどれだけ離れているか。 */
	/* 	glRotated((double) day, 0.0, 1.0, 0.0); */
	/* 	glutWireSphere(0.2, 10, 8);//地球 */
	/* glPopMatrix(); */
	glutSwapBuffers();
}

void myReshape(int width, int height){
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 5.0,	//カメラの位置
			0.0,0.0, 0.0,		//カメラが見つめている先の位置
			0.0, 1.0, 0.0);		//カメラの頭の方向を表すベクトル
}

void myKeyboard(unsigned char key, int x, int y){
	switch (key) {
		/* case 'd': */
		/* 	day = (day + 10) % 360; */
		/* 	glutPostRedisplay(); */
		/* 	break; */
		/* case 'D': */
		/* 	day = (day - 10) % 360; */
		/* 	glutPostRedisplay(); */
		/* 	break; */
		/* case 'y': */
		/* 	year = (year + 5) % 360; */
		/* 	glutPostRedisplay(); */
		/* 	break; */
		/* case 'Y': */
		/* 	year = (year - 5) % 360; */
		/* 	glutPostRedisplay(); */
		/* 	break; */
		/* case 263: */
		/* 	year = (year + 5) % 360; */
		/* 	glutPostRedisplay(); */
		/* 	break; */

		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void myTimer(int value){
	if (value==1){
		glutTimerFunc(samplingTime,myTimer,1);
		//公転
		earth.rad_revolution = (int)(earth.rad_revolution + ( (double) earth.period * 6 / 360)) % 360;
		for(int i = 0; i < sizeof(planet); i++){
			planet[i].rad_revolution = (int)(planet[i].rad_revolution + ( (double) planet[i].period * earth.period * 6 / 360)) % 360;
		}
		//自転
		day  = ( day + 5 ) % 360;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	myInit();
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(samplingTime, myTimer, 1);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay); 
	glutMainLoop();
	return 0;
}

