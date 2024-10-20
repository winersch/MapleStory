#include "MCollider.h"
#include "MGameObject.h"
#include "MScript.h"

namespace maple {

	UINT Collider::CollisionID = 1;

	Collider::Collider(eColliderType type)
		: Component(enums::eComponentType::Collider)
		, mType(type)
		, mID(CollisionID++)
		, mSize(Vector2::One) {

	}

	Collider::~Collider() {

	}
	
	void Collider::Initialize() {

	}

	void Collider::Update() {

	}

	void Collider::LateUpdate() {

	}

	void Collider::Render() {

	}

	void Collider::OnCollisionEnter(Collider* other) {
		Script* script = GetOwner()->GetComponent<Script>();
		if (script == nullptr) {
			return;
		}
		script->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other) {
		Script* script = GetOwner()->GetComponent<Script>();
		if (script == nullptr) {
			return;
		}
		script->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other) {
		Script* script = GetOwner()->GetComponent<Script>();
		if (script == nullptr) {
			return;
		}
		script->OnCollisionExit(other);
	}

}