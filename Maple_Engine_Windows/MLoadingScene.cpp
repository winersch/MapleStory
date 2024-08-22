#pragma once
#include "MLoadingScene.h"
#include "MRenderer.h"
#include "MSceneManager.h"
#include "MResources.h"
#include "MTexture.h"
#include "MApplication.h"
#include "MRenderer.h"
#include "MTitleScene.h"
#include "MPlayScene.h"

extern maple::Application application;

namespace maple {

	LoadingScene::LoadingScene()
		: mbLoadCompleted(false)
		, mMutualExclusion()
		, mResourcesLoadThread() {

	}

	LoadingScene::~LoadingScene() {
		delete mResourcesLoadThread;
		mResourcesLoadThread = nullptr;
	}

	void LoadingScene::Initialize() {
		//mResourcesLoadThread = new std::thread(&LoadingScene::resourcesLoad, this, std::ref(mMutualExclusion));
		Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Cat\\stand\\0_100.png");
		Resources::Load<graphics::Texture>(L"Alter", L"..\\Resources\\rootabyss\\bellum\\alter\\0_100.png");
		Resources::Load<graphics::Texture>(L"tile", L"..\\Resources\\rootabyss\\tile\\enH0\\0.png");

		Resources::Load<graphics::Texture>(L"Bellum", L"..\\Resources\\rootabyss\\bellum\\summon\\0_330.png");
		//Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\Entrence.png");
		//Resources::Load<graphics::Texture>(L"enH0_0", L"..\\Resources\\rootabyss\\tile\\enH0\\0.png");
		//Resources::Load<graphics::Texture>(L"enH0_1", L"..\\Resources\\rootabyss\\tile\\enH0\\1.png");
		//Resources::Load<graphics::Texture>(L"enH0_2", L"..\\Resources\\rootabyss\\tile\\enH0\\2.png");	


		renderer::Initialize();

		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::SetActiveScene(L"LoadingScene");
		mbLoadCompleted = true;

		application.IsLoaded(true);
		SceneManager::LoadScene(L"PlayScene");
	}

	void LoadingScene::Update() {
		
	}

	void LoadingScene::LateUpdate() {

	}

	void LoadingScene::Render() {
		//if (mbLoadCompleted) {

		//	//만약 메인쓰레드가 종료되는데 자식쓰레드가 남아있다면
		//	//자식쓰레드를 메인쓰레드에 편입시켜 메인쓰레드가 종료되기전까지 block
		//	mResourcesLoadThread->join();

		//	//메인쓰레드와 완전 분리 시켜 독립적인 쓰레드 운영가능
		//	//mResourcesLoadThread->detach();

		//	SceneManager::LoadScene(L"PlayScene");
		//}
	}

	void LoadingScene::OnEnter() {

	}

	void LoadingScene::OnExit() {

	}
	void LoadingScene::resourcesLoad(std::mutex& m) {
		while (true) {
			if (application.IsLoaded() == true)
				break;
		}
		m.lock();
		{
			Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Cat\\stand\\0_100.png");
			Resources::Load<graphics::Texture>(L"Alter", L"..\\Resources\\rootabyss\\bellum\\alter\\0_100.png");
			Resources::Load<graphics::Texture>(L"Bellum", L"..\\Resources\\rootabyss\\bellum\\summon\\0_330.png");
			//Resources::Load<graphics::Texture>(L"BG", L"..\\Resources\\Entrence.png");
			//Resources::Load<graphics::Texture>(L"enH0_0", L"..\\Resources\\rootabyss\\tile\\enH0\\0.png");
			//Resources::Load<graphics::Texture>(L"enH0_1", L"..\\Resources\\rootabyss\\tile\\enH0\\1.png");
			//Resources::Load<graphics::Texture>(L"enH0_2", L"..\\Resources\\rootabyss\\tile\\enH0\\2.png");	


			renderer::Initialize();

			//SceneManager::CreateScene<TitleScene>(L"TitleScene");
			SceneManager::CreateScene<PlayScene>(L"PlayScene");
		}
		m.unlock();

		// complete
		SceneManager::SetActiveScene(L"LoadingScene");
		mbLoadCompleted = true;

		application.IsLoaded(true);
	}

}