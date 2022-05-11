#include "cSensor.h"
#include "globalThings.h"

extern float CalculateAngle(glm::vec3 vecA, glm::vec3 vecB);

cSensor::cSensor(glm::vec3 pos, float weight, glm::vec4 colour)
	: m_Position(pos)
	, sensorWeight(weight)
{
	// Make the mesh
	this->m_Mesh = new cMesh();
	this->m_Mesh->meshName = "Isosphere_Smooth_Normals.ply";
	this->m_Mesh->positionXYZ = pos;
	this->m_Mesh->bDontLight = true;
	this->m_Mesh->bUseWholeObjectDiffuseColour = true;
	//this->m_Mesh->wholeObjectDiffuseRGBA = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	this->m_Mesh->wholeObjectDiffuseRGBA = colour;
	this->m_Mesh->bIsWireframe = true;
	this->m_Mesh->setUniformScale(0.1f);

	objectDetected = 1;
}

cSensor::~cSensor()
{

}

void cSensor::Update(float dt, glm::vec3 position, glm::vec3 forward)
{
	this->m_Forward = forward;
	this->m_Position = position;
	this->m_Mesh->positionXYZ = this->m_Position;
}

//glm::vec3 cSensor::CheckObstacles()
int cSensor::CheckObstacles()
{
	//glm::vec3 bestObstacle = glm::vec3(-1.0f);	// the closest obstacle that we need to try and avoid
	float bestFuzzyValue = 1.0f;

	// Check all obstacles and decide whether or not we should return a force to push the vehicle away from it
	for (unsigned int index = 0; index != ::obstaclePositions.size(); index++)
	{
		float distance = glm::distance(this->m_Position, ::obstaclePositions[index]);
		if (distance > MaxDistance)
		{
			continue;
		}

		float fuzzy = 1.0f;
		fuzzy -= CalculateFuzzyDistance(distance) * FuzzyObstacleDistanceWeight;
		fuzzy -= CalculateFuzzyAngle(::obstaclePositions[index]) * FuzzyAngleWeight;

		if (fuzzy < bestFuzzyValue)
		//if (fuzzy > bestFuzzyValue)
		{
			//bestObstacle = ::obstaclePositions[index];
			bestFuzzyValue = fuzzy;
		}
	}

	// now we have to check the positions of all the vehicles
	for (unsigned int index = 0; index != ::vec_pFLEntities.size(); index++)
	{
		float distance = glm::distance(this->m_Position, ::vec_pFLEntities[index]->m_Position);
		if (distance > MaxDistance)
		{
			continue;
		}

		float fuzzy = 1.0f;
		fuzzy -= CalculateFuzzyDistance(distance) * FuzzyVehicleDistanceWeight;
		fuzzy -= CalculateFuzzyAngle(::vec_pFLEntities[index]->m_Position);

		if (fuzzy < bestFuzzyValue)
		//if (fuzzy > bestFuzzyValue)
		{
			//bestObstacle = ::vec_pFLEntities[index]->m_Position;
			bestFuzzyValue = fuzzy;
		}
	}

	//return bestObstacle;
	this->objectDetected = glm::clamp(bestFuzzyValue, 0.0f, 1.0f);
	return this->objectDetected;	// 0 should mean that there are no obstacles detected
}


float cSensor::CalculateFuzzyDistance(float distance)
{
	float fuzzyDistance = (1 - ((distance - MinDistance) / (MaxDistance - MinDistance)));
	return glm::clamp(fuzzyDistance, 0.0f, 1.0f);
}

float cSensor::CalculateFuzzyAngle(glm::vec3 obstaclePosition)
{
	glm::vec3 toObstacle = obstaclePosition - this->m_Position;
	toObstacle = glm::normalize(toObstacle);
	float angleDifference = CalculateAngle(toObstacle, this->m_Forward);
	float fuzzyAngle = (1 - ((angleDifference - MinAngle) / (MaxAngle - MinAngle)));
	return glm::clamp(fuzzyAngle, 0.0f, 1.0f);
}