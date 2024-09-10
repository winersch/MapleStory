#pragma once
#include "MGameObject.h"
#include "CommonInclude.h"
#include "MAnimator.h"

namespace maple {

	class BossMonster : public GameObject{

	public:

		BossMonster();
		~BossMonster();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;


	protected:


	private:



	public:

	protected:
		Animator* mAnimator;

		std::vector<int> mCoolDown;
		std::vector<int> mCoolDownTime;
		std::vector<std::pair<Vector3, Vector3>> mAttackRange;
		std::vector<std::pair<Vector3, Vector3>> mCurrHeatBox;

		long long mHP;
		float mSpeed;


	private:

		

		
		


	};



}


