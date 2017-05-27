#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include "FPSCamera.h"

#define roomSizeX 200.f
#define roomSizeY 60.f
#define roomSizeZ 200.f

#define SkyboxSize 600.f

void loadTex(int i, char *filename, GLuint* texture);

void drawRect(GLuint texture);
void drawCube(GLuint texture);

void drawSkybox(GLuint* texture);                  //������պ�

void initBoxCollidersProperty();                   //���ú��ӵ�λ�úʹ�С
void drawBoxColliders(GLuint* texture);            //���ƺ���
void setBoxColliderBoundary(FPSCamera* cam);       //���ú�����ײ��Ե