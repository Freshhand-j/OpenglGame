#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
	velocity = glm::vec3(0.f, 0.f, 0.f);
	gravity = glm::vec3(0.f, GravityAcceler, 0.f);
	accelerUp = glm::vec3(0.f, 0.f, 0.f);

	isJumping = false;
}

PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::setSceneOuterBoundary(float x1, float z1, float x2, float z2) {
	outerBoundary = glm::vec4(x1, z1, x2, z2);
}

void PhysicsEngine::setSceneInnerBoundary(float x1, float y1, float z1, float x2, float y2, float z2) {
	glm::vec3 key(x1 - BoundaryGap, y1 - BoundaryGap, z1 - BoundaryGap);
	glm::vec3 value(x2 + BoundaryGap, y2 + BoundaryGap, z2 + BoundaryGap);

	innerBoundaryMin.push_back(key);
	innerBoundaryMax.push_back(value);
}

void PhysicsEngine::outCollisionTest(glm::vec3 & cameraPos, glm::vec3 & targetPos) {
	outCollisionTestXZ(outerBoundary[0], outerBoundary[1], outerBoundary[2], outerBoundary[3], cameraPos, targetPos);
}
void PhysicsEngine::outCollisionTestXZ(float x1, float z1, float x2, float z2, glm::vec3 & cameraPos, glm::vec3 & targetPos) {
	//�����ð�Χ�У��ȿռ��ⲿ��ԵСһ��
	if (x1 < 0)
		x1 += 2;
	else x1 -= 2;

	if (x2 < 0)
		x2 += 2;
	else x2 -= 2;

	if (z1 < 0)
		z1 += 2;
	else z1 -= 2;

	if (z2 < 0)
		z2 += 2;
	else z2 -= 2;

	//���Ŀ��λ�ó��˰�Χ�У��ȷŻ���
	if (targetPos[0] < x1) {
		targetPos[0] = x1;
	}

	if (targetPos[0] > x2) {
		targetPos[0] = x2;
	}
	if (targetPos[2] < z1) {
		targetPos[2] = z1;
	}
	if (targetPos[2] > z2) {
		targetPos[2] = z2;
	}

	float distance = sqrt((cameraPos[0] - targetPos[0])*(cameraPos[0] - targetPos[0]) +
		(cameraPos[2] - targetPos[2])*(cameraPos[2] - targetPos[2]));

	//���ӵ���Ŀ�����̫С����̶�Ŀ��λ�ã��ӵ�������Ŀ����淽���ƶ�
	if (distance <= 2.0f) {
		cameraPos[0] = 2.0f*(cameraPos[0] - targetPos[0]) / distance + targetPos[0];
		cameraPos[2] = 2.0f*(cameraPos[2] - targetPos[2]) / distance + targetPos[2];
	}
	bool flag = false;

	//�ټ���ӵ��Ƿ���˰�Χ�У�������Ż�
	if (cameraPos[0] < x1) {
		flag = true;
		cameraPos[0] = x1;
	}
	if (cameraPos[0] > x2) {
		flag = true;
		cameraPos[0] = x2;
	}
	if (cameraPos[2] < z1) {
		flag = true;
		cameraPos[2] = z1;
	}
	if (cameraPos[2] > z2) {
		flag = true;
		cameraPos[2] = z2;
	}

	//�ظ�����Զ���������Ĳ���
	if (flag) {
		distance = sqrt((cameraPos[0] - targetPos[0])*(cameraPos[0] - targetPos[0]) +
			(cameraPos[2] - targetPos[2])*(cameraPos[2] - targetPos[2]));

		if (distance <= 2.0f) {
			targetPos[0] = 2.0f*(targetPos[0] - cameraPos[0]) / distance + cameraPos[0];
			targetPos[2] = 2.0f*(targetPos[2] - cameraPos[2]) / distance + cameraPos[2];
		}
	}
}

void PhysicsEngine::jumpAndUpdateVelocity() {
	velocity += glm::vec3(0.f, JumpInitialSpeed, 0.f);
	accelerUp.y = 0.f;
}

//�ж���xzƽ�棬���λ���Ƿ�λ����ײ���ڲ�
bool insideTheCollider(glm::vec3 _cameraPos, glm::vec3 _innerMin, glm::vec3 _innerMax) {
	float camX = _cameraPos.x;
	float camZ = _cameraPos.z;
	float minX = _innerMin.x;
	float minZ = _innerMin.z;
	float maxX = _innerMax.x;
	float maxZ = _innerMax.z;

	if (minX <= camX && camX <= maxX && minZ <= camZ && camZ <= maxZ)
		return true;
	else
		return false;
}

void PhysicsEngine::updateCameraVertMovement(glm::vec3 & cameraPos, glm::vec3 & targetPos) {
	glm::vec3 acceleration = gravity + accelerUp;
	velocity += acceleration * GravityFactor;
	cameraPos += velocity * JumpFactor;
	targetPos += velocity * JumpFactor;

	//if (abs(velocity.y) < 0.1f)
	//	cout << "#### cameraPos.y " << cameraPos.y << endl;

	//���������ײ��
	for (int i = 0; i < innerBoundaryMin.size(); i++) {
		if (insideTheCollider(cameraPos, innerBoundaryMin[i], innerBoundaryMax[i])) {
			//cout << "inside the colliderXZ" << endl;
			if (cameraPos.y - HeroHeight <= innerBoundaryMax[i][1]) {    //�Ӵ�����ײ��
				//cout << "touch the colliderY" << endl;
				isJumping = false;
				accelerUp.y = -GravityAcceler;
				velocity.y = 0.f;
				cameraPos.y = innerBoundaryMax[i][1] + HeroHeight;
				break;
			}
			else {
				accelerUp.y = 0.f;
			}
		}
		else {
			accelerUp.y = 0.f;
		}
	}
}

void PhysicsEngine::inCollisionTest(glm::vec3 & cameraPos, glm::vec3 & targetPos) {
	//���������������ӣ�Ԥ�����ų���ǰ�϶����������ײ������
	for (int i = 0; i < innerBoundaryMin.size(); i++) {
		inCollisionTestWithHeight(innerBoundaryMin[i][0], innerBoundaryMin[i][1], innerBoundaryMin[i][2],
			innerBoundaryMax[i][0], innerBoundaryMax[i][1], innerBoundaryMax[i][2], cameraPos, targetPos);
	}
}

void PhysicsEngine::inCollisionTestWithHeight(float x1, float y1, float z1, float x2, float y2, float z2, glm::vec3 & cameraPos, glm::vec3 & targetPos) {
	if (!(cameraPos[1] <= y1 || cameraPos[1] - HeroHeight >= y2)) {
		inCollisionTestXZ(x1, z1, x2, z2, cameraPos, targetPos);
	}
}
double Direction(dot pi, dot pj, dot pk) {
	return (pk.x - pi.x)*(pj.y - pi.y) - (pj.x - pi.x)*(pk.y - pi.y);
}

bool OnSegment(dot pi, dot pj, dot pk) {
	if ((min(pi.x, pj.x) <= pk.x) && (pk.x <= max(pi.x, pj.x))
		&& (min(pi.y, pj.y) <= pk.y) && (pk.y <= max(pi.y, pj.y)))
		return true;
	else return false;
}

//����߶��ཻ�����㷨
bool SegmentIntersect(dot p1, dot p2, dot p3, dot p4) {
	int d1, d2, d3, d4;
	d1 = Direction(p3, p4, p1);
	d2 = Direction(p3, p4, p2);
	d3 = Direction(p1, p2, p3);
	d4 = Direction(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2>0)) && ((d3>0 && d4 < 0) || (d3 < 0 && d4>0)))
		return true;
	else if (d1 == 0 && OnSegment(p3, p4, p1))
		return true;
	else if (d2 == 0 && OnSegment(p3, p4, p2))
		return true;
	else if (d3 == 0 && OnSegment(p1, p2, p3))
		return true;
	else if (d4 == 0 && OnSegment(p1, p2, p4))
		return true;
	else
		return false;
}

void PhysicsEngine::inCollisionTestXZ(float x1, float z1, float x2, float z2, glm::vec3 & cameraPos, glm::vec3 & targetPos) {
	const float d = 2.0f;
	float tarX = targetPos[0], camX = cameraPos[0], tarZ = targetPos[2], camZ = cameraPos[2];
	float len = sqrt((camX - tarX)*(camX - tarX) + (camZ - tarZ)*(camZ - tarZ));

	dot d1(cameraPos[0], cameraPos[2]), d2(targetPos[0], targetPos[2]);
	dot d3(x1, z1), d4(x1, z2), d5(x2, z1), d6(x2, z2);

	if (SegmentIntersect(d1, d2, d4, d6)) {
		if (targetPos[2] < cameraPos[2]) {
			printf("1\n");

			//��������������ԭ����㣬
			//���ı�z����
			targetPos[2] = z2;
			cameraPos[2] += (targetPos[2] - tarZ);
		}
		else if (targetPos[2] > cameraPos[2]) {
			printf("2\n");
			cameraPos[2] = z2;
			targetPos[2] += (cameraPos[2] - camZ);
		}
	}
	else if (SegmentIntersect(d1, d2, d5, d6)) {
		if (targetPos[0]<cameraPos[0]) {
			printf("3\n");
			targetPos[0] = x2;
			cameraPos[0] += (targetPos[0] - tarX);
		}
		else if (targetPos[0]>cameraPos[0]) {
			printf("4\n");
			cameraPos[0] = x2;
			targetPos[0] += (cameraPos[0] - camX);
		}
	}
	else if (SegmentIntersect(d1, d2, d3, d5)) {
		if (targetPos[2] > cameraPos[2]) {
			printf("5\n");
			targetPos[2] = z1;
			cameraPos[2] += (targetPos[2] - tarZ);
		}
		else if (targetPos[2] < cameraPos[2]) {
			printf("6\n");
			cameraPos[2] = z1;
			targetPos[2] += (cameraPos[2] - camZ);
		}
	}
	else if (SegmentIntersect(d1, d2, d3, d4)) {
		if (targetPos[0] > cameraPos[0]) {
			printf("7\n");
			targetPos[0] = x1;
			cameraPos[0] += (targetPos[0] - tarX);
		}
		else if (targetPos[0] < cameraPos[0]) {
			printf("8\n");
			cameraPos[0] = x1;
			targetPos[0] += (cameraPos[0] - camX);
		}
	}
}
