#pragma once
#include "MScript.h"
#include "MAnimator.h"
#include "MPlayer.h" 
#include "MAudioSource.h" 
#include "MBoxCollider2D.h"

namespace maple {


	class BellumScript : public Script {
	public:

		enum class eState {
			Idle,
			Summon,
			Move,
			ShortAttack,
			LongAttack,
			DigAttack,
			FireAttack,
			PoisonAttack,
			PoisonAttacking,
			BreathAttack,
			BreathAttacking,
			Death,
		};

		BellumScript();
		~BellumScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void AttackUpdate();
		void HitboxUpdate();

		void Idle();
		void Summon();
		void Move();
		void ShortAttack();		//cooldown 0
		void LongAttack();		//cooldown 1
		void DigAttack();		//cooldown 2
		void FireAttack();		//cooldown 3
		void PoisonAttack();		//cooldown 4
		void BreathAttack();		//cooldown 5
		void Death();

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void PlayAnimation(const std::wstring& name, bool loop = false);	

		void CooldownUpdate();

		void SetPlayer(Player* player) { mPlayer = player; }
		void PlayerDistanceUpdate();
		void InitializeAnimationEvent();
		void InitializeHPBar();
		void UpdateHPBar();
		void GetHit(double damage);

	private:
		Animator* mAnimator;
		Player* mPlayer;
		AudioSource* mAudioSource;
		BoxCollider2D* mCollider;

		GameObject* mHPBar;
		GameObject* mHPBarBackground;


		float mTime;
		float mSpeed;
		float mDelay;
		double mHP;
		double mMaxHP;

		float mCooldown[6];
		float mCooldownTime[6];
		float mDistance;
		eState mState;
		bool mbHide;
		bool mbSummon;
		bool mbFlip;

		int mPoisionAttackCount;




	};

}

