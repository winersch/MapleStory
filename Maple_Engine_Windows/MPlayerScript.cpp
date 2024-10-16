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

namespace maple {

	PlayerScript::PlayerScript()
		:mState(eState::Stand)
		, mAnimator(nullptr)
		, mTime(0.0f)
		, mbPlashJumped(false)
		, mDirection(1)

	{
	}

	PlayerScript::~PlayerScript() {
	}

	void PlayerScript::Initialize() {
		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->CreateAnimationByFolder(L"Stand", L"..\\Resources\\Cat\\stand");
		mAnimator->CreateAnimationByFolder(L"Move", L"..\\Resources\\Cat\\move");
		mAnimator->CreateAnimationByFolder(L"Attack", L"..\\Resources\\Cat\\attack");

		mAnimator->PlayAnimation(L"Stand", true);

		for (auto& a : mAnimator->GetAnimations()) {
			a.second->SetFixedFlip(true);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(-745.0f, -376.0f, 0.0f);

		GetOwner()->AddComponent<Rigidbody>();
		GetOwner()->AddComponent<SkillManager>();

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
			GetOwner()->GetComponent<Transform>()->SetRotation(Vector3(0,0,0));
		}

		if (pos.y <= -410.0f) {
			playerRb->SetGround(true);
			mbPlashJumped = false;
			pos.y = -409.9f;
			tr->SetPosition(pos);
		}
		else {
			//playerRb->SetGround(false);
		}

		move();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();

	}

	void PlayerScript::LateUpdate() {
	}

	void PlayerScript::Render() {
	}

	void PlayerScript::SkillInitialize() {
		mSkillManager = GetOwner()->AddComponent<SkillManager>();

		ReadXML* xml = new ReadXML();
		xml->LoadSkill(L"..\\Resources\\skill\\skill.xml", mSkillManager);

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

	void PlayerScript::idle() {

	}

	void PlayerScript::move() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();

		if (Input::GetKey(eKeyCode::Right)) {
			//pos.x += 200.0f * Time::DeltaTime();
			if (abs(velocity.x) <= 1000.0f) {
				if (rb->GetGround()) {
					rb->AddForce(Vector2(1000.0f, 0.0f));
				}
				else {
					rb->AddForce(Vector2(200.0f, 0.0f));
				}
			}
			mDirection = 1;
			mbFlip = true;
		}
		if (Input::GetKey(eKeyCode::Left)) {
			//pos.x -= 200.0f * Time::DeltaTime();
			if (abs(velocity.x) >= -1000.0f) {
				if (rb->GetGround()) {
					rb->AddForce(Vector2(-1000.0f, 0.0f));
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
				velocity.y = 300.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
				mbPlashJumped = false;
			}
			else if (!mbPlashJumped) {
				mbPlashJumped = true;
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
				mSkillManager->PlayAnimation(L"PhantomBlow", false, mbFlip);
				mSkillManager->PlayAnimation(L"PhantomBlow0", false, mbFlip);
				mDelay = 0.7f;
			}
		}


		//if (velocity.x > 250) {
		//	velocity.x = 250;
		//}
		//if (velocity.x < -250) {
		//	velocity.x = -250;
		//}

		//tr->SetPosition(pos);

	}
	



}