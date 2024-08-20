#include "MCameraScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MTime.h"
#include "MGameObject.h"
#include "MAnimator.h"
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
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
			pos += 200.0f * -tr->Right() * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::W))
			pos += 200.0f * tr->Up() * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::D))
			pos += 200.0f * tr->Right() * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::S))
			pos += 200.0f * -tr->Up() * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::E))
			pos += 200.0f * tr->Foward() * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::Q))
			pos += 200.0f * -tr->Foward() * Time::DeltaTime();

		tr->SetPosition(pos);
	}

	void CameraScript::LateUpdate() {
	}

	void CameraScript::Render() {
	}


}