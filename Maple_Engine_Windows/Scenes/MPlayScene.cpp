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
#include "MTime.h"
#include "..\\Maple_Engine_Windows\\MSceneObject.h"
#include "..\\MAlterScript.h"
#include "..\\MBellum.h"
#include "..\\MBellumScript.h"

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
			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector3(000.0f, 000.0f, -1000.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraComp->SetSize(1.0f);

			CameraScript* cameraScript = camera->AddComponent<CameraScript>();
			renderer::mainCamera = cameraComp;


			// player
			mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
			//object::DontDestroyOnLoad(mPlayer, L"Player");

			SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
			sr->SetSprite(playerTex);

			Transform* playerTransform = mPlayer->GetComponent<Transform>();
			playerTransform->SetScale(playerTex->GetWidth(), playerTex->GetHeight(), 0.0f);
			playerTransform->SetPosition(0.0f, 0.0f, 0.0f);

			PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();

			GameObject* alter = object::Instantiate<GameObject>(enums::eLayerType::NPC, Vector3(0.0f, 0.0f, 0.0f));
			AlterScript* alterScript = alter->AddComponent<AlterScript>();



			mGameObjects.insert(std::make_pair(L"Alter", alter));

			//GameObject* alter = object::Instantiate<GameObject>(enums::eLayerType::NPC, Vector3(-0.0f, 0.0f, 0.0f));

			//SpriteRenderer* alterSr = alter->AddComponent<SpriteRenderer>();
			//Texture* alterTex = Resources::Find<graphics::Texture>(L"Alter");
			//alterSr->SetSprite(alterTex);

			//Transform* alterTransform = alter->GetComponent<Transform>();
			//alterTransform->SetScale(alterTex->GetWidth(), alterTex->GetHeight(), 0.0f);
			//alterTransform->SetPosition(0.0f, 0.0f, 0.0f);

			//std::vector<GameObject*> tiles;

			//Texture* enH0_0 = Resources::Find<graphics::Texture>(L"enH0_0");
			//Texture* enH0_1 = Resources::Find<graphics::Texture>(L"enH0_1");
			//Texture* enH0_2 = Resources::Find<graphics::Texture>(L"enH0_2");


			//for (size_t i = 0; i < 10; i++) {
			//	GameObject* tile = object::Instantiate<GameObject>(enums::eLayerType::Floor, Vector3((float)i * 90.0f - 900.0f, 150.0f, 0.0f));
			//	Transform* tileTransform = tile->GetComponent<Transform>();
			//	switch (i % 3) {
			//		case 0:
			//		{
			//			SpriteRenderer* enH0_0Sr = tile->AddComponent<SpriteRenderer>();
			//			enH0_0Sr->SetSprite(enH0_0);
			//			tileTransform->SetScale(enH0_0->GetWidth(), enH0_0->GetHeight(), 0.0f);
			//			break;
			//		}
			//		case 1:
			//		{
			//			SpriteRenderer* enH0_1Sr = tile->AddComponent<SpriteRenderer>();
			//			enH0_1Sr->SetSprite(enH0_1);
			//			tileTransform->SetScale(enH0_1->GetWidth(), enH0_1->GetHeight(), 0.0f);
			//			break;
			//		}
			//		case 2:
			//		{
			//			SpriteRenderer* enH0_2Sr = tile->AddComponent<SpriteRenderer>();
			//			enH0_2Sr->SetSprite(enH0_2);
			//			tileTransform->SetScale(enH0_2->GetWidth(), enH0_2->GetHeight(), 0.0f);
			//			break;
			//		}
			//		default:
			//			break;
			//	}
			//	
			//	tiles.push_back(tile);
			//}

			


		}
	}

	void PlayScene::Update() {
		Scene::Update();
		Vector2 mousePos = Input::GetMousePosition();
		//Transform* tr = mGameObjects.find(L"Alter")->second->GetComponent<Transform>();
		//Vector2 posLeftDown, posRightUp;
		//Vector2 size;
		//size.x = tr->GetScale().x;
		//size.y = tr->GetScale().y;

		//posLeftDown.x = tr->GetPosition().x - size.x / 2;
		//posLeftDown.y = tr->GetPosition().y - size.y / 2;

		//posRightUp.x = tr->GetPosition().x + size.x / 2;
		//posRightUp.y = tr->GetPosition().y + size.y / 2;
		//
		//if (mousePos.x > posLeftDown.x && mousePos.x < posRightUp.x &&
		//	mousePos.y > posLeftDown.y && mousePos.y < posRightUp.y) {
		//	if (Input::GetKeyDown(eKeyCode::LButton)) {
		//		mGameObjects.find(L"Bellum")->second->GetComponent<BellumScript>()->Summon();
		//	}
		//}
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

}

