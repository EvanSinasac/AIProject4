#include "GLMCommon.h"


float CalculateAngle(glm::vec3 vecA, glm::vec3 vecB)
{
	vecA = glm::normalize(vecA);
	vecB = glm::normalize(vecB);
	float dot = glm::dot(vecA, vecB);
	float denom = glm::length(vecA) * glm::length(vecB);	// shouldn't this always be one if we normalize them?
	return glm::degrees(glm::acos(dot / denom));
}