#include "MCameraScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MTime.h"
#include "MGameObject.h"
#include "MAnimator.h"
#include "..\\Maple_Engine_Windows\\Contents\\MCat.h"
#include "MCatScript.h"
#include "MObject.h"
#include "MResources.h"


namespace maple {

	CameraScript::CameraScript() {
	}

	CameraScript::~CameraScript() {
	}

	void CameraScript::Initialize() {
	}

	void CameraScript::Update() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right)) {
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::Left)) {
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::Up)) {
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::Down)) {
			pos.y += 100.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void CameraScript::LateUpdate() {
	}

	void CameraScript::Render(HDC hdc) {
	}


}