#pragma once
#include "MGameObject.h"

namespace maple {

	class Tile : public GameObject {
	public:

		Tile();
		~Tile();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		
	private:
	};

}


