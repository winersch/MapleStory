#pragma once
#include "mComponent.h" 


namespace maple {


	class Skill : public Component{

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

		
	private:
		eSkillType mSkillType;


	};

}

