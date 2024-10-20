#pragma once
#include "..\\Maple_Engine_SOURCE\\MScene.h"
#include "..\\Maple_Engine_SOURCE\\MTexture.h"
#include "MTile.h"
#include "MMapObject.h"
#include "MBackGroundObject.h"
#include "MAudioSource.h"
#include "MPlayer.h"

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
		void LoadBackGround(const std::wstring& path);
		void LoadMapObject(const std::wstring& path);
		void LoadBossMonster(const std::wstring& path);

		GameObject* GetGameObject(const std::wstring& name) { return mGameObjects[name]; }

	private:
		Player* mPlayer;
		std::map<std::wstring, GameObject*> mGameObjects;
		std::map<std::wstring, std::vector<Tile*>> mTileMap;
		std::map<std::wstring, std::vector<BackGroundObject*>> mBackGroundObjects;
		std::map<std::wstring, std::vector<MapObject*>> mMapObjects;
		float mTime;
	};

}



