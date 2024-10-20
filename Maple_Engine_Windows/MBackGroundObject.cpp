#include "MBackGroundObject.h"
#include "MTransform.h"
#include "MCameraScript.h"
#include "MRenderer.h"

namespace maple {


	BackGroundObject::BackGroundObject() {
	}

	BackGroundObject::~BackGroundObject() {
	}

	void BackGroundObject::Initialize() {
		GameObject::Initialize();
	}

	void BackGroundObject::Update() {
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		Transform* cameraTransform = renderer::mainCamera->GetOwner()->GetComponent<Transform>();
		Vector3 cameraPos = cameraTransform->GetPosition();

		Vector3 newPos = mOriginPos + Vector3(cameraPos.x * rx - 500, cameraPos.y * ry-200, 0.0f);
		tr->SetPosition(newPos);

	}

	void BackGroundObject::LateUpdate() {
		GameObject::LateUpdate();
	}

	void BackGroundObject::Render() {
		GameObject::Render();
	}

}