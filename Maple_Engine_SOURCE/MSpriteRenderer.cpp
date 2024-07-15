#include "MSpriteRenderer.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MTexture.h"
#include "MRenderer.h"
#include "MCamera.h"

namespace maple {
	using namespace math;
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::SpriteRenderer)
		, mTexture(nullptr)
		, mSize(Vector2::One){
	}

	SpriteRenderer::~SpriteRenderer() {
	}

	void SpriteRenderer::Initialize() {
	}

	void SpriteRenderer::Update() {
	}

	void SpriteRenderer::LateUpdate() {
	}

	void SpriteRenderer::Render(HDC hdc) {
		/*
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));*/

		if (mTexture == nullptr) { // 텍스처 세팅
			assert(false);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		pos = renderer::mainCamera->CalculatePosition(pos);
		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {


			if (mTexture->IsAlpha()) {
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc
					, pos.x
					, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc()
					, 0, 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, func);
			} else {
				//https://blog.naver.com/power2845/50147965306
				TransparentBlt(hdc
					, pos.x, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc()
					, 0, 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, RGB(255, 0, 255));
			}
		}

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {
			// 내가 원하는 픽셀을 투명화 시킬 때
			Gdiplus::ImageAttributes imgAtt = {};

			// 투명화 시킬 픽셀의 색 범위
			imgAtt.SetColorKey(Gdiplus::Color(0, 0, 0), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(mTexture->GetImage(),
				Gdiplus::Rect(
					pos.x, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
				)
				, 0
				, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, Gdiplus::UnitPixel
				, &imgAtt
			);

		}

	}



}