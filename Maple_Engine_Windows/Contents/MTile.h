#pragma once
#include "..\\Maple_Engine_SOURCE\\\MGameObject.h"

namespace maple {

	class Tile : public GameObject {
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		
	private:
	};

}


