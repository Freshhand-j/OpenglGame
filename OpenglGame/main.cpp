#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include "SceneController.h"

#define Sensitivity 0.003

FPSCamera* cam;

static int mouseLastPosX = 0;
static int mouseLastPosY = 0;

GLuint texture[10];

void drawScene() {
	//��պ�
	drawSkybox(texture);

	//�ذ�  
	glPushMatrix();
	glTranslatef(0.0f, -roomSizeY / 2.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glScalef(roomSizeX, roomSizeZ, 1);
	drawRect(texture[3]);
	glPopMatrix();

	//����  
	drawBoxColliders(texture);

	cam->updateCameraMovement();
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

void initLightingAndTexture() {
	glEnable(GL_DEPTH_TEST);//������Ȳ���        
	glEnable(GL_LIGHTING);  //��������ģʽ   
	glGenTextures(10, texture);
	loadTex(0, "textures/1.bmp", texture);
	loadTex(1, "textures/16.bmp", texture);
	loadTex(2, "textures/14.bmp", texture);
	loadTex(3, "textures/11.bmp", texture);

	loadTex(4, "textures/Skybox/Sunny_up.bmp", texture);
	loadTex(5, "textures/Skybox/Sunny_down.bmp", texture);
	loadTex(6, "textures/Skybox/Sunny_left.bmp", texture);
	loadTex(7, "textures/Skybox/Sunny_right.bmp", texture);
	loadTex(8, "textures/Skybox/Sunny_front.bmp", texture);
	loadTex(9, "textures/Skybox/Sunny_back.bmp", texture);
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

void initializeGL() {
	cam = new FPSCamera();
	//�����ײ��Ե
	cam->setSceneOuterBoundary(-roomSizeX / 2.0, -roomSizeZ / 2.0, roomSizeX / 2.0, roomSizeZ / 2.0);

	cam->setSceneInnerBoundary(-roomSizeX / 2.0,  -roomSizeY / 2.0f - 1.f, -roomSizeZ / 2.0,
		roomSizeX / 2.0, -roomSizeY / 2.0f, roomSizeZ / 2.0);    //�ذ�collider

	initBoxCollidersProperty();
	setBoxColliderBoundary(cam);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(250, 100);
	glutInitWindowSize(600, 600);
	int windowHandle = glutCreateWindow("Final project!");

	initializeGL();

	glutDisplayFunc(redraw);               //ע����ƻص�����
	glutReshapeFunc(reshape);              //ע���ػ�ص�����
	glutKeyboardFunc(normalKeyPress);    //ע����ͨ�����ص�����
	glutKeyboardUpFunc(normalKeyUp);
	glutMouseFunc(mouseClick);             //ע��������ص�����
	glutMotionFunc(mouseMove);             //ע�������&�ƶ��ص�����
	glutIdleFunc(idle);                    //ע��ȫ�ֻص�����������ʱ����       

	initLightingAndTexture();
	glutMainLoop();                        // glut�¼�����ѭ��    

	delete cam;

	return 0;
}