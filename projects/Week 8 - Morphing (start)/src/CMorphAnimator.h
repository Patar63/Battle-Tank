/*
NOU Framework - Created for INFR 2310 at Ontario Tech.
(c) Samantha Stahlke 2020

CMorphAnimator.h
Simple animator component for demonstrating morph target animation.

As a convention in NOU, we put "C" before a class name to signify
that we intend the class for use as a component with the ENTT framework.
*/

#pragma once

#include "NOU/Entity.h"

namespace nou
{
	class Mesh;

	class CMorphAnimator
	{
	public:

		CMorphAnimator(Entity& owner);
		~CMorphAnimator() = default;

		CMorphAnimator(CMorphAnimator&&) = default;
		CMorphAnimator& operator=(CMorphAnimator&&) = default;

		void Update(float deltaTime);

		//function to load frames
		void LoadFrames(Mesh* Frame);

	protected:

		Entity* m_owner;

		class AnimData
		{
		public:

			//store and manage full animation clips for the exercise.

			std::vector<Mesh*> frames;
			std::vector<Mesh*> Frame;
			const Mesh* frame0;
			const Mesh* frame1;
			int FrameInd = 0;
			

			//The time inbetween frames.
			float frameTime;

			AnimData();
			~AnimData() = default;
		};

		std::unique_ptr<AnimData> m_data;

		float m_timer;
		bool m_forwards;
	};
}