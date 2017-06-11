#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <glm/gtx/string_cast.hpp>
#include "SceneController.h"

#define Sensitivity 0.003    //������������ж�

enum GameStatus { MenuScene, GameScene };

FPSCamera* cam;

static int mouseLastPosX = 0;
static int mouseLastPosY = 0;

GLuint texture[11];

GameStatus gameStatus = MenuScene;

Shader boxShader;

void drawScene() {

	boxShader.Use();
	glStencilMask(0x00);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	drawBoxColliders(boxShader, texture[8], texture[9], texture[10], cam);	//Modern GL
	glDisable(GL_CULL_FACE);
	glUseProgram(NULL);
	
	//��պ�
	glStencilMask(0x00);
	drawSkybox(texture);

	//�ذ�  
	glPushMatrix();
	glStencilMask(0x00);
	glTranslatef(0.0f, -roomSizeY / 2.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	glScalef(roomSizeX, roomSizeZ, 1);
	drawRect(texture[0]);
	glPopMatrix();

	//����  
	//drawBoxColliders(texture);
	drawBreadModels();
	playBreadEatenEffect(cam);

	glColor3f(1, 1, 1);

	//����
	drawGameSceneUIText(cam, 0, 0);

	cam->updateCameraMovement();
	detectBreadBeingEaten(cam);

}

void reshape(int width, int height) {
	if (height == 0) {
		height = 1;        //�ø߶�Ϊ1��������ַ�ĸΪ0������   
	}

	cam->resetWinSize(width, height);    
}

void idle() {
	glutPostRedisplay();
}

void initTexture() {
	glEnable(GL_DEPTH_TEST);
	glGenTextures(11, texture);
	loadTex(0, "Textures/18.bmp", texture);    //�ذ�
	loadTex(1, "Textures/14.bmp", texture);    //����

	//ѡ����������һ����պ���ͼ

	loadTex(2, "Textures/Skybox/SkyBox2_up.bmp", texture);
	loadTex(3, "Textures/Skybox/SkyBox2_down.bmp", texture);
	loadTex(4, "Textures/Skybox/SkyBox2_left.bmp", texture);
	loadTex(5, "Textures/Skybox/SkyBox2_right.bmp", texture);
	loadTex(6, "Textures/Skybox/SkyBox2_front.bmp", texture);
	loadTex(7, "Textures/Skybox/SkyBox2_back.bmp", texture);

	boxShader.Use();
	loadTex(8, "Textures/19d.bmp", texture);		//Box Diffuse
	loadTex(9, "Textures/20b.bmp", texture);		//Box Bump
	loadTex(10,"Textures/21s.bmp", texture);		//Box Specular
	glUseProgram(NULL);

	//loadTex(2, "Textures/Skybox/Sunny_up.bmp", texture);
	//loadTex(3, "Textures/Skybox/Sunny_down.bmp", texture);
	//loadTex(4, "Textures/Skybox/Sunny_left.bmp", texture);
	//loadTex(5, "Textures/Skybox/Sunny_right.bmp", texture);
	//loadTex(6, "Textures/Skybox/Sunny_front.bmp", texture);
	//loadTex(7, "Textures/Skybox/Sunny_back.bmp", texture);
}

void normalKeyPress(unsigned char key, int x, int y) {
	if (gameStatus == GameScene)
		cam->keyPressed(key);
}

void normalKeyUp(unsigned char key, int x, int y) {
	if (gameStatus == GameScene)
		cam->keyUp(key);
}

//���յ��ʱ
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseLastPosX = x;
		mouseLastPosY = y;

		if (gameStatus == MenuScene) {
			//��������޸ĳ�����Ӧ�İ�ťλ������
			if (245 <= x && x <= 357 && 445 <= y && y <= 493)
				gameStatus = GameScene;
			cout << "x " << x << " y " << y << endl;
		}
	}
}

//��������ƶ�ʱ
void mouseMove(int x, int y) {
	if (gameStatus == GameScene) {
		//����������Ծ���
		float pitch = (float)(y - mouseLastPosY) * Sensitivity;
		float yaw = (float)(x - mouseLastPosX) * Sensitivity;
		mouseLastPosY = y;
		mouseLastPosX = x;
		cam->rotate(pitch, yaw);
	}
}

void redraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	if (gameStatus == MenuScene) {
		drawMenuSceneUIText(cam);
	}
	else {
		//��ʼ��ģ����
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		drawScene();
	}
	glutSwapBuffers();
}

void initializeGL() {
	glewInit();
	glewExperimental = GL_TRUE;

	cam = new FPSCamera();
	//�����ײ��Ե
	cam->setSceneOuterBoundary(-roomSizeX / 2.0, -roomSizeZ / 2.0, roomSizeX / 2.0, roomSizeZ / 2.0);

	cam->setSceneInnerBoundary(-roomSizeX / 2.0,  -roomSizeY / 2.0f - 1.f, -roomSizeZ / 2.0,
		roomSizeX / 2.0, -roomSizeY / 2.0f, roomSizeZ / 2.0);    //�ذ�collider

	initBoxCollidersProperty();
	setBoxColliderBoundary(cam);

	initBreadModels();

	setupLights();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	boxShader.load("shader.vert", "shader.frag");
	
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowPosition(250, 100);
	glutInitWindowSize(600, 600);
	int windowHandle = glutCreateWindow("Final project - OpenGL game!");

	initializeGL();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(normalKeyPress);
	glutKeyboardUpFunc(normalKeyUp);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutIdleFunc(idle);

	boxShader.Use();
	initCube(boxShader);
	glUseProgram(NULL);

	initTexture();
	glutMainLoop();

	delete cam;
	deleteBreadModels();

	return 0;
}