#include "MAlterScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MComponent.h"
#include "MGameObject.h"
#include "MTexture.h"
#include "MResources.h"
#include "MSceneManager.h"
#include "MObject.h"
#include "MBellum.h" 
#include "MBellumScript.h"
#include "MRenderer.h"

namespace maple {




	AlterScript::AlterScript()
		: mAnimator(nullptr)
		, mbClicked(false){
	}

	AlterScript::~AlterScript() {
	}

	void AlterScript::Initialize() {
		Script::Initialize();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Alter");
		tr->SetPosition(-195.0f, -290.0f, 0.0f);
		tr->SetScale(tex->GetWidth(), tex->GetHeight(), 0.0f);

		mAnimator = GetOwner()->AddComponent<Animator>();
		std::vector<float> duration;
		for (size_t i = 0; i < 5; i++) {
			duration.push_back(0.15f);
		}
		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();

		mAnimator->CreateAnimationByFolder(L"AlterIdle", L"..\\Resources\\rootabyss\\bellum\\alter");

		mAnimator->PlayAnimation(L"AlterIdle", true);
	}

	void AlterScript::Update() {
		Script::Update();
		if (mbClicked == false) {
			onClick();
		}
	}

	void AlterScript::LateUpdate() {
		Script::LateUpdate();
	}

	void AlterScript::Render() {
		Script::Render();
	}

	void AlterScript::onClick() {

		Vector2 mousePos = Input::GetMousePosition();

		Vector3 worldMousePos = renderer::mainCamera->ScreenToWorld(mousePos);

		mousePos.x = worldMousePos.x;
		mousePos.y = worldMousePos.y;

		//Vector2 mousePos = Input::GetMousePosition();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 posLeftDown, posRightUp;
		Vector2 size;
		size.x = tr->GetScale().x;
		size.y = tr->GetScale().y;

		posLeftDown.x = tr->GetPosition().x - size.x / 2;
		posLeftDown.y = tr->GetPosition().y - size.y / 2;

		posRightUp.x = tr->GetPosition().x + size.x / 2;
		posRightUp.y = tr->GetPosition().y + size.y / 2;
		
		if (mousePos.x > posLeftDown.x && mousePos.x < posRightUp.x &&
			mousePos.y > posLeftDown.y && mousePos.y < posRightUp.y) {
			if (Input::GetKeyDown(eKeyCode::LButton)) {
				summonBellum();
				mbClicked = true;
			}
		}
	}

	void AlterScript::summonBellum() {
		GameObject* bellum = object::Instantiate<GameObject>(enums::eLayerType::Monster);
		//SceneManager::GetActiveScene()->AddGameObject(bellum, L"Bellum", enums::eLayerType::Monster);
		BellumScript* bellumScript = bellum->AddComponent<BellumScript>();

	}

}