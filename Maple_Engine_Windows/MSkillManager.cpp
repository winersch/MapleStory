#include "MSkillManager.h"
#include "MObject.h"
#include "MTransform.h"

namespace maple {

	SkillManager::SkillManager()
		: Component(enums::eComponentType::SkillManager)
		, mSkills{}
		, mActiveSkills{} {
		mSkillObjectPool = new SkillObjectPool(100);
		mAnimator = new Animator();
	}

	SkillManager::~SkillManager() {
		//delete mSkillObjectPool;
		//for (auto& iter : mSkills) {
		//	if (iter.second == nullptr) {
		//		continue;
		//	}
		//	delete iter.second;
		//	iter.second = nullptr;
		//}
		//for (auto& iter : mActiveSkills) {
		//	if (iter == nullptr) {
		//		continue;
		//	}
		//	delete iter;
		//	iter = nullptr;
		//}
		//mSkills.clear();
		//mActiveSkills.clear();
	}

	void SkillManager::Initialize() {
	}

	void SkillManager::Update() {
		for (auto& iter : mActiveSkills) {
			iter->Update();
		}
	}

	void SkillManager::LateUpdate() {
	}

	void SkillManager::Render() {
	}

	void SkillManager::AddSkill(std::wstring& name, Skill* skill) {
		mSkills.insert(std::make_pair(name, skill));
	}

	void SkillManager::PlayAnimation(std::wstring name, bool loop, bool flip) {
		GameObject* object = mSkillObjectPool->GetObjectW();
		object->AddComponent<SpriteRenderer>();
		Animator* animator = object->AddComponent<Animator>();
		Animation* animation = mAnimator->GetAnimation(name);
		animation->SetFixedPos(true);
		animation->SetOriginPos(GetOwner()->GetComponent<Transform>()->GetPosition());
		animation->SetAnimator(animator);
		animator->AddAnimation(name, animation);

		animator->GetCompleteEvent(name) = [object]() {
			object->SetActive(false);
			};

		animator->PlayAnimation(name, loop, flip);
	}

}