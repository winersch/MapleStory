#pragma once
#include "MTexture.h"
#include "MResource.h"
#include "MSpriteRenderer.h"
#include "MAudioClip.h"

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

		struct Hitbox {
			Vector3 lt;  // 좌측 상단 좌표 (left-top)
			Vector3 rb;  // 우측 하단 좌표 (right-bottom)
			bool valid;  // 유효 여부 (히트박스가 존재하는지)

			// 기본값 생성자
			Hitbox() : lt(Vector3(0, 0, 0)), rb(Vector3(0, 0, 0)), valid(false) {}
			Hitbox(Vector3 leftTop, Vector3 rightBottom) : lt(leftTop), rb(rightBottom), valid(true) {}
		};

		Animation();
		~Animation();

		virtual HRESULT Save(const std::wstring& path) override;
		virtual HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render();


		void CreateAnimation(std::vector<std::pair<int, Animation::Sprite>>& animationFrame);
		void SetOffset(std::vector<Vector3>& offset) { mOffset = offset; mbOffset = true; }
		void SetHide(std::vector<bool>& hide) { mbHide = hide; }
		void SetHitboxes(std::vector<std::vector<Hitbox>>& hitboxes) { mHitboxes = hitboxes; }

		bool GetHide(int index) { return mbHide[index]; }
		std::vector<Hitbox>& GetHitboxes(int index) { return mHitboxes[index]; }

		void Reset();

		bool IsCompleted() const { return mbComplete; }
		void SetComplete(bool complete) { mbComplete = complete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator; }
		void setFlip(bool flip) { mbFlip = flip; }
		void setModifyRotation(bool modify) { mbModifyRotation = modify; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
		void SetFixedPos(bool fixed) { mbFixedPos = fixed; }
		void SetOriginPos(Vector3 pos) { mOriginPos = pos; }
		void SetFixedFlip(bool fixed) { mbFixedFlip = fixed; }

		int GetIndex() const { return mIndex; }

	private:
		class Animator* mAnimator;
		graphics::Texture* mTexture;
		GameObject* mOwner;

		std::vector<Sprite> mAnimationFrame;
		std::vector<Vector3> mOffset;
		std::vector<bool> mbHide;
		std::vector<std::vector<Hitbox>> mHitboxes;

		int mIndex;
		float mTime;
		bool mbComplete;
		bool mbFlip;
		bool mbModifyRotation;
		bool mbOffset;
		bool mbFixedPos;
		bool mbFixedFlip;

		Vector3 mOriginPos;

	};

}

