#include "MCameraScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MTime.h"
#include "MGameObject.h"
#include "MAnimator.h"
#include "MObject.h"
#include "MResources.h"


namespace maple {

	CameraScript::CameraScript()
		:mTarget(nullptr)
	{
	}

	CameraScript::~CameraScript() {
	}

	void CameraScript::Initialize() {
	}

	void CameraScript::Update() {
		if (mTarget == nullptr) {
			return;
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 currentPos = tr->GetPosition();


		Transform* targetTransform = mTarget->GetComponent<Transform>();
		Vector3 targetPos = targetTransform->GetPosition();

		// 부드럽게 따라가기 위한 보간 비율
		float followSpeed = 5.0f * Time::DeltaTime();

		Vector3 newPos = Vector3::Lerp(currentPos, targetPos, followSpeed);
		newPos.z = currentPos.z;
		tr->SetPosition(newPos);
	}

	void CameraScript::LateUpdate() {
	}

	void CameraScript::Render() {
	}


}