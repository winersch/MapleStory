#include "MAnimation.h"
#include "MTime.h"
#include "MTransform.h"
#include "MAnimator.h"
#include "MGameObject.h"
#include "MRenderer.h"
#include "MCamera.h"
#include "MResources.h"

namespace maple {

	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAnimator(nullptr)
		, mTexture(nullptr)
		, mAnimationFrame({})
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		, mbFlip(false)
		, mbFixedFlip(false)
	{
	}

	Animation::~Animation() {
		mAnimationFrame.clear();
		mOffset.clear();
		mHitboxes.clear();
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
		mTime -= Time::DeltaTime();
		Transform* transform = mAnimator->GetOwner()->GetComponent<Transform>();
		if (!mbFixedPos) {
			mOriginPos = transform->GetPosition();
		}
		if (mAnimator->GetActiveAnimationName() == L"FlashJump" || mAnimator->GetActiveAnimationName() == L"KramaFury" || mAnimator->GetActiveAnimationName() == L"PhantomBlow") {
			int a = 0;
		}
		if (mTime <= 0.0001f) {

			if (mIndex <= mAnimationFrame.size() - 1) {
				Texture* texture = mAnimationFrame[mIndex].texture;
				Transform* transform = mAnimator->GetOwner()->GetComponent<Transform>();
				transform->SetScale((float)mAnimationFrame[mIndex].texture->GetWidth(), (float)mAnimationFrame[mIndex].texture->GetHeight(), 0.0f);
				Vector3 rotation = transform->GetRotation();

				if (!mbFixedFlip) {
					if (mbFlip) {
						rotation.y = 180;
						transform->SetRotation(rotation);
					}
					else {
						rotation.y = 0;
						transform->SetRotation(rotation);
					}
				}
				if (mbOffset) {
					Vector3 pos = mOriginPos;
					if (!mbFixedFlip) {
						if (mbFlip) {
							pos.y -= mOffset[mIndex].y;
							pos.x += mOffset[mIndex].x;
							pos.x -= texture->GetWidth() / 2;
						}
						else {
							pos -= mOffset[mIndex];
							pos.x += texture->GetWidth() / 2;
						}
					}
					else {
						pos -= mOffset[mIndex];
						pos.x += texture->GetWidth() / 2;
					}
					pos.y -= texture->GetHeight() / 2;
					transform->SetRenderPos(pos);
				}
				else {
					transform->ResetRenderPos();
				}
				mAnimator->GetOwner()->GetComponent<SpriteRenderer>()->SetSprite(mAnimationFrame[mIndex].texture);
				mTime = mAnimationFrame[mIndex].duration;
				mIndex++;
			}
			else {
				//mAnimator->GetOwner()->GetComponent<Transform>()->ResetRenderPos();
				mbComplete = true;
				//mAnimator->GetOwner()->GetComponent<SpriteRenderer>()->SetSprite(Resources::Find<graphics::Texture>(L"Empty"));
			}
		}
	}

	void Animation::Render() {
		if (mTexture == nullptr) {
			return;
		}

	}

	void Animation::CreateAnimation(std::vector<std::pair<int, Animation::Sprite>>& animationFrame) {
		mAnimationFrame.resize(animationFrame.size());
		for (size_t i = 0; i < animationFrame.size(); i++) {
			mAnimationFrame[i] = animationFrame[i].second;
		}
	}

	void Animation::Reset() {
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

}
