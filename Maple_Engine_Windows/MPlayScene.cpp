#include "MPlayScene.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MSpriteRenderer.h"
#include "..\\Maple_Engine_SOURCE\\MSceneManager.h"
#include "MPlayer.h"
#include "MInput.h"
#include "MObject.h"
#include "MTexture.h"
#include "MResources.h"
#include "MPlayerScript.h"
#include "MCamera.h"
#include "MRenderer.h"
#include "MAnimator.h"
#include "MBoxCollider2D.h"
#include "MCollisionManager.h"
#include "MTile.h"
#include "MTilemapRenderer.h"
#include "MRigidbody.h"
#include "MCameraScript.h"
#include "MFloor.h"
#include "MUIManager.h"
#include "MAudioClip.h"
#include "MAudioListener.h"
#include "MAudioSource.h"
#include "MGraphicDevice_DX11.h"
#include "MMaterial.h"
#include "MTime.h"
#include "MSceneObject.h"
#include "MAlterScript.h"
#include "MBellum.h"
#include "MBellumScript.h"
#include "MReadXML.h"

namespace maple {

	PlayScene::PlayScene()
		: mPlayer(nullptr)
		, mGameObjects({})
		, mTime(0.0f)
	{

	}

	PlayScene::~PlayScene() {

	}

	void PlayScene::Initialize() {



		{
			Scene::Initialize();
			
			// main camera
			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector3(000.0f, -300.0f, -500.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraComp->SetSize(500.0f);

			CameraScript* cameraScript = camera->AddComponent<CameraScript>();
			renderer::mainCamera = cameraComp;


			// player
			mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
			object::DontDestroyOnLoad(mPlayer, L"Player");
			cameraScript->SetTarget(mPlayer);

			SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
			sr->SetSprite(playerTex);

			Transform* playerTransform = mPlayer->GetComponent<Transform>();
			playerTransform->SetScale(playerTex->GetWidth()*2, playerTex->GetHeight()*2, 0.0f);
			playerTransform->SetPosition(0.0f, 0.0f, 0.0f);

			PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();

			GameObject* alter = object::Instantiate<GameObject>(enums::eLayerType::NPC);
			AlterScript* alterScript = alter->AddComponent<AlterScript>();

			mGameObjects.insert(std::make_pair(L"Alter", alter));

			GameObject* bellum = object::Instantiate<GameObject>(enums::eLayerType::Monster);
			mGameObjects.insert(std::make_pair(L"Bellum", bellum));
			LoadTileMap(L"..\\Resources\\rootabyss\\tile\\tile.xml");
			LoadMapObject(L"..\\Resources\\rootabyss\\mapObject.xml");
			LoadBossMonster(L"..\\Resources\\rootabyss\\bellum\\bellum.xml");
			BellumScript* bellumScript = bellum->AddComponent<BellumScript>();
			bellumScript->SetPlayer(mPlayer);

		}
	}

	void PlayScene::Update() {
		Scene::Update();
		
	}

	void PlayScene::LateUpdate() {
		Scene::LateUpdate();
		
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

	void PlayScene::LoadTileMap(const std::wstring& path) {
		ReadXML* xml = new ReadXML();
		xml->LoadXML(path);
		xml->CreateTileMap(mTileMap);
		delete xml;
	}

	void PlayScene::LoadMapObject(const std::wstring& path) {
		ReadXML* xml = new ReadXML();
		xml->LoadXML(path);
		xml->CreateMapObject(mMapObjects);
		delete xml;
	}

	void PlayScene::LoadBossMonster(const std::wstring& path) {
		ReadXML* xml = new ReadXML();
		xml->LoadXML(path);
		xml->LoadBossMonster(path, mGameObjects[L"Bellum"]);
		delete xml;
	}

	

}

