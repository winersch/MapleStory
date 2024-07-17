#include "MSpriteRenderer.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MTexture.h"
#include "MRenderer.h"
#include "MCamera.h"
#include "MTransform.h"
#include "MResources.h"

namespace maple {
	using namespace math;
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::SpriteRenderer)
		, mSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr) {
	}

	SpriteRenderer::~SpriteRenderer() {
	}

	void SpriteRenderer::Initialize() {
		mMesh = Resources::Find<Mesh>(L"RectMesh");
		mMaterial = Resources::Find<Material>(L"Sprite-Default-Material");
	}

	void SpriteRenderer::Update() {
	}

	void SpriteRenderer::LateUpdate() {
	}

	void SpriteRenderer::Render() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (tr)
			tr->Bind();

		if (mMesh)
			mMesh->Bind();

		if (mMaterial)
			mMaterial->BindShader();

		if (mSprite)
			mSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

		if (mMesh)
			graphics::GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);
	}



}