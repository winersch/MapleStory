#include "MBellumScript.h"
#include "MInput.h"
#include "MTransform.h"
#include "MComponent.h"
#include "MGameObject.h"
#include "MTexture.h"
#include "MResources.h"

namespace maple {


	BellumScript::BellumScript()
		: mAnimator(nullptr)
		, mTime(0.0f)
	{
	}

	BellumScript::~BellumScript() {
	}

	void BellumScript::Initialize() {
		Script::Initialize();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Bellum");

		GetOwner()->GetComponent<Transform>()->SetPosition(0.0f, 0.0f, 0.0f);
		GetOwner()->GetComponent<Transform>()->SetScale(tex->GetWidth(), tex->GetHeight(), 0.0f);
		

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		sr->SetSprite(tex);

		mAnimator = GetOwner()->AddComponent<Animator>();
		mAnimator->CreateAnimationByFolder(L"Summon", L"..\\Resources\\rootabyss\\bellum\\summon");

		mAnimator->PlayAnimation(L"Summon", true);
		

	}

	void BellumScript::Update() {
		Script::Update();
	}

	void BellumScript::LateUpdate() {
		Script::LateUpdate();
	}

	void BellumScript::Render() {
		Script::Render();
	}
	
	void BellumScript::Summon() {

	}


}