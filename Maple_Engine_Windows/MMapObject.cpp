#include "MMapObject.h"
#include "MTexture.h"
#include "MSpriteRenderer.h"
#include "MResources.h"
#include "MTransform.h"

namespace maple {



	MapObject::MapObject() {

	}

	MapObject::~MapObject() {
		mAnimator = nullptr;
		mName.clear();
	}

	void MapObject::Initialize() {
		GameObject::Initialize();
	}

	void MapObject::Initialize(const std::wstring& name, int x, int y) {
		mName = name;
		mX = x;
		mY = y;

		graphics::Texture* texture = Resources::Load<graphics::Texture>(name, L"..\\Resources\\" + name);
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		Transform* transform = AddComponent<Transform>();
		transform->SetPosition(x, -y, 0.0f);

		if (texture->GetHeight()) {
			sr->SetSprite(texture);
			transform->SetScale(texture->GetWidth(), texture->GetHeight(), 0.0f);
			transform->SetRotation(0.0f, 0.0f, 0.0f);
		}
		else {
			mAnimator = AddComponent<Animator>();
			mAnimator->CreateAnimationByFolder(name, L"..\\Resources\\" + name); 
			mAnimator->PlayAnimation(name, true);
		}
		
	}

	void MapObject::Update() {
		GameObject::Update();
	}

	void MapObject::LateUpdate() {
		GameObject::LateUpdate();
	}

	void MapObject::Render() {
		GameObject::Render();
	}

}