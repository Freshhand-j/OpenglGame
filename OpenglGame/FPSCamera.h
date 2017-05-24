#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
using namespace std;

class FPSCamera {
	public:

		FPSCamera();
		void resetWinSize(int w, int h);    //���ڴ�С�����仯ʱ�ص�

		void setSceneOuterBoundary(float x1, float z1, float x2, float z2);    //���ÿռ��ⲿ��Ե
		void setSceneInnerBoundary(float x1, float z1, float x2, float z2);    //���ÿռ��ڲ���Ե

		void setSceneInnerBoundaryMap(float x1, float y1, float z1, float x2, float y2, float z2);    //���ÿռ��ڲ���Ե

		void rotate(GLfloat const pitchRad, GLfloat const yawRad);
		void keyPressed(const unsigned char key);       //��������
		void keyUp(const unsigned char key);            //����̧��

		void detectCameraMove();        //ÿ֡���Ƶ�ʱ����������Ƿ��ƶ�

	private:

		//Taking changes into effect.
		void updateView();
		void detectJump();              //ÿ֡���Ƶ�ʱ�����Ƿ���Ծ

		int winH = 0;
		int winW = 0;

		bool isWPressing, isSPressing, isAPressing, isDPressing;
		bool isJumping;

		glm::vec4 outerBoundary;
		map<glm::vec3, glm::vec3> innerBoundaryMap;    //���ΪС��x/y/z���꣬�Ҽ�Ϊ���x/y/z����
		vector<glm::vec4> innerBoundary;

		vector<glm::vec3> innerBoundaryMin;
		vector<glm::vec3> innerBoundaryMax;

		//Current view matrix
		glm::mat4 viewMatrix;
		//Lens parameters for the camera
		GLfloat pfov, pratio, pnear, pfar;

		glm::vec3 cameraPos;
		glm::vec3 targetPos;
		//Camera roll, pitch, yaw info.
		GLfloat roll, pitch, yaw;

		glm::vec3 velocity, gravity;


		void inCollisionTest(float x1, float z1, float x2, float z2);     //�ռ��ڲ���Ե��ײ���
		void inCollisionTestWithHeight(float x1, float y1, float z1, float x2, float y2, float z2);
		void outCollisionTest(float x1, float z1, float x2, float z2);    //�ռ��ⲿ��Ե��ײ���
};