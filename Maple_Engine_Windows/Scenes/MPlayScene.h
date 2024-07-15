#pragma once
#include "..\\Maple_Engine_SOURCE\\MScene.h"
//#include "..\\Maple_Engine_Windows\Contents\MPlayer.h"

namespace maple {


	class PlayScene : public Scene {

	public:
		PlayScene();
		~PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void OnEnter() override;
		void OnExit() override;


	private:
		class Player* mPlayer;

	};

}



