#include "MTile.h"
#include "MInput.h"
#include "MTransform.h"
#include "MSpriteRenderer.h"
#include "MTexture.h"
#include "MResources.h"


namespace maple {



	Tile::Tile()
		: mX(0), mY(0), mNo(0)
	{
	}

	Tile::~Tile() {
	}

	void Tile::Initialize() {
		GameObject::Initialize();
	}

	void Tile::Initialize(const std::wstring& name, int x, int y, int no) {
		mName = name;
		mX = x;
		mY = y;
		mNo = no;

		
		graphics::Texture* texture = Resources::Load<graphics::Texture>(name + std::to_wstring(no), L"..\\Resources\\rootabyss\\tile\\" + name + L"\\" + std::to_wstring(no) + L".png");
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetSprite(texture);
		Transform* transform = AddComponent<Transform>();
		transform->SetPosition(x, -y, 0.0f);
		transform->SetScale(texture->GetWidth(), texture->GetHeight(), 0.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);
	}

	void Tile::Update() {
		GameObject::Update();
	}

	void Tile::LateUpdate() {
		GameObject::LateUpdate();
	}

	void Tile::Render() {
		GameObject::Render();
	}
	

}