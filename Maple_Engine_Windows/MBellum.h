#pragma once
#include "MGameObject.h"

namespace maple {
	
	class Bellum : public GameObject{

	public:
		Bellum();
		~Bellum();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;	



	};
}


