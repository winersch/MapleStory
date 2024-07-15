#include "..\\Maple_Engine_SOURCE\\MSceneManager.h"

#include "MTitleScene.h"
#include "MPlayScene.h"
#include "MInput.h"

namespace maple {

	TitleScene::TitleScene() {
	}

	TitleScene::~TitleScene() {
	}

	void TitleScene::Initialize() {
		Scene::Initialize();
	}

	void TitleScene::Update() {
		Scene::Update();
	}

	void TitleScene::LateUpdate() {
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"PlayScene");
		}
	}

	void TitleScene::Render() {
		Scene::Render();
	}

	void TitleScene::OnEnter() {
		Scene::OnEnter();

	}

	void TitleScene::OnExit() {
		Scene::OnExit();
	}

}