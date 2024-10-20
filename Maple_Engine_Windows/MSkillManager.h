#pragma once
#include "MComponent.h"
#include "MSkill.h"
#include "CommonInclude.h"
#include "MSkillObjectPool.h"
#include "MAnimator.h"

namespace maple {

	class SkillManager : public Component{

	public:

		SkillManager();
		~SkillManager();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void AddSkill(std::wstring &name, Skill* skill);
		void AddActiveSkill(std::wstring& name) { mActiveSkills.push_back(mSkills[name]); }
		GameObject* PlayAnimation(std::wstring name, bool loop, bool flip = false);
		GameObject* PlayAnimationWithOffset(std::wstring name, bool loop, Vector3 offset, bool flip = false);

		Skill* GetSkill(std::wstring& name) { return mSkills[name]; }

		Animator* GetAnimator() { return mAnimator; }
		std::map<std::wstring, Skill*>& GetSkills() { return mSkills; }

	private:
		std::map<std::wstring, Skill*> mSkills;
		std::vector<Skill*> mActiveSkills;

		Animator* mAnimator;

		SkillObjectPool* mSkillObjectPool;

	};



}

