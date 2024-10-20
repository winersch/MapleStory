#include "MPhantomBlowScript.h"
#include "MBoxCollider2D.h"
#include "MSpriteRenderer.h"
#include "MTexture.h" 
#include "MAnimator.h"
#include "MAnimation.h"
#include "MBellumScript.h"
#include "MPlayerScript.h"

namespace maple {





	PhantomBlowScript::PhantomBlowScript() {
	}

	PhantomBlowScript::~PhantomBlowScript() {
	}

	void PhantomBlowScript::Initialize() {
		mbAttackable = false;
		BoxCollider2D* collider = GetOwner()->AddComponent<BoxCollider2D>();
		collider->SetSize(Vector2(0, 0));
		collider->SetOffset(Vector2(0, 0));
	}

	void PhantomBlowScript::Update() {
		BoxCollider2D* collider = GetOwner()->AddComponent<BoxCollider2D>();
		graphics::Texture* texture = GetOwner()->GetComponent<SpriteRenderer>()->GetSprite();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Animation* animation = animator->GetActiveAnimation();
		if (animation == nullptr) {
			return;
		}
		int index = animation->GetIndex();
		bool flip = animation->GetFlip();
		if ((index <= 2 ) && texture != nullptr) {
			collider->SetSize(Vector2(texture->GetWidth(),texture->GetHeight()));
			if (flip) {
				//collider->SetOffset(Vector2((-1.0f * texture->GetWidth()), 0));
			}
			mbAttackable = true;
		}
		else {
			collider->SetSize(Vector2(0, 0));
			mbAttackable = false;
		}
	}

	void PhantomBlowScript::LateUpdate() {
	}

	void PhantomBlowScript::Render() {
	}

	void PhantomBlowScript::OnCollisionEnter(Collider* target) {
		if (mbAttackable == false) {
			return;
		}
		if (target->GetOwner()->GetLayerType() == eLayerType::Monster) {
			target->GetOwner()->GetComponent<BellumScript>()->GetHit(5000000000);
			Vector3 pos = target->GetOwner()->GetComponent<Transform>()->GetPosition() + GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x += target->GetOffset().x;
			pos.y += target->GetOffset().y;
			mPlayer->GetComponent<PlayerScript>()->PhantomBlowHit(pos / 2);
		}
	}

	void PhantomBlowScript::OnCollisionStay(Collider* other) {
		int a = 0;
	}

	void PhantomBlowScript::OnCollisionExit(Collider* target) {
		int a = 0;
	}

}