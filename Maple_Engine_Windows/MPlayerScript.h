#pragma once
#include "..\\Maple_Engine_SOURCE\\MScript.h"
#include "MAnimator.h"
#include "MTexture.h"
#include "MSkillManager.h"

namespace maple {

	class PlayerScript : public Script{

	public:
		enum class eState {
			Stand,
			Move,
			Attack
		};


		PlayerScript();
		~PlayerScript();


		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SkillInitialize();
		void SkillUpdate();
		void SkillLateUpdate();

		void AttackEffect();

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;


	private:
		void idle();
		void move();


	private:
		eState mState;
		Animator* mAnimator;

		SkillManager* mSkillManager;

		float mTime;
		float mDelay;
		int mDirection;

		bool mbFlip;
		bool mbPlashJumped;
		
				
	};

}

