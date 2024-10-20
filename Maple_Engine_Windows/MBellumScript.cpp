#include "MBellumScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MComponent.h"
#include "MGameObject.h"
#include "MTexture.h"
#include "MResources.h"
#include "MTime.h"
#include "MAudioClip.h"
#include "MAudioSource.h"
#include "MCollider.h"
#include "MObject.h"
#include "MRenderer.h"
#include <random>

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
		, mAudioSource(nullptr)
		, mTime(0.0f)
		, mbHide(true)
		, mState(eState::Idle)
		, mCooldown{}
		, mCooldownTime{}
		, mbSummon(false)
		, mbDeath(false)
		, mDelay(0.0f)
		, mHP(200000000000.0f)
		, mMaxHP(200000000000.0f) {
	}

	BellumScript::~BellumScript() {
		mAnimator = nullptr;
		mPlayer = nullptr;
	}

	void BellumScript::Initialize() {
		Script::Initialize();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Bellum");

		GetOwner()->GetComponent<Transform>()->SetPosition(-195.0f, -95.0f, 0.0f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		sr->SetSprite(tex);

		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->CreateAnimationByFolder(L"Summon", L"..\\Resources\\rootabyss\\bellum\\bellum\\summon");

		InitializeAnimationEvent();

		Resources::LoadFromFolder<AudioClip>(L"..\\Resources\\sound\\bellum");
		mAudioSource = GetOwner()->AddComponent<AudioSource>();

		mCooldownTime[0] = 0.0f;
		mCooldownTime[1] = 0.0f;
		mCooldownTime[2] = 35.0f;
		mCooldownTime[3] = 30.0f;
		mCooldownTime[4] = 30.0f;
		mCooldownTime[5] = 50.0f;

		mCollider = GetOwner()->AddComponent<BoxCollider2D>();
		mCollider->SetSize(Vector2(0, 0));
		mCollider->SetOffset(Vector2(0, 0));



	}

	void BellumScript::Update() {
		if (!mbSummon || mbDeath) {
			return;
		}
		

		mTime += Time::DeltaTime();
		CooldownUpdate();
		PlayerDistanceUpdate();
		HitboxUpdate();
		UpdateHPBar();

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
		
		if (mHP / mMaxHP < 0.8f && mCooldown[2] <= 0.0f) {
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

	void BellumScript::HitboxUpdate() {
		if (mAnimator->GetActiveAnimationName() == L"" || mAnimator->GetActiveAnimationName() == L"Summon") {
			return;
		}
		int idx = mAnimator->GetActiveAnimation()->GetIndex()-1;
		if (idx < 0) {
			return;
		}
		std::vector<maple::Animation::Hitbox>& hitboxes = mAnimator->GetActiveAnimation()->GetHitboxes(idx);
		BoxCollider2D* collider = GetOwner()->GetComponent<BoxCollider2D>();
		if (collider == nullptr) {
			return;
		}
		if (hitboxes.size() == 0) {
			collider->SetSize(Vector2(0, 0));
			collider->SetOffset(Vector2(0, 0));
			return;
		}

		Vector2 hitboxOffset = (Vector2)((hitboxes[0].lt + hitboxes[0].rb) / 2);
		collider->SetOffset(hitboxOffset);
		collider->SetSize(Vector2(abs(hitboxes[0].lt.x - hitboxes[0].rb.x), abs(hitboxes[0].lt.y - hitboxes[0].rb.y)));

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
		mHP = mMaxHP;
		InitializeHPBar();
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
			return;
		}
	}

	void BellumScript::LongAttack() {
		if (mAnimator->IsCompleted()) {
			mCooldown[1] = mCooldownTime[1];
			mTime = 0.0f;
			return;
		}
	}

	void BellumScript::DigAttack() {
	}

	void BellumScript::FireAttack() {
	}

	void BellumScript::PoisonAttack() {
	}

	void BellumScript::BreathAttack() {
	}

	void BellumScript::Death() {
		if (mAnimator->IsCompleted() && !mbDeath) {
			PlayAnimation(L"die1", false);
		}
	}

	void BellumScript::OnCollisionEnter(Collider* other) {
	}

	void BellumScript::OnCollisionStay(Collider* other) {
	}

	void BellumScript::OnCollisionExit(Collider* other) {
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
			mState = eState::Idle;
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
				if (mState != eState::Death) {
					mState = eState::Idle;
				}
				};
		}
		for (size_t i = 1; i <= 16; i++) {
			mAnimator->GetStartEvent(L"attack" + std::to_wstring(i)) = [this, i]() {
				AudioClip* clip = Resources::Find<AudioClip>(L"Attack" + std::to_wstring(i));
				GetOwner()->GetComponent<AudioSource>()->SetClip(clip);
				GetOwner()->GetComponent<AudioSource>()->Play();
				};
		}

		mAnimator->GetStartEvent(L"Summon") = [this]() {
			AudioClip* clip = Resources::Find<AudioClip>(L"Attack1");
			GetOwner()->GetComponent<AudioSource>()->SetClip(clip);
			GetOwner()->GetComponent<AudioSource>()->Play();
			};

		mAnimator->GetStartEvent(L"die1") = [this]() {
			AudioClip* clip = Resources::Find<AudioClip>(L"Die");
			GetOwner()->GetComponent<AudioSource>()->SetClip(clip);
			GetOwner()->GetComponent<AudioSource>()->Play();
			};

		mAnimator->GetCompleteEvent(L"die1") = [this]() {
			GetOwner()->SetActive(false);
			mbDeath = true;
			};

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

	void BellumScript::InitializeHPBar() {
		graphics::Texture* bellumHpBarTex = Resources::Load<graphics::Texture>(L"BellumHPBar", L"..\\Resources\\UI\\BellumHPBar.png");

		mHPBarBackground = object::Instantiate<GameObject>(eLayerType::UI);
		mHPBarBackground->AddComponent<SpriteRenderer>()->SetSprite(Resources::Find<graphics::Texture>(L"BellumHPBar"));

		Transform* mHPBarBackgroundTransform = mHPBarBackground->GetComponent<Transform>();

		mHPBarBackgroundTransform->SetScale(bellumHpBarTex->GetWidth(), bellumHpBarTex->GetHeight(), 0.0f);

		Transform* cameraTransform = renderer::mainCamera->GetOwner()->GetComponent<Transform>();
		Vector3 cameraPos = cameraTransform->GetPosition();

		mHPBarBackgroundTransform->SetPosition(cameraPos.x, cameraPos.y + 364.0f, 0.0f);

		graphics::Texture* mHPBarTex = Resources::Load<graphics::Texture>(L"HPGage", L"..\\Resources\\UI\\HPGage.png");

		mHPBar = object::Instantiate<GameObject>(eLayerType::UI);
		mHPBar->AddComponent<SpriteRenderer>()->SetSprite(Resources::Find<graphics::Texture>(L"HPGage"));

		Transform* mHPBarTransform = mHPBar->GetComponent<Transform>();

		mHPBarTransform->SetScale(697.0f * ((float)mHP / (float)mMaxHP), 10.0f, 0.0f);
		Vector3 pos = mHPBarBackgroundTransform->GetPosition();
		float newHPBarWidth = 697.0f * ((float)mHP / (float)mMaxHP);
		mHPBarTransform->SetPosition(pos.x + 20 - (697.0f - newHPBarWidth) / 2, pos.y + 10, 0.0f);

	}

	void BellumScript::UpdateHPBar() {

		Transform* mHPBarBackgroundTransform = mHPBarBackground->GetComponent<Transform>();
		Transform* mHPBarTransform = mHPBar->GetComponent<Transform>();
		Transform* cameraTransform = renderer::mainCamera->GetOwner()->GetComponent<Transform>();
		Vector3 cameraPos = cameraTransform->GetPosition();

		mHPBarBackgroundTransform->SetPosition(cameraPos.x, cameraPos.y + 364.0f, 0.0f);
		mHPBarTransform->SetScale(697.0f * ((float)mHP / (float)mMaxHP), 10.0f, 0.0f);
		Vector3 pos = mHPBarBackgroundTransform->GetPosition();
		float newHPBarWidth = 697.0f * ((float)mHP / (float)mMaxHP);
		mHPBarTransform->SetPosition(pos.x + 20 - (697.0f - newHPBarWidth)/2, pos.y + 10, 0.0f);
	}

	void BellumScript::GetHit(double damage) {
		mHP -= damage;
		if (mHP <= 0.001f) {
			mHP = 0.0f;
			mState = eState::Death;
		}
	}


}