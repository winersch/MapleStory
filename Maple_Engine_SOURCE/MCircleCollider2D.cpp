#include "MCircleCollider2D.h"
#include "MTransform.h"
#include "MGameObject.h"
#include "MRenderer.h"
#include "MCamera.h"

namespace maple {


	CircleCollider2D::CircleCollider2D()
		: Collider(enums::eColliderType::Circle2D) 
		, mRadius(0.0f)
	{

	}

	CircleCollider2D::~CircleCollider2D() {

	}

	void CircleCollider2D::Initialize() {

	}

	void CircleCollider2D::Update() {

	}

	void CircleCollider2D::LateUpdate() {

	}

	void CircleCollider2D::Render() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

	}
}