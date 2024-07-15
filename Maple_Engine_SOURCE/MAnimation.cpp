#include "MAnimation.h"
#include "MTime.h"
#include "MTransform.h"
#include "MAnimator.h"
#include "MGameObject.h"
#include "MRenderer.h"
#include "MCamera.h"

namespace maple {

	Animation::Animation() 
		: Resource(enums::eResourceType::Animation)
		, mAnimator(nullptr)
		, mTexture(nullptr)
		, mAnimationSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}

	Animation::~Animation() {
	}

	HRESULT Animation::Load(const std::wstring& path) {
		return E_NOTIMPL;
	}

	void Animation::Update() {
		if (mbComplete) {
			return;
		}
		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime) {
			mTime = 0;
			if (mIndex < mAnimationSheet.size()-1) {
				mIndex++;
			} else {
				mbComplete = true;
			}
		}
	}

	void Animation::Render(HDC hdc) {
		// 알파블렌드를 쓸수 있는 조건 : 해당이미지 알파채널이 있어야 함
		if (mTexture == nullptr) {
			return;
		}

		GameObject* gameobj = mAnimator->GetOwner();
		Transform* tr = gameobj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera) {
			pos = renderer::mainCamera->CalculatePosition(pos);
		}
		Sprite sprite = mAnimationSheet[mIndex];

		graphics::Texture::eTextureType textureType = mTexture->GetTextureType();

		if (textureType == graphics::Texture::eTextureType::Bmp) {
			

			HDC imgHdc = mTexture->GetHdc();

			if (mTexture->IsAlpha()) {
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0 (tarnsparend) ~ 255(Opaque)

				AlphaBlend(hdc
					, pos.x - (sprite.size.x / 2.0f) + sprite.offset.x
					, pos.y - (sprite.size.y / 2.0f) + sprite.offset.y
					, sprite.size.x * scale.x
					, sprite.size.y * scale.y
					, imgHdc
					, sprite.leftTop.x
					, sprite.leftTop.y
					, sprite.size.x
					, sprite.size.y
					, func);
			} else {
				TransparentBlt(hdc
					, pos.x - (sprite.size.x / 2.0f) + sprite.offset.x
					, pos.y - (sprite.size.y / 2.0f) + sprite.offset.y
					, sprite.size.x * scale.x
					, sprite.size.y * scale.y
					, imgHdc
					, sprite.leftTop.x
					, sprite.leftTop.y
					, sprite.size.x
					, sprite.size.y
					, RGB(255, 0, 255));
			}
		}

		if (textureType == graphics::Texture::eTextureType::Png) {
			// 내가 원하는 픽셀을 투명화 시킬 때
			Gdiplus::ImageAttributes imgAtt = {};

			// 투명화 시킬 픽셀의 색 범위
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(mTexture->GetImage(),
				Gdiplus::Rect(
					  pos.x - (sprite.size.x / 2.0f)
                    , pos.y - (sprite.size.y / 2.0f)
                    , sprite.size.x * scale.x
                    , sprite.size.y * scale.y
				)
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.size.x
				, sprite.size.y
				, Gdiplus::UnitPixel
				, &imgAtt//nullptr
			);


		}

		Rectangle(hdc, pos.x, pos.y, pos.x + 10, pos.y + 10);

	}

	void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration) {
		mTexture = spriteSheet;
		for (size_t i = 0; i < spriteLength; i++) {
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Reset() {
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

}
