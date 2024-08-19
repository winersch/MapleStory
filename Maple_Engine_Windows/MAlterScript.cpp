#include "MAlterScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MComponent.h"
#include "MGameObject.h"

namespace maple {




	AlterScript::AlterScript() {
	}

	AlterScript::~AlterScript() {
	}

	void AlterScript::Initialize() {
	}

	void AlterScript::Update() {

		Vector2 mousePos = Input::GetMousePosition();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos;
		
		pos.x = tr->GetPosition().x;
		pos.y = tr->GetPosition().y;




	}

	void AlterScript::LateUpdate() {
	}

	void AlterScript::Render() {
	}

}