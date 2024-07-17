#include "MPlayScene.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MSpriteRenderer.h"
#include "..\\Maple_Engine_SOURCE\\MSceneManager.h"
#include "..\\Maple_Engine_Windows\Contents\MPlayer.h"
#include "MInput.h"
#include "MObject.h"
#include "MTexture.h"
#include "MResources.h"
#include "..\\Maple_Engine_Windows\\Scripts\\MPlayerScript.h"
#include "MCamera.h"
#include "MRenderer.h"
#include "MAnimator.h"
#include "..\\Maple_Engine_Windows\Contents\MCat.h"
#include "MBoxCollider2D.h"
#include "MCollisionManager.h"
#include "..\\Maple_Engine_Windows\\Contents\\MTile.h"
#include "MTilemapRenderer.h"
#include "MRigidbody.h"
#include "..\\Maple_Engine_Windows\\Scripts\\MCameraScript.h"
#include "..\\Maple_Engine_Windows\\Contents\\MFloor.h"
#include "MUIManager.h"
#include "MAudioClip.h"
#include "MAudioListener.h"
#include "MAudioSource.h"
#include "MGraphicDevice_DX11.h"
#include "MMaterial.h"

namespace maple {

	PlayScene::PlayScene()
		:mPlayer(nullptr)
	
	{

	}

	PlayScene::~PlayScene() {
	}

	void PlayScene::Initialize() {

	

		{
			Scene::Initialize();

			// main camera
			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraComp->SetSize(700.0f);

			CameraScript* cameraScript = camera->AddComponent<CameraScript>();
			renderer::mainCamera = cameraComp;

			mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
			object::DontDestroyOnLoad(mPlayer);
			
			SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			sr->SetSprite(Resources::Find<graphics::Texture>(L"Player"));

		}
	}

	void PlayScene::Update() {
		Scene::Update();
	}

	void PlayScene::LateUpdate() {
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void PlayScene::Render() {
		Scene::Render();
	}

	void PlayScene::OnEnter() {
		Scene::OnEnter();
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		//UIManager::Push(eUIType::Button);
	}

	void PlayScene::OnExit() {
		//UIManager::Pop(eUIType::Button);
		Scene::OnExit();
	}

}

