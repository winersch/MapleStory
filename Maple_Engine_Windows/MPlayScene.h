#pragma once
#include "..\\Maple_Engine_SOURCE\\MScene.h"
#include "..\\Maple_Engine_SOURCE\\MTexture.h"
//#include "..\\Maple_Engine_Windows\Contents\MPlayer.h"
#include "MTile.h"

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

		void LoadTileMap(const std::wstring& path);

	private:
		class Player* mPlayer;
		std::map<std::wstring, GameObject*> mGameObjects;
		std::map<std::wstring, std::vector<Tile*>> mTileMap;
		float mTime;
	};

}



