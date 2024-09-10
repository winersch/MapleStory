#pragma once
#include "..\\Maple_Engine_SOURCE\\MGameObject.h"
#include "..\\Maple_Engine_SOURCE\\MAnimator.h"

namespace maple {

	class MapObject : public GameObject {
	public:

		MapObject();
		~MapObject();

		void Initialize() override;
		void Initialize(const std::wstring& name, int x, int y);
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		std::wstring mName;
		int mX;
		int mY;
		Animator* mAnimator;
		
	};

}


