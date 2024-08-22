#pragma once
#include "..\\Maple_Engine_SOURCE\\MScript.h"
#include "MAnimator.h"
#include "MTexture.h"

namespace maple {

	class PlayerScript : public Script{

	public:
		enum class eState {
			Idle,
			Walk,
			Sleep,
			GiveWater,
			Attack,
		};


		PlayerScript();
		~PlayerScript();


		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void AttackEffect();

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;


	private:
		void idle();
		void move();
		void giveWater();

	private:
		eState mState;
		Animator* mAnimator;
		
				
	};

}

