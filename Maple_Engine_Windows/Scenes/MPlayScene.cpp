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
#include "..\\Maple_Engine_Windows\Scripts\MCatScript.h"
#include "MBoxCollider2D.h"
#include "MCollisionManager.h"
#include "..\\Maple_Engine_Windows\\Contents\\MTile.h"
#include "MTilemapRenderer.h"
#include "MRigidbody.h"
#include "..\\Maple_Engine_Windows\\Contents\\MFloor.h"
#include "..\\Maple_Engine_Windows\\Scripts\\MFloorScript.h"
#include "MUIManager.h"
#include "MAudioClip.h"
#include "MAudioListener.h"
#include "MAudioSource.h"


namespace maple {

	PlayScene::PlayScene()
		:mPlayer()
	
	{

	}

	PlayScene::~PlayScene() {
	}

	void PlayScene::Initialize() {

	

		{
			// main camera
			GameObject* camera =object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 440.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::mainCamera = cameraComp;

			mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
			object::DontDestroyOnLoad(mPlayer);
			mPlayer->AddComponent<AudioListener>();

			PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();

			BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
			//CircleCollider2D* collider = mPlayer->AddComponent<CircleCollider2D>();
			collider->SetOffset(Vector2(-50.0f, -50.0f));


			graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
			Animator* playerAnimator = mPlayer->AddComponent<Animator>();
			playerAnimator->CreateAnimation(L"Idle", playerTex
				, Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
			playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
				, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.005f);

			playerAnimator->PlayAnimation(L"Idle", false);

			playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);

			//playerAnimator->

			mPlayer->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 250.0f));
			//mPlayer->GetComponent<Transform>()->SetRotation(0.0f);
			//mPlayer->GetComponent<Transform>()->SetScale(Vector2(3.0f, 3.0f));

			mPlayer->AddComponent<Rigidbody>();

			//Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(100.0f, 600.0f));
			Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(0.0f, 0.0f));
			floor->SetName(L"Floor");
			SpriteRenderer* floorSR = floor->AddComponent<SpriteRenderer>();
			floorSR->SetTexture(Resources::Find<graphics::Texture>(L"PixelMap"));

			AudioSource* as = floor->AddComponent<AudioSource>();

			plScript->SetPixelMapTexture(Resources::Find<graphics::Texture>(L"PixelMap"));

			//BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
			//floorCol->SetSize(Vector2(3.0f, 1.0f));
			//floor->AddComponent<FloorScript>();

			AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sound\\smw_bonus_game_end.wav");
			as->SetClip(ac);
			//as->Play();

			Scene::Initialize();
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

	void PlayScene::Render(HDC hdc) {
		Scene::Render(hdc);
	}

	void PlayScene::OnEnter() {
		Scene::OnEnter();
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		UIManager::Push(eUIType::Button);
	}

	void PlayScene::OnExit() {
		UIManager::Pop(eUIType::Button);
		Scene::OnExit();
	}

}

