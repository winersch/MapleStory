#include "MBoxCollider2D.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MRenderer.h"

namespace maple {

	BoxCollider2D::BoxCollider2D()
		: Collider(enums::eColliderType::Rect2D) {

	}

	BoxCollider2D::~BoxCollider2D() {

	}

	void BoxCollider2D::Initialize() {

	}

	void BoxCollider2D::Update() {

	}

	void BoxCollider2D::LateUpdate() {

	}

	void BoxCollider2D::Render() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		

	}

}