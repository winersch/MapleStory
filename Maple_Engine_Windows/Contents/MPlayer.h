#pragma once
#include "..\\Maple_Engine_SOURCE\MGameObject.h"

namespace maple {


	class Player : public GameObject{
	public:

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;


	private:

	};

}


