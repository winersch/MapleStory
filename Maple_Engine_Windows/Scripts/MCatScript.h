#pragma once
#include "..\\Maple_Engine_SOURCE\\MScript.h"
#include "MAnimator.h"
#include "MTransform.h"

namespace maple {

	class CatScript : public Script {

	public:
		enum class eState {
			SitDown,
			Walk,
			Sleep,
			LayDown,
			Attack
		};

		enum class eDirection {
			Left,
			Right,
			Up,
			Down,
			End
		};


		CatScript();
		~CatScript();


		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void SetPlayer(GameObject* player) { mPlayer = player; }
		Vector2 mDest;

	private:
		void sitDown();
		void move();
		void layDown();
		void playWalkAnimationByDirection(eDirection dir);
		void translate(Transform* tr);

	private:
		eState mState;
		eDirection mDirection;
		Animator* mAnimator;
		float mTime;
		float mDeathTime;
		GameObject* mPlayer;
		float mRadian;
	};

}

