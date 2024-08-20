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
		, mAnimationFrame({})
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}

	Animation::~Animation() {
	}

	HRESULT Animation::Save(const std::wstring& path) {
		return E_NOTIMPL;
	}

	HRESULT Animation::Load(const std::wstring& path) {
		return E_NOTIMPL;
	}

	void Animation::Update() {
		if (mbComplete) {
			return;
		}
		mTime += Time::DeltaTime();

		if (mAnimationFrame[mIndex].duration < mTime) {
			mTime = 0;
			if (mIndex < mAnimationFrame.size()-1) {
				mAnimator->GetOwner()->GetComponent<SpriteRenderer>()->SetSprite(mAnimationFrame[mIndex].texture);
				//mSpriteRenderer->SetSprite(mAnimationFrame[mIndex].texture);
				mIndex++;
			} else {
				mbComplete = true;
			}
		}
	}

	void Animation::Render() {
		// 알파블렌드를 쓸수 있는 조건 : 해당이미지 알파채널이 있어야 함
		if (mTexture == nullptr) {
			return;
		}

	}

	void Animation::CreateAnimation(std::vector<Sprite>& animationFrame, SpriteRenderer* spriteRenderer) {
		mSpriteRenderer = spriteRenderer;
		mAnimationFrame.resize(animationFrame.size());
		for (size_t i = 0; i < animationFrame.size(); i++) {
			mAnimationFrame[i] = animationFrame[i];
		}
		int a = 0;
	}

	void Animation::Reset() {
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

}
