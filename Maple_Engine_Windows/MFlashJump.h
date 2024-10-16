#pragma once
#include "MSkill.h"

namespace maple {

	class FlashJump : public Skill{

	public:

		FlashJump();
		~FlashJump();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		float getDelay() { return mDelay; }
		float getCoolDown() { return mCoolDown; }

	private:
		bool mbIsJumping;
		float mDelay;
		float mCoolDown;

	};
};

