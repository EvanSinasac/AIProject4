#pragma once

#include "cMesh.h"
#include "GLMCommon.h"

class cSensor
{
public:
	cSensor(glm::vec3 pos, float weight, glm::vec4 colour);
	virtual ~cSensor();

	void Update(float dt, glm::vec3 position, glm::vec3 forward);
	// Checks all the obstacles and determines which if any need to be avoided
	//glm::vec3 CheckObstacles();
	int CheckObstacles();

	glm::vec3 m_Position;
	glm::vec3 m_Forward;
	cMesh* m_Mesh;
	int objectDetected;
	float sensorWeight;
protected:

private:
	float CalculateFuzzyDistance(float distance);
	float CalculateFuzzyAngle(glm::vec3 obstaclePosition);

	float MinDistance = 0.0f;
	float MaxDistance = 0.75f;

	float MinAngle = 0.0f;
	float MaxAngle = glm::pi<float>() / 2.0f;

	float FuzzyObstacleDistanceWeight = 2.0f;
	float FuzzyVehicleDistanceWeight = 1.0f;
	float FuzzyAngleWeight = 1.0f;
};