#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "FPSCamera.h"
#include "Shader.h"

#define roomSizeX 200.f
#define roomSizeY 60.f
#define roomSizeZ 200.f

#define SkyboxSize 600.f             //��պд�С

#define EatBreadDistance 5.f         //�Ե�����ľ���
#define CloseToBreadDistance 200.f    //��������ľ���

void loadTex(int i, char *filename, GLuint* texture);

void drawRect(GLuint texture);
void drawCube(GLuint texture);

void initCube(Shader shader);	
void drawCube(Shader shader, GLuint diffuse, GLuint bump, GLuint spec);	//modern gl draw, init before use.

void drawSkybox(GLuint* texture);                  //������պ�

void initBoxCollidersProperty();                   //���ú��ӵ�λ�úʹ�С
void initSingleBoxCollider(glm::vec3 pos, glm::vec3 scalar);    //���õ������ӵ�λ�úʹ�С
void setBoxColliderBoundary(FPSCamera* cam);       //���ú�����ײ��Ե
void drawBoxColliders(GLuint* texture);            //���ƺ���
void drawBoxColliders(Shader shader, GLuint diffuse, GLuint bump, GLuint spec, FPSCamera* cam);	//Override with modernGL method

void initBreadModels();        //��ʼ�������
void drawBreadModels();        //���������
void playBreadEatenEffect(FPSCamera* cam);
void deleteBreadModels();      //���������

void detectBreadBeingEaten(FPSCamera* cam);      //�������Ƿ񱻳Ե�

void drawMenuSceneUIText(FPSCamera* cam);
void drawGameSceneUIText(FPSCamera* cam, int x, int y);             //����UI����

void setupLights();            //���ù���