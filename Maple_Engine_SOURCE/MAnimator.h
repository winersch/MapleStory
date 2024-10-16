#pragma once
#include "CommonInclude.h"
#include "MComponent.h"
#include "MAnimation.h"

namespace maple {

	class Animator : public Component {

	public:

		struct Event {

			void operator = (std::function<void()> func) {
				mEvent = std::move(func);
			}

			void operator()() {
				if (mEvent) {
					mEvent();
				}
			}

			std::function<void()> mEvent;

		};

		struct Events {
			Event StartEvent;
			Event CompleteEvent;
			Event EndEvent;
		};

		Animator();
		~Animator();


		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, UINT spriteLength
			, float duration);

		void CreateAnimationByFolder(const std::wstring& name
			, const std::wstring& path);
		void CreateAnimationWithOffset(const std::wstring& name
			, std::vector<std::wstring>& path, std::vector<float>& duration, std::vector<Vector3>& offset
			, std::vector<std::vector<Animation::Hitbox>> hitboxes, std::vector<bool> hide);

		void CreateAnimationWithOffset(const std::wstring& name
			, std::vector<std::wstring>& path, std::vector<float>& duration, std::vector<Vector3>& offset);

		Animation* FindAnimation(const std::wstring& name);
		void AddAnimation(const std::wstring& name, Animation* animation);
		void PlayAnimation(const std::wstring& name, bool loop = true, bool flip = false);
		void PlayAnimation(Animation* animation, bool loop = true, bool flip = false);
		void StopAnimation();

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		bool IsCompleted() { return mActiveAnimation->IsCompleted(); }

		Animation* GetActiveAnimation() { return mActiveAnimation; }
		Animation* GetAnimation(const std::wstring& name) { return mAnimations[name]; }
		std::wstring GetActiveAnimationName() { return mActiveAnimationName; }
		std::map<std::wstring, Animation*>& GetAnimations() { return mAnimations; }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		std::wstring mActiveAnimationName;
		bool mbLoop;

		std::map<std::wstring, Events*> mEvents;
	};

}

