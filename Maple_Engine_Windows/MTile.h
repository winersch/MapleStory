#pragma once
#include "..\\Maple_Engine_SOURCE\\MGameObject.h"

namespace maple {

	class Tile : public GameObject {
	public:

		Tile();
		~Tile();

		void Initialize() override;
		void Initialize(const std::wstring& name, int x, int y, int no);
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		std::wstring mName;
		int mX;
		int mY;
		int mNo;

	};

}


