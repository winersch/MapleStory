#pragma once
#include "mComponent.h" 


namespace maple {


	class Skill{

	public:

		enum class eSkillType {
			Active,
			Passive,
			None,
		};

		Skill();
		~Skill();
		
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetSkillType(eSkillType type) { mSkillType = type; }
		eSkillType GetSkillType() { return mSkillType; }

	private:
		eSkillType mSkillType;


	};

}

