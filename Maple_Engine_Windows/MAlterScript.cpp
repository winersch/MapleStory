#include "MAlterScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MComponent.h"
#include "MGameObject.h"
#include "MTexture.h"
#include "MResources.h"

namespace maple {




	AlterScript::AlterScript()
		: mAnimator(nullptr) {
	}

	AlterScript::~AlterScript() {
	}

	void AlterScript::Initialize() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Alter");
		tr->SetPosition(0.0f, 0.0f, 0.0f);
		tr->SetScale(tex->GetWidth(), tex->GetHeight(), 0.0f);

		mAnimator = GetOwner()->AddComponent<Animator>();
		std::vector<float> duration;
		for (size_t i = 0; i < 5; i++) {
			duration.push_back(0.15f);
		}
		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();

		mAnimator->CreateAnimationByFolder(L"AlterIdle", L"..\\Resources\\rootabyss\\bellum\\alter", duration, sr);

		mAnimator->PlayAnimation(L"AlterIdle", true);
	}

	void AlterScript::Update() {

		Vector2 mousePos = Input::GetMousePosition();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos;
		
		pos.x = tr->GetPosition().x;
		pos.y = tr->GetPosition().y;




	}

	void AlterScript::LateUpdate() {
	}

	void AlterScript::Render() {
	}

}