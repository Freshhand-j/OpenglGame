#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
using namespace std;

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) < (y) ? (y) : (x))

#define HeroHeight 7.5f

#define GravityAcceler -9.8f

#define MoveSpeed 0.01f
#define BoundaryGap 1.0f
#define JumpInitialSpeed 12.0f
#define JumpFactor 0.004f
#define GravityFactor 0.004f

struct dot {
	float x;
	float y;
	dot(float _x, float _y) :x(_x), y(_y) { }
};

class PhysicsEngine {
public:
	PhysicsEngine();
	~PhysicsEngine();

	//���ÿռ��ⲿ��Ե
	void setSceneOuterBoundary(float x1, float z1, float x2, float z2);
	//�ⲿ��ײ���
	void outCollisionTest(glm::vec3 & cameraPos, glm::vec3 & targetPos);
	//���ÿռ��ڲ���Ե
	void setSceneInnerBoundary(float x1, float y1, float z1, float x2, float y2, float z2);
	//�ڲ���ײ���
	void inCollisionTest(glm::vec3 & cameraPos, glm::vec3 & targetPos);

	bool isJumping;
	void jumpAndUpdateVelocity();    //����space��Ծʱ����
	//ÿ֡���Ƶ�ʱ������������ֱ�����ƶ�
	void updateCameraVertMovement(glm::vec3 & cameraPos, glm::vec3 & targetPos);

private:
	//�ռ��ڲ���Ե��ײ��⣨���Ǹ߶ȣ�
	void inCollisionTestWithHeight(float x1, float y1, float z1, float x2, float y2, float z2, glm::vec3 & cameraPos, glm::vec3 & targetPos);
	//�ռ��ڲ���Ե��ײ��⣨�����Ǹ߶ȣ���XZƽ�棩
	void inCollisionTestXZ(float x1, float z1, float x2, float z2, glm::vec3 & cameraPos, glm::vec3 & targetPos);
	//�ռ��ⲿ��Ե��ײ���
	void outCollisionTestXZ(float x1, float z1, float x2, float z2, glm::vec3 & cameraPos, glm::vec3 & targetPos);

	glm::vec3 velocity;        //��ֱ�����ٶ�
	glm::vec3 gravity;         //�������ٶ�
	glm::vec3 accelerUp;       //�������ϵļ��ٶ�

	glm::vec4 outerBoundary;
	vector<glm::vec3> innerBoundaryMin;    //��ײ��С��x/y/z����
	vector<glm::vec3> innerBoundaryMax;    //��ײ�����x/y/z����
};

#endif // !PHYSICSENGINE_H



