/*
NOU Framework - Created for INFR 2310 at Ontario Tech.
(c) Samantha Stahlke 2020

CMorphAnimator.cpp
Simple animator component for demonstrating morph target animation.

As a convention in NOU, we put "C" before a class name to signify
that we intend the class for use as a component with the ENTT framework.
*/

#include "CMorphAnimator.h"
#include "CMorphMeshRenderer.h"
#include "NOU/Mesh.h"
#include "NOU/GLTFLoader.h"

namespace nou
{
	CMorphAnimator::AnimData::AnimData()
	{
		//define needed m_data
		std::vector<Mesh*> frames;
		frame0 = nullptr;
		frame1 = nullptr;
		frameTime = 1.0f;
	}

	CMorphAnimator::CMorphAnimator(Entity& owner)
	{
		m_owner = &owner;
		m_data = std::make_unique<AnimData>();
		m_timer = 0.0f;
		m_forwards = true;
	}

	
	void CMorphAnimator::Update(float deltaTime)
	{
		m_timer += deltaTime;
		while (m_timer > m_data->frameTime)
		{
			m_timer -= m_data->frameTime;
			m_data->frameTime += 1;

			if (m_data->frameTime >= m_data->frames.size())
			{
				m_data->frameTime = 0;
			}
		}

		float t = m_timer / m_data->frameTime;

		//keep track of size of the vector and manage the frame count
		int FRIC = 0;
		int FRIP = 0;
		FRIP = m_data->FrameInd;

		if (FRIP == 0)
		{
			FRIC = m_data->frames.size() - 1;
		}
		else
		{
			FRIC = FRIP - 1;
		}

		//update frames 
		m_data->frame0 = m_data->frames[FRIC];
		m_data->frame1 = m_data->frames[FRIP];

		//update data from Mesh Renderer
		m_owner->Get<CMorphMeshRenderer>().UpdateData(*m_data->frame0, *m_data->frame1, t);
	}

	void CMorphAnimator::LoadFrames(Mesh* Frame)
	{
		m_data->frames.push_back(Frame);
	}

}