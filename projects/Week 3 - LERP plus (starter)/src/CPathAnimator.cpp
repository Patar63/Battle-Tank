/*
NOU Framework - Created for INFR 2310 at Ontario Tech.
(c) Samantha Stahlke 2020

CPathAnimator.cpp
Simple component for animating an object along a path.

As a convention in NOU, we put "C" before a class name to signify
that we intend the class for use as a component with the ENTT framework.
*/

#include "CPathAnimator.h"

namespace nou
{
	CPathAnimator::CPathAnimator(Entity& owner)
	{
		m_owner = &owner;

		m_segmentIndex = 0;
		m_segmentTimer = 0.0f;

		m_segmentTravelTime = 1.0f;
		m_mode = PathSampler::PathMode::LERP;
	}

	void CPathAnimator::SetMode(PathSampler::PathMode mode)
	{
		m_mode = mode;
		m_segmentIndex = 0;
	}

	void CPathAnimator::Update(const PathSampler::KeypointSet& keypoints, float deltaTime)
	{
		// TODO: Implement this function
		// Steps to follow:

		// Make sure we have points to use
		// Ensure we have at least 2 points to LERP along
		// Need at least 2 points for 1 segment
		if (keypoints.size() > 1)
		{
			// Increment our t value
			m_segmentTimer += deltaTime;

			// Work out t using segment timer and segment travel time
			float t = m_segmentTimer / m_segmentTravelTime;

			// Handle switching segments each time t = 1
			if (t >= 1)
			{
				m_segmentTimer = 0.0f;
				t = 0.0f;
				m_segmentIndex++;

				if (m_segmentIndex >= keypoints.size())
				{
					m_segmentIndex = 0;
				}
			}

			// Determine the indices of the points to LERP along (in our vector of key points)
			int ind1 = m_segmentIndex;
			int ind2 = m_segmentIndex + 1;
			if (ind2 >= keypoints.size())
			{
				ind2 = 0;
			}

			// Perform LERP using function in PathSampler
			m_owner->transform.m_pos = PathSampler::LERP(keypoints[ind1]->transform.m_pos, keypoints[ind2]->transform.m_pos, t);
		}
	}
}