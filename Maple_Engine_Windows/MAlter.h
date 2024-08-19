#pragma once

#include "MGameObject.h"



namespace maple {

	class Alter : public GameObject {

	public:
		Alter();
		~Alter();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;


	};

}


