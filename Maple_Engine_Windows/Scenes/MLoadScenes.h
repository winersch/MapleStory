#pragma once
#include "..\\Maple_Engine_SOURCE\\MSceneManager.h"

#include "MLoadingScene.h"
#include "MPlayScene.h"
#include "MTitleScene.h"



namespace maple {

	void LoadScenes() {

		SceneManager::CreateScene<LoadingScene>(L"LoadingScene");

		SceneManager::LoadScene(L"LoadingScene");
	}
}
