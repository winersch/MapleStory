#pragma once
#include "MTexture.h"
#include "MResource.h"
#include "MSpriteRenderer.h"

namespace maple {

	class Animation : public Resource{

	public:
		struct Sprite {
			graphics::Texture* texture;
			float duration;

			Sprite()
				: texture(nullptr)
				, duration(0.0f)
			{

			}

		};
		Animation();
		~Animation();

		virtual HRESULT Save(const std::wstring& path) override;
		virtual HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render();


		void CreateAnimation(std::vector<std::pair<int, Animation::Sprite>>& animationFrame);

		void Reset();

		bool IsCompleted() const { return mbComplete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator; }


	private:
		class Animator* mAnimator;
		graphics::Texture* mTexture;
		SpriteRenderer* mSpriteRenderer;

		std::vector<Sprite> mAnimationFrame;
		int mIndex;
		float mTime;
		bool mbComplete;
	};

}

