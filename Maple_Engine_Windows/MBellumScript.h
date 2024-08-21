#pragma once
#include "MScript.h"
#include "MAnimator.h"

namespace maple {


	class BellumScript : public Script {
	public:

		enum class eState {
			Idle,
			Summon,
			Moving,
			Attack,
			Dead,
		};

		BellumScript();
		~BellumScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Summon();


	private:
		float mTime;
		float mSpeed;
		long long mHP;

		Animator* mAnimator;

	};

}

