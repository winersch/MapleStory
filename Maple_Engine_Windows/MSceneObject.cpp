#include "MSceneObject.h"


namespace maple {



	SceneObject::SceneObject() {
	}

	SceneObject::~SceneObject() {
	}

	void SceneObject::Initialize() {
		GameObject::Initialize();
	}

	void SceneObject::Update() {
		GameObject::Update();
	}

	void SceneObject::LateUpdate() {
		GameObject::LateUpdate();
	}

	void SceneObject::Render() {
		GameObject::Render();
	}

}