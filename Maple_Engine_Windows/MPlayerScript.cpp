#include "MPlayerScript.h"
#include "MComponent.h"
#include "MTime.h"
#include "MTransform.h"
#include "MInput.h"
#include "MGameObject.h"
#include "MResources.h"
#include "MObject.h"
#include "MRigidbody.h"
#include "MUIManager.h"
#include "MSkillManager.h"
#include "MSkill.h"
#include "MReadXML.h"
#include "MAudioClip.h"
#include "MPhantomBlowScript.h"

namespace maple {

	PlayerScript::PlayerScript()
		:mState(eState::Stand)
		, mAnimator(nullptr)
		, mTime(0.0f)
		, mbFlashJumped(false)
		, mDirection(1)
		, mbFlip(true)
		, mDelay(0.0f)
		, mbDoubleFlashJumped(false)
		, mAudioSource(nullptr)
		, mSkillManager(nullptr)

	{
	}

	PlayerScript::~PlayerScript() {
	}

	void PlayerScript::Initialize() {
		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->CreateAnimationByFolder(L"Stand", L"..\\Resources\\Cat\\stand");
		mAnimator->CreateAnimationByFolder(L"Move", L"..\\Resources\\Cat\\move");
		mAnimator->CreateAnimationByFolder(L"Attack", L"..\\Resources\\Cat\\attack");
		Resources::Load<graphics::Texture>(L"Jump", L"..\\Resources\\Cat\\jump.png");
		Resources::Load<AudioClip>(L"JumpClip", L"..\\Resources\\sound\\player\\Jump.mp3");
		
		mAnimator->PlayAnimation(L"Stand", true);

		for (auto& a : mAnimator->GetAnimations()) {
			a.second->SetFixedFlip(true);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(-745.0f, -376.0f, 0.0f);

		GetOwner()->AddComponent<Rigidbody>();
		GetOwner()->AddComponent<SkillManager>();
		mAudioSource = GetOwner()->AddComponent<AudioSource>();

		SkillInitialize();

	}

	void PlayerScript::Update() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Rigidbody* playerRb = GetOwner()->GetComponent<Rigidbody>();
		mTime += Time::DeltaTime();
		mDelay -= Time::DeltaTime();

		if (mbFlip) {
			GetOwner()->GetComponent<Transform>()->SetRotation(Vector3(0, 180, 0));
		}
		else {
			GetOwner()->GetComponent<Transform>()->SetRotation(Vector3(0, 0, 0));
		}

		if (pos.y <= -410.0f) {
			playerRb->SetGround(true);
			mbFlashJumped = false;
			mbDoubleFlashJumped = false;
			pos.y = -409.9f;
			mState = eState::Stand;
		}

		if (pos.x <= -1900.0f) {
			pos.x = -1899.9f;
		}
		if (pos.x >= 1000.0f) {
			pos.x = 999.9f;
		}

		tr->SetPosition(pos);
		move();
		PlayerAnimationUpdate();

	}

	void PlayerScript::LateUpdate() {
	}

	void PlayerScript::Render() {
	}

	void PlayerScript::PlayerAnimationUpdate() {
		std::wstring activeAnimationName = mAnimator->GetActiveAnimationName();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		
		switch (mState) {
			case eState::Stand:
				if (activeAnimationName != L"Stand") {
					mAnimator->StopAnimation();
					mAnimator->PlayAnimation(L"Stand", true);
				}
				break;
			case eState::Move:
				if (activeAnimationName != L"Move") {
					mAnimator->StopAnimation();
					mAnimator->PlayAnimation(L"Move", true);
				}
				break;
			case eState::Jump:
			{
				mAnimator->StopAnimation();
				graphics::Texture* texture = Resources::Find<graphics::Texture>(L"Jump");
				GetOwner()->GetComponent<SpriteRenderer>()->SetSprite(texture);
				tr->SetScale(texture->GetWidth(), texture->GetHeight(), 0.0f);
				break;
			}
			case eState::Attack:
				if (activeAnimationName != L"Attack") {
					mAnimator->StopAnimation();
					mAnimator->PlayAnimation(L"Attack", true);
				}
				break;
		}
	}

	void PlayerScript::SkillInitialize() {
		mSkillManager = GetOwner()->AddComponent<SkillManager>();

		ReadXML* xml = new ReadXML();
		xml->LoadSkill(L"..\\Resources\\skill\\skill.xml", mSkillManager);

		Animator* skillAnimator = mSkillManager->GetAnimator();
		for (auto& a : skillAnimator->GetAnimations()) {
			std::wstring path = L"..\\Resources\\sound\\player\\skill" + a.first + L"Hit";
			AudioClip* hitaudioclip = Resources::Load<AudioClip>(a.first + L"Hit", L"..\\Resources\\sound\\player\\skill\\" + a.first + L"\\Hit.mp3");
			AudioClip* useaudioclip = Resources::Load<AudioClip>(a.first + L"Use", L"..\\Resources\\sound\\player\\skill\\" + a.first + L"\\Use.mp3");
		}
	}

	void PlayerScript::SkillUpdate() {
	}

	void PlayerScript::SkillLateUpdate() {
	}

	void PlayerScript::AttackEffect() {

	}

	void PlayerScript::OnCollisionEnter(Collider* other) {
	}

	void PlayerScript::OnCollisionStay(Collider* other) {

	}

	void PlayerScript::OnCollisionExit(Collider* other) {

	}

	void PlayerScript::PhantomBlowHit(Vector3 pos) {
		if (!mbFlip) {
			pos.x = -pos.x;
		}

		mSkillManager->PlayAnimationWithOffset(L"PhantomBlowHit", false, pos, mbFlip);
		for (size_t i = 0; i < 3; i++) {
			mAudioSource->Play(L"PhantomBlowHit");
		}
	}

	void PlayerScript::idle() {

	}

	void PlayerScript::move() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();

		if (mDelay < 0.001f && rb->GetGround()) {
			if (abs(velocity.x) <= 0.001f) {
				mState = eState::Stand;
			}
			else {
				mState = eState::Move;
			}
		}

		if (Input::GetKey(eKeyCode::Right)) {
			if (velocity.x <= 180.0f && mDelay < 0.01f) {
				if (rb->GetGround()) {
					rb->AddForce(Vector2(4000.0f, 0.0f));
				}
				else {
					rb->AddForce(Vector2(200.0f, 0.0f));
				}
			}
			mDirection = 1;
			mbFlip = true;
		}
		if (Input::GetKey(eKeyCode::Left)) {
			if (velocity.x >= -180.0f && mDelay < 0.01f) {
				if (rb->GetGround()) {
					rb->AddForce(Vector2(-4000.0f, 0.0f));
				}
				else {
					rb->AddForce(Vector2(-200.0f, 0.0f));
				}
			}
			mDirection = -1;
			mbFlip = false;
		}
		if (Input::GetKeyDown(eKeyCode::Up) || Input::GetKeyDown(eKeyCode::Alt)) {
			bool b = rb->GetGround();
			if (rb->GetGround()) {
				mAudioSource->Play(L"JumpClip");
				mAnimator->StopAnimation();
				mState = eState::Jump;
				velocity.y = 300.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
				mbFlashJumped = false;
				mbDoubleFlashJumped = false;
			}
			else if (!mbFlashJumped) {
				mbFlashJumped = true;
				mAudioSource->Play(L"FlashJumpUse");
				velocity.y += 100.0f;
				velocity.x = 500.0f * mDirection;
				rb->SetVelocity(velocity);
				mSkillManager->PlayAnimation(L"FlashJump", false, mbFlip);
			}
			else if (!mbDoubleFlashJumped) {
				mbDoubleFlashJumped = true;
				mAudioSource->Play(L"FlashJumpUse");
				velocity.y += 100.0f;
				velocity.x = 500.0f * mDirection;
				rb->SetVelocity(velocity);
				mSkillManager->PlayAnimation(L"FlashJump", false, mbFlip);
			}
		}
		if (Input::GetKey(eKeyCode::Down)) {
		}

		if (Input::GetKey(eKeyCode::W)) {
			if (mDelay < 0.001f) {
				mSkillManager->PlayAnimation(L"KramaFury", false, mbFlip);
				mDelay = 1.9f;
			}
		}

		if (Input::GetKey(eKeyCode::Ctrl)) {
			if (mDelay < 0.001f) {
				mState = eState::Attack;
				mAudioSource->Play(L"PhantomBlowUse");
				GameObject* skillObject = mSkillManager->PlayAnimation(L"PhantomBlow", false, mbFlip);
				PhantomBlowScript* phantomBlowScript = skillObject->AddComponent<PhantomBlowScript>();
				phantomBlowScript->SetPlayer(GetOwner());
				mDelay = 0.7f;
			}
		}

	}




}