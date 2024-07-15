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

	void TitleScene::Render(HDC hdc) {
		Scene::Render(hdc);
		wchar_t str[50] = L"Title Scene";
		TextOut(hdc, 0, 0, str, 11);
	}

	void TitleScene::OnEnter() {
		Scene::OnEnter();

	}

	void TitleScene::OnExit() {
		Scene::OnExit();
	}

}