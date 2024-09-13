#include "MBellumScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MComponent.h"
#include "MGameObject.h"
#include "MTexture.h"
#include "MResources.h"
#include "MTime.h"

/// <summary>
/// bellum attack pattern
/// Long Attack : attack1
/// Short Attack : attack7
/// Fire Attack : attack2 -> attack5 -> attack3 -> attack4 -> attack6
/// Dig Attack : attack8	// 80% 20sec
/// Poision Attack : attack13 -> attack 14(repeat) -> attack 16 // 60% 20sec
/// Breath Attack : attack9 -> attack 10(repeat) -> attack 11 -> attack 12 // 40% 50sec
/// </summary>

namespace maple {


	BellumScript::BellumScript()
		: mAnimator(nullptr)
		, mTime(0.0f)
		, mbHide(true)
		, mState(eState::Idle)
		, mCooldown{}
		, mCooldownTime{}
		, mbSummon(false)
		, mDelay(0.0f){
	}

	BellumScript::~BellumScript() {
		mAnimator = nullptr;
		mPlayer = nullptr;
	}

	void BellumScript::Initialize() {
		Script::Initialize();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Bellum");

		GetOwner()->GetComponent<Transform>()->SetPosition(-195.0f, -95.0f, 0.0f);
		//GetOwner()->GetComponent<Transform>()->SetScale((float)tex->GetWidth(), (float)tex->GetHeight(), 0.0f);


		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		sr->SetSprite(tex);

		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimationByFolder(L"Summon", L"..\\Resources\\rootabyss\\bellum\\bellum\\summon");

		InitializeAnimationEvent();

		mCooldownTime[0] = 6.0f;
		mCooldownTime[1] = 6.0f;
		mCooldownTime[2] = 20.0f;
		mCooldownTime[3] = 20.0f;
		mCooldownTime[4] = 20.0f;
		mCooldownTime[5] = 50.0f;

	}

	void BellumScript::Update() {
		if (!mbSummon) {
			return;
		}

		Script::Update();
		mTime += Time::DeltaTime();
		CooldownUpdate();
		PlayerDistanceUpdate();

		switch (mState) {
			case maple::BellumScript::eState::Idle:
				Idle();
				break;
			case maple::BellumScript::eState::Summon:
				Summon();
				break;
			case maple::BellumScript::eState::Move:
				Move();
				break;
			case maple::BellumScript::eState::ShortAttack:
				ShortAttack();
				break;
			case maple::BellumScript::eState::LongAttack:
				LongAttack();
				break;
			case maple::BellumScript::eState::DigAttack:
				DigAttack();
				break;
			case maple::BellumScript::eState::FireAttack:
				FireAttack();
				break;
			case maple::BellumScript::eState::PoisonAttack:
				PoisonAttack();
				break;
			case maple::BellumScript::eState::BreathAttack:
				BreathAttack();
				break;
			case maple::BellumScript::eState::Death:
				Death();
				break;
			default:
				break;
		}
	}

	void BellumScript::LateUpdate() {
		Script::LateUpdate();
	}

	void BellumScript::Render() {
		Script::Render();
	}

	void BellumScript::AttackUpdate() {
		if (mCooldown[5] <= 0.0f) {
			mState = eState::BreathAttack;
			PlayAnimation(L"attack9", false);
			mCooldown[5] = mCooldownTime[5];
			return;
		}
		if (mCooldown[4] <= 0.0f) {
			mState = eState::PoisonAttack;
			PlayAnimation(L"attack13", false);
			mCooldown[4] = mCooldownTime[4];
			return;
		}
		if (mCooldown[2] <= 0.0f) {
			mState = eState::DigAttack;
			PlayAnimation(L"attack8", false);
			mCooldown[2] = mCooldownTime[2];
			return;
		}
		if (mCooldown[3] <= 0.0f) {
			mState = eState::FireAttack;
			PlayAnimation(L"attack2", false);
			mCooldown[3] = mCooldownTime[3];
			return;
		}
		if (mCooldown[1] <= 0.0f) {
			mState = eState::LongAttack;
			PlayAnimation(L"attack1", false);
			mCooldown[1] = mCooldownTime[1];
			return;
		}
		if (mCooldown[0] <= 0.0f) {
			mState = eState::ShortAttack;
			PlayAnimation(L"attack7", false);
			mCooldown[0] = mCooldownTime[0];
			return;
		}
	}

	void BellumScript::Idle() {
		if (!mAnimator->IsCompleted()) {
			return;
		}

		GetOwner()->GetComponent<SpriteRenderer>()->SetSprite(Resources::Find<graphics::Texture>(L"Empty"));

		if (mDistance < 100.0f) {
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 playerPos = mPlayer->GetComponent<Transform>()->GetPosition();

			if (playerPos.x < pos.x) {
				mbFlip = false;
			}
			else {
				mbFlip = true;
			}
			AttackUpdate();
		}
		else {
			mAnimator->PlayAnimation(L"move", false);
			mState = eState::Move;
		}
	}

	void BellumScript::Summon() {
		mAnimator->PlayAnimation(L"Summon", false);

		for (size_t i = 0; i < 6; i++) {
			mCooldown[i] = mCooldownTime[i];
		}
	}

	void BellumScript::Move() {
		if (mAnimator->IsCompleted()) {
			mState = eState::Idle;
		}
		if (mDistance < 1.0f) {
			mAnimator->StopAnimation();
			mState = eState::Idle;
			return;
		}

		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 playerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		if (playerPos.x < pos.x) {
			pos.x -= 140.0f * Time::DeltaTime();
		}
		else {
			pos.x += 140.0f * Time::DeltaTime();
		}

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);

	}

	void BellumScript::ShortAttack() {
		if (mAnimator->IsCompleted()) {
			mCooldown[0] = mCooldownTime[0];
			mTime = 0.0f;
		}
	}

	void BellumScript::LongAttack() {
		if (mAnimator->IsCompleted()) {
			mCooldown[1] = mCooldownTime[1];
			mTime = 0.0f;
		}
	}

	void BellumScript::DigAttack() {
	}

	void BellumScript::FireAttack() {
		if (mAnimator->IsCompleted()) {
			PlayAnimation(L"attack2", false);
		}
	}

	void BellumScript::PoisonAttack() {
		if (mAnimator->IsCompleted()) {
			PlayAnimation(L"attack13", false);
		}
	}

	void BellumScript::BreathAttack() {
	}

	void BellumScript::Death() {
	}

	void BellumScript::PlayAnimation(const std::wstring& name, bool loop) {
		mAnimator->PlayAnimation(name, loop, mbFlip);
	}

	void BellumScript::CooldownUpdate() {
		for (float& a : mCooldown) {
			if (a > 0.0f) {
				a -= Time::DeltaTime();
			}
		}
	}

	void BellumScript::PlayerDistanceUpdate() {
		Vector3 playerPos = mPlayer->GetComponent<Transform>()->GetPosition();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mDistance = abs(playerPos.x - pos.x);
	}

	void BellumScript::InitializeAnimationEvent() {
		mAnimator->GetCompleteEvent(L"Summon") = [this]() {
			mState = eState::Idle;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos.y = -430.0f;
			tr->SetPosition(pos);
			mbSummon = true;
			};

		mAnimator->GetCompleteEvent(L"move") = [this]() {
			//mState = eState::Idle;
			};
		std::vector<int> v;
		v.push_back(1);
		v.push_back(6);
		v.push_back(7);
		v.push_back(8);
		v.push_back(12);
		v.push_back(16);

		for (size_t i = 0; i < v.size(); i++) {
			mAnimator->GetCompleteEvent(L"attack" + std::to_wstring(v[i])) = [this]() {
				mState = eState::Idle;
				};
		}

		mAnimator->GetCompleteEvent(L"attack2") = [this]() {
			PlayAnimation(L"attack5", false);
			};

		mAnimator->GetCompleteEvent(L"attack5") = [this]() {
			PlayAnimation(L"attack3", false);
			};

		mAnimator->GetCompleteEvent(L"attack3") = [this]() {
			PlayAnimation(L"attack4", false);
			};

		mAnimator->GetCompleteEvent(L"attack4") = [this]() {
			PlayAnimation(L"attack6", false);
			};

		mAnimator->GetCompleteEvent(L"attack13") = [this]() {
			PlayAnimation(L"attack14", false);
			};

		mAnimator->GetCompleteEvent(L"attack14") = [this]() {
			PlayAnimation(L"attack16", false);
			};

		mAnimator->GetCompleteEvent(L"attack9") = [this]() {
			PlayAnimation(L"attack10", false);
			};

		mAnimator->GetCompleteEvent(L"attack10") = [this]() {
			PlayAnimation(L"attack11", false);
			};

		mAnimator->GetCompleteEvent(L"attack11") = [this]() {
			PlayAnimation(L"attack12", false);
			};

	}


}