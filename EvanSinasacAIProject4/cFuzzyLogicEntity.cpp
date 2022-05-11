#include "cFuzzyLogicEntity.h"
#include <iostream>

extern float CalculateAngle(glm::vec3 vecA, glm::vec3 vecB);

cFuzzyLogicEntity::cFuzzyLogicEntity(glm::vec3 startPos, glm::vec3 startForward, glm::vec4 colour)
	: m_Position(startPos)
	, m_Forward(startForward)
{
	this->m_Mesh = new cMesh();
	this->m_Mesh->meshName = "Low Poly Tank Model 3D model_XYZ_N_RGBA_UV.ply";
	this->m_Mesh->positionXYZ = startPos;
	this->m_Mesh->orientationXYZ = glm::vec3(0.0f, 0.0f, glm::radians(glm::acos(startForward.y)));
	this->m_Mesh->bDontLight = true;
	this->m_Mesh->bUseWholeObjectDiffuseColour = true;
	//this->m_Mesh->wholeObjectDiffuseRGBA = glm::vec4(0.4f, 0.8f, 0.6f, 1.0f);
	this->m_Mesh->wholeObjectDiffuseRGBA = colour;
	this->m_Mesh->setUniformScale(0.1f);

	//for (unsigned int index = 0; index != 5; index++)
	//{
	//	this->m_Sensors[index] = new cSensor(startPos);
	//	//this->m_Mesh->vec_pChildMeshes.push_back(this->m_Sensors[index]->m_Mesh);
	//}
	this->m_Sensors[0] = new cSensor(startPos, -2.5f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));	// center should be grey
	this->m_Sensors[1] = new cSensor(startPos, 1.5f, glm::vec4(0.8f, 0.0f, 0.4f, 1.0f));	// 30* left of forward dark pinkish
	this->m_Sensors[2] = new cSensor(startPos, 1.0f, glm::vec4(0.4f, 0.0f, 0.8f, 1.0f));	// 60* left of forward dark purple
	this->m_Sensors[3] = new cSensor(startPos, -1.6f, glm::vec4(0.0f, 0.4f, 0.8f, 1.0f));	// 30* right of forward dark blueish
	this->m_Sensors[4] = new cSensor(startPos, -1.1f, glm::vec4(0.0f, 0.8f, 0.4f, 1.0f));	// 60* right of forward dark green
}
cFuzzyLogicEntity::~cFuzzyLogicEntity()
{

}

void cFuzzyLogicEntity::Update(float dt)
{
	unsigned int closestObstacleToAvoid = CheckSensors();
	
	glm::vec3 rightVector = glm::normalize(glm::cross(this->m_Forward, this->Up));
	
	switch (closestObstacleToAvoid)
	{
	case 0:
		rightVector *= this->m_Sensors[0]->sensorWeight; // -1.0f * 2.5f;	// turn left, 2x weight.  The obstacle is directly ahead
		break;
	case 1:
		rightVector *= this->m_Sensors[1]->sensorWeight; //1.0f * 1.5f;		// turn right, 1x weight.  The obstacle is ahead and slightly to the left
		break;
	case 2:
		rightVector *= this->m_Sensors[2]->sensorWeight; //1.0f * 1.0f;		// turn right 1.5x weight.  The obstacle is mostly left
		break;
	case 3:
		rightVector *= this->m_Sensors[3]->sensorWeight; //-1.0f * 1.5f;	// turn left, 1.5x weight.  The obstacle is ahead and slightly to the right
		break;
	case 4:
		rightVector *= this->m_Sensors[4]->sensorWeight; //-1.0f * 1.0f;	// turn left, 1.0x weight.  The obstacle is mostly to the right
		break;
	default:	// no sensor is detecting anything
		rightVector = glm::vec3(0.0f);
	}

	this->m_Forward += rightVector * dt;
	this->m_Forward = glm::normalize(this->m_Forward);

	this->m_Position += this->m_Forward * dt;
	float angle = CalculateAngle(this->m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
	if (this->m_Forward.x > 0)
		this->m_Mesh->orientationXYZ = glm::vec3(0.0f, 0.0f, -glm::radians(angle));
	else
		this->m_Mesh->orientationXYZ = glm::vec3(0.0f, 0.0f, glm::radians(angle));

	this->m_Mesh->positionXYZ = this->m_Position;
	
	glm::vec3 forwardPlus30 = glm::vec3(this->m_Forward.x * glm::cos(glm::radians(30.0f)) + this->m_Forward.y * glm::sin(glm::radians(30.0f)), 
		-this->m_Forward.x * glm::sin(glm::radians(30.0f)) + this->m_Forward.y * glm::cos(glm::radians(30.0f)), 0.0f);/*) * 1.5f;*/
	glm::vec3 forwardPlus60 = glm::vec3(this->m_Forward.x * glm::cos(glm::radians(60.0f)) + this->m_Forward.y * glm::sin(glm::radians(60.0f)),
		-this->m_Forward.x * glm::sin(glm::radians(60.0f)) + this->m_Forward.y * glm::cos(glm::radians(60.0f)), 0.0f);
	glm::vec3 forwardMinus30 = glm::vec3(this->m_Forward.x * glm::cos(glm::radians(-30.0f)) + this->m_Forward.y * glm::sin(glm::radians(-30.0f)),
		-this->m_Forward.x * glm::sin(glm::radians(-30.0f)) + this->m_Forward.y * glm::cos(glm::radians(-30.0f)), 0.0f);
	glm::vec3 forwardMinus60 = glm::vec3(this->m_Forward.x * glm::cos(glm::radians(-60.0f)) + this->m_Forward.y * glm::sin(glm::radians(-60.0f)),
		-this->m_Forward.x * glm::sin(glm::radians(-60.0f)) + this->m_Forward.y * glm::cos(glm::radians(-60.0f)), 0.0f);

	this->m_Sensors[0]->Update(dt, this->m_Position + this->m_Forward, this->m_Forward);
	this->m_Sensors[1]->Update(dt, this->m_Position + forwardMinus30, this->m_Forward);
	this->m_Sensors[2]->Update(dt, this->m_Position + forwardMinus60, this->m_Forward);
	this->m_Sensors[3]->Update(dt, this->m_Position + forwardPlus30, this->m_Forward);
	this->m_Sensors[4]->Update(dt, this->m_Position + forwardPlus60, this->m_Forward);

}

unsigned int cFuzzyLogicEntity::CheckSensors()
{
	//glm::vec3 obsPos[5];
	for (unsigned int index = 0; index != 5; index++)
	{
		/*obsPos[index] = */
		this->m_Sensors[index]->CheckObstacles();
		//glm::vec3 currentObstacle = this->m_Sensors[index]->CheckObstacles();
		//if (currentObstacle != glm::vec3(-1.0f))	// CheckObstacles goes through the obstacles and returns the position of the closest obstacle within range of the sensor (i.e. the sensor has detected the obstacle)
		//{

		//}
	}
	
	
	//return ChooseObstacle(obsPos);
	return ChooseObstacle();
}

//unsigned int cFuzzyLogicEntity::ChooseObstacle(glm::vec3 obstaclePositions[])
unsigned int cFuzzyLogicEntity::ChooseObstacle()
{
	unsigned int sensorToUse = -1;
	float bestFuzzyValue = 0.0f;
	for (unsigned int index = 0; index != 5; index++)
	{
		if (this->m_Sensors[index]->objectDetected == 1)
		//if (this->m_Sensors[index]->objectDetected == 0)
		{
			continue;	// sensor isn't detecting anything
		}

		float fuzzy = 0.0f;
		fuzzy += CalculateFuzzySteer(index) * FuzzySteerWeight;
		fuzzy += CalculateFuzzySpeed(index) * FuzzySpeedWeight;

		if (fuzzy > bestFuzzyValue)
		{
			sensorToUse = index;
			bestFuzzyValue = fuzzy;
		}
	}

	return sensorToUse;
}

float cFuzzyLogicEntity::CalculateFuzzySpeed(unsigned int i)
{
	float fuzzySpeed = (1 - ((m_Sensors[i]->sensorWeight - MinFuzzySpeed) / (MaxFuzzySpeed - MinFuzzySpeed)));
	return glm::clamp(fuzzySpeed, 0.0f, 1.0f);
}

float cFuzzyLogicEntity::CalculateFuzzySteer(unsigned int i)
{
	glm::vec3 rightVector = glm::normalize(glm::cross(this->m_Forward, this->Up)) * this->m_Sensors[i]->sensorWeight;
	float fuzzyMagnitude = (1 - ((rightVector.length() - MinSteer) / (MaxSteer - MinSteer)));
	return glm::clamp(fuzzyMagnitude, 0.0f, 1.0f);
}