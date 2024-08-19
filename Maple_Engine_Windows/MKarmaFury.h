#pragma once
#include "MSkill.h"
#include "MAnimator.h"

namespace maple {

	class KarmaFury : public Skill{

	public:

		KarmaFury();
		~KarmaFury();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		float mDelay;
		float mCoolDown;

		Animator* mAnimator;

	};


}

