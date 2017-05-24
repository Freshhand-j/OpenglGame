#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include "SceneController.h"
#include "FPSCamera.h"

#define Sensitivity 0.002

FPSCamera* cam;

static int mouseLastPosX = 0;
static int mouseLastPosY = 0;

GLuint texture[4];

void drawScene() {
	//�ذ�  
	glPushMatrix();
	glTranslatef(0.0f, -1.0f*roomSizeY / 2.0f, 0.0f);
	glRotatef(90, 1, 0, 0);

	glScalef(roomSizeX, roomSizeZ, 1);
	drawRect(texture[3]);
	glPopMatrix();

	//�컨��     
	glPushMatrix();
	glTranslatef(0.0f, 1.0f*roomSizeY / 2.0f, 0.0f);
	glRotatef(270, 1, 0, 0);

	glScalef(roomSizeX, roomSizeZ, 1);
	drawRect(texture[0]);
	glPopMatrix();

	//ǽ�ڣ�ǰ��  
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -1.0f*roomSizeZ / 2.0);
	glRotatef(180, 1, 0, 0);
	glRotatef(180, 0, 0, 1);

	glScalef(roomSizeX, roomSizeY, 1);
	drawRect(texture[1]);
	glPopMatrix();

	//ǽ�ڣ���  
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.0f*roomSizeZ / 2.0f);
	glScalef(roomSizeX, roomSizeY, 1);

	drawRect(texture[1]);
	glPopMatrix();

	//ǽ�ڣ���  
	glPushMatrix();
	glTranslatef(-1.0f*roomSizeX / 2.0f, 0.0f, 0.0f);
	glRotatef(270, 0, 1, 0);

	glScalef(roomSizeZ, roomSizeY, 1);
	drawRect(texture[1]);
	glPopMatrix();

	//ǽ�ڣ��ң�  
	glPushMatrix();
	glTranslatef(1.0f*roomSizeX / 2.0f, 0.0f, 0.0f);
	glRotatef(90, 0, 1, 0);

	glScalef(roomSizeZ, roomSizeY, 1);
	drawRect(texture[1]);
	glPopMatrix();

	//�м�ǽ��  
	glPushMatrix();
	glScalef(40, 15, 40);
	drawCube(texture[1]);
	glPopMatrix();

	//����  
	glPushMatrix();
	glTranslatef(-1.0f*roomSizeX / 2.0f + 2.5f, -1.0f*roomSizeY / 2.0f + 2.5f, -1.0f*roomSizeZ / 2.0f + 2.5f);
	glScalef(5, 5, 5);
	drawCube(texture[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f*roomSizeX / 2.0f + 2.5f, -1.0f*roomSizeY / 2.0f + 7.5f, -1.0f*roomSizeZ / 2.0f + 2.5f);
	glScalef(5, 5, 5);
	drawCube(texture[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f*roomSizeX / 2.0f + 7.5f, -1.0f*roomSizeY / 2.0f + 2.5f, -1.0f*roomSizeZ / 2.0f + 2.5f);
	glScalef(5, 5, 5);
	drawCube(texture[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f*roomSizeX / 2.0f + 2.5f, -1.0f*roomSizeY / 2.0f + 2.5f, -1.0f*roomSizeZ / 2.0f + 7.5f);
	glScalef(5, 5, 5);
	drawCube(texture[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30.f, -1.0f*roomSizeY / 2.0f + 2.5f, 0);
	glScalef(5, 5, 5);
	drawCube(texture[2]);
	glPopMatrix();

	cam->detectCameraMove();

}

void reshape(int width, int height) {
	if (height == 0) {     //����߶�Ϊ0 
		height = 1;        //�ø߶�Ϊ1��������ַ�ĸΪ0������      
	}

	cam->resetWinSize(width, height);    
}

void idle() {
	glutPostRedisplay();
}

void init() {
	glEnable(GL_DEPTH_TEST);//������Ȳ���        
	glEnable(GL_LIGHTING);  //��������ģʽ   
	glGenTextures(3, texture);
	loadTex(0, "textures/1.bmp", texture);
	loadTex(1, "textures/16.bmp", texture);
	loadTex(2, "textures/14.bmp", texture);
	loadTex(3, "textures/11.bmp", texture);
}

void normalKeyPress(unsigned char key, int x, int y) {
	cam->keyPressed(key);
}

void normalKeyUp(unsigned char key, int x, int y) {
	cam->keyUp(key);
}

//���յ��ʱ
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseLastPosX = x;
		mouseLastPosY = y;
	}
}

//��������ƶ�ʱ
void mouseMove(int x, int y) {
	//����������Ծ���
	float pitch = (float)(y - mouseLastPosY) * Sensitivity;
	float yaw = (float)(x - mouseLastPosX) * Sensitivity;
	mouseLastPosY = y;
	mouseLastPosX = x;
	cam->rotate(pitch, yaw);
}

void redraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ���   
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	// ���ù��ռ���  
	glEnable(GL_LIGHTING);
	// ָ��������ǿ�ȣ�RGBA��  
	GLfloat ambientLight[] = { 2.0f, 2.0f, 2.0f, 1.0f };

	// ���ù���ģ�ͣ���ambientLight��ָ����RGBAǿ��ֵӦ�õ�������  
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	// ������ɫ׷��  
	glEnable(GL_COLOR_MATERIAL);
	// ���ö��������Ļ������ɢ���������ԣ�׷��glColor  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	drawScene();//���Ƴ���   
	glutSwapBuffers();//����������  
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	int windowHandle = glutCreateWindow("Final project!");

	cam = new FPSCamera();
	//�����ײ��Ե
	cam->setSceneOuterBoundary(-roomSizeX / 2, -roomSizeZ / 2, roomSizeX / 2, roomSizeZ / 2);
	cam->setSceneInnerBoundary(-20, -20, 20, 20);
	cam->setSceneInnerBoundary(-50, -45, -45, -40);
	cam->setSceneInnerBoundary(-45, -50, -40, -45);

	cam->setSceneInnerBoundaryMap(-32.5f, -1.0f*roomSizeY / 2.0f, -2.5f, 
		-27.5f, -1.0f*roomSizeY / 2.0f + 5.f, 2.5f);

	glutDisplayFunc(redraw);               //ע����ƻص�����
	glutReshapeFunc(reshape);              //ע���ػ�ص�����
	glutKeyboardFunc(normalKeyPress);    //ע����ͨ�����ص�����
	glutKeyboardUpFunc(normalKeyUp);
	glutMouseFunc(mouseClick);             //ע��������ص�����
	glutMotionFunc(mouseMove);             //ע�������&�ƶ��ص�����
	glutIdleFunc(idle);                    //ע��ȫ�ֻص�����������ʱ����       

	init();
	glutMainLoop();                        // glut�¼�����ѭ��    

	delete cam;

	return 0;
}