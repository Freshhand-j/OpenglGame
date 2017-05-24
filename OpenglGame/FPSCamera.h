#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
using namespace std;

class FPSCamera {
	public:

		FPSCamera();
		void resetWinSize(int w, int h);    //���ڴ�С�����仯ʱ�ص�

		void setSceneOuterBoundary(float x1, float z1, float x2, float z2);    //���ÿռ��ⲿ��Ե
		void setSceneInnerBoundary(float x1, float y1, float z1, float x2, float y2, float z2);    //���ÿռ��ڲ���Ե

		void rotate(GLfloat const pitchRad, GLfloat const yawRad);
		void keyPressed(const unsigned char key);       //��������
		void keyUp(const unsigned char key);            //����̧��

		void updateCameraMovement();    //ÿ֡���Ƶ�ʱ�����������ƶ�

	private:
		void updateCameraHoriMovement();        //ÿ֡���Ƶ�ʱ����������ˮƽ�����ƶ�
		void updateCameraVertMovement();        //ÿ֡���Ƶ�ʱ������������ֱ�����ƶ�
		void updateView();                      //�����ӽ�

		void inCollisionTest(float x1, float z1, float x2, float z2);     //�ռ��ڲ���Ե��ײ���
		void inCollisionTestWithHeight(float x1, float y1, float z1, float x2, float y2, float z2);
		void outCollisionTest(float x1, float z1, float x2, float z2);    //�ռ��ⲿ��Ե��ײ���

		int winH = 0;
		int winW = 0;

		bool isWPressing, isSPressing, isAPressing, isDPressing;
		bool isJumping;

		glm::vec4 outerBoundary;
		vector<glm::vec3> innerBoundaryMin;    //��ײ��С��x/y/z����
		vector<glm::vec3> innerBoundaryMax;    //��ײ�����x/y/z����

		//Current view matrix
		glm::mat4 viewMatrix;
		//Lens parameters for the camera
		GLfloat pfov, pratio, pnear, pfar;

		glm::vec3 cameraPos;
		glm::vec3 targetPos;
		//Camera roll, pitch, yaw info.
		GLfloat roll, pitch, yaw;

		glm::vec3 velocity;        //��ֱ�����ٶ�
		glm::vec3 gravity;         //�������ٶ�
		glm::vec3 accelerUp;       //�������ϵļ��ٶ�

};