#include "MAnimator.h"
#include "MTexture.h"
#include "MResources.h"
#include "MReadXML.h"
#include <regex>

namespace maple {



	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		, mAnimations{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
		, mEvents{}
	{
	}

	Animator::~Animator() {
		for (auto& iter : mEvents) {
			delete iter.second;
			iter.second = nullptr;
		}
		for (auto& iter : mAnimations) {
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void Animator::Initialize() {
	}

	void Animator::Update() {
		if (mActiveAnimation) {
			mActiveAnimation->Update();
			Events* events = FindEvents(mActiveAnimation->GetName());

			if (mActiveAnimation->IsCompleted() == true) {
				if (events) {
					events->CompleteEvent();
				}
				if (mbLoop == true) {
					mActiveAnimation->Reset();
				}
			}
		}
	}

	void Animator::LateUpdate() {
	}

	void Animator::Render() {
		//if (mActiveAnimation) {
		//	mActiveAnimation->Render();
		//}
	}

	void Animator::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration) {
		//Animation* animation = nullptr;
		//animation = FindAnimation(name);
		//if (animation != nullptr) {
		//	return;
		//}
		//animation = new Animation();
		//animation->SetName(name);
		//animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);
		//animation->SetAnimator(this);

		//Events* events = new Events();
		//mEvents.insert(std::make_pair(name, events));

		//mAnimations.insert(std::make_pair(name, animation));

	}

	void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path) {
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr) {
			return;
		}

		animation = new Animation();
		animation->SetName(name);
		animation->SetAnimator(this);

		std::filesystem::path fs(path);
		std::vector<std::pair<int,Animation::Sprite>> sprites = {};

		for (auto& p : std::filesystem::recursive_directory_iterator(fs)) {
			std::wstring fileName = p.path();
			std::wstring fullName = p.path();
			Animation::Sprite sprite = {};

			std::wregex pattern(LR"((\d+)_(\d+))");
			std::wsmatch match;
			float duration = 0.0f;
			int start, end;
			if (std::regex_search(fileName, match, pattern)) {
				start = std::stoi(match[1].str());
				end = std::stoi(match[2].str());
				duration = (end - start) / 1000.0f;
			}

			graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);
			sprite.texture = texture;
			sprite.duration = duration;
			sprites.push_back(std::make_pair(start,sprite));
		}
		std::sort(sprites.begin(), sprites.end(), [](const std::pair<int, Animation::Sprite>& a, const std::pair<int, Animation::Sprite>& b) {
			return a.first < b.first;
			});

		animation->CreateAnimation(sprites);

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
		mAnimations.insert(make_pair(name,animation));

	}

	void Animator::CreateAnimationWithOffset(const std::wstring& name, std::vector<std::wstring>& path, std::vector<float>& duration, std::vector<Vector3>& offset
		, std::vector<std::vector<Animation::Hitbox>> hitboxes, std::vector<bool> hide) {

		Animation* animation = nullptr;

		animation = new Animation();
		animation->SetName(name);
		animation->SetAnimator(this);

		std::vector<std::pair<int, Animation::Sprite>> sprites = {};

		for (size_t i = 0; i < path.size(); i++) {
			graphics::Texture* texture = Resources::Load<graphics::Texture>(path[i], path[i]);
			Animation::Sprite sprite = {};
			sprite.texture = texture;
			sprite.duration = duration[i];
			sprites.push_back(std::make_pair(i, sprite));
		}

		animation->CreateAnimation(sprites);
		animation->SetOffset(offset);
		animation->SetHide(hide);
		animation->SetHitboxes(hitboxes);
		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
		mAnimations.insert(make_pair(name, animation));
	}

	void Animator::CreateAnimationWithOffset(const std::wstring& name, std::vector<std::wstring>& path, std::vector<float>& duration, std::vector<Vector3>& offset) {
		Animation* animation = nullptr;

		animation = new Animation();
		animation->SetName(name);
		animation->SetAnimator(this);

		std::vector<std::pair<int, Animation::Sprite>> sprites = {};

		for (size_t i = 0; i < path.size(); i++) {
			graphics::Texture* texture = Resources::Load<graphics::Texture>(path[i], path[i]);
			Animation::Sprite sprite = {};
			sprite.texture = texture;
			sprite.duration = duration[i];
			sprites.push_back(std::make_pair(i, sprite));
		}

		animation->CreateAnimation(sprites);
		animation->SetOffset(offset);
		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
		mAnimations.insert(make_pair(name, animation));
	}

	Animation* Animator::FindAnimation(const std::wstring& name) {
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end()) {
			return nullptr;
		}

		return iter->second;
	}

	void Animator::AddAnimation(const std::wstring& name, Animation* animation) {
		mAnimations.insert(std::make_pair(name, animation));
		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop, bool flip) {
		Animation* animation = FindAnimation(name);
		if (animation == nullptr) {
			return;
		}
		mActiveAnimationName = name;
		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mActiveAnimation->setFlip(flip);
		mbLoop = loop;
		Events* currentEvents = FindEvents(mActiveAnimation->GetName());
		if (currentEvents) {
			currentEvents->EndEvent();
		}
		Events* nextEvents = FindEvents(mActiveAnimation->GetName());
		if (nextEvents) {
			nextEvents->StartEvent();
		}
	}
	void Animator::PlayAnimation(Animation* animation, bool loop, bool flip) {
		if (animation == nullptr) {
			return;
		}
		mActiveAnimationName = animation->GetName();
		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mActiveAnimation->setFlip(flip);
		mbLoop = loop;
		Events* currentEvents = FindEvents(mActiveAnimation->GetName());
		if (currentEvents) {
			currentEvents->EndEvent();
		}
		Events* nextEvents = FindEvents(mActiveAnimation->GetName());
		if (nextEvents) {
			nextEvents->StartEvent();
		}
	}

	void Animator::StopAnimation() {
		if (mActiveAnimation) {
			// 현재 애니메이션의 완료 이벤트 호출
			Events* events = FindEvents(mActiveAnimation->GetName());
			if (events) {
				events->EndEvent();
			}

			// 애니메이션 중단
			mActiveAnimation->Reset();
			mActiveAnimation->SetComplete(true);
			mbLoop = false;
		}
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name) {
		auto iter = mEvents.find(name);
		if (iter == mEvents.end()) {
			return nullptr;
		}

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name) {
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->StartEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name) {
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->CompleteEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name) {
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->EndEvent.mEvent;
	}

}