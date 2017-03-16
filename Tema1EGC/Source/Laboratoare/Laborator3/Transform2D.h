#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		// TODO implement translate matrix
		return glm::transpose(
			glm::mat3(1.0f, 0.0f, translateX,
				0.0f, 1.0f, translateY,
				0.0f, 0.0f, 1.0f)
		);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		// TODO implement scale matrix
		return glm::transpose(
			glm::mat3(scaleX, 0.0f, 0.0f,
				0.0f, scaleY, 0.0f,
				0.0f, 0.0f, 1.0f)
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		// TODO implement rotate matrix
		float sinu = glm::sin(radians);
		float cosu = glm::cos(radians);

		return glm::transpose(
			glm::mat3(cosu, -sinu, 0.0f,
				sinu, cosu, 0.0f,
				0.0f, 0.0f, 1.0f)
		);
	}
}
