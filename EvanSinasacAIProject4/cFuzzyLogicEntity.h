#pragma once

#include "GLMCommon.h"
#include "cMesh.h"
#include "cSensor.h"

class cFuzzyLogicEntity
{
public:
	cFuzzyLogicEntity(glm::vec3 startPos, glm::vec3 startForward, glm::vec4 colour);
	virtual ~cFuzzyLogicEntity();

	void Update(float dt);

	unsigned int CheckSensors();

	//unsigned int ChooseObstacle(glm::vec3 obsticalPositions[]);
	unsigned int ChooseObstacle();

	cMesh* m_Mesh;
	cSensor* m_Sensors[5];
	glm::vec3 m_Position;
protected:
	
private:

	glm::vec3 m_Forward;
	glm::vec3 Up = glm::vec3(0.0f, 0.0f, 1.0f);		// used to determine "right" vector

	//float MinDistance = 0.0f;
	//float MaxDistance = 2.0f;

	//float MinAngle = 0.0f;
	//float MaxAngle = glm::pi<float>() / 2.0f;

	//float FuzzyDistanceWeight = 2.0f;
	//float FuzzyAngleWeight = 1.0f;
	float FuzzySpeedWeight = 1.0f;
	float FuzzySteerWeight = 2.0f;

	float MaxFuzzySpeed = 2.5f;
	float MinFuzzySpeed = -2.5f;
	float MaxSteer = 2.0f;
	float MinSteer = 1.0f;

	//float CalculateFuzzyDistance(float distance);
	//float CalculateFuzzyAngle(glm::vec3 obstaclePosition);

	float CalculateFuzzySpeed(unsigned int i);
	float CalculateFuzzySteer(unsigned int i);
};