#pragma once
#include "MScript.h"
#include "MAnimator.h"



namespace maple {

	class AlterScript : public Script{


	public:
		AlterScript();
		~AlterScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		Animator* mAnimator;
	};


}

