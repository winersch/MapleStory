#pragma once
#include <tinyxml2.h>
#include "CommonInclude.h"
#include "..\\Maple_Engine_Windows\\MTile.h"
#include "..\\Maple_Engine_Windows\\MMapObject.h"
#include "MAnimator.h"
#include "..\\Maple_Engine_Windows\\MSkillManager.h"
#include "..\\Maple_Engine_Windows\\MBackGroundObject.h"

namespace maple {

	class ReadXML {

	public:
		ReadXML();
		~ReadXML();

		void LoadXML(const std::wstring& path);
		void CreateTileMap(std::map<std::wstring, std::vector<Tile*>>& tileMap);

		void CreateBackGround(std::map<std::wstring, std::vector<BackGroundObject*>>& backGroundObjectMap);


		void CreateMapObject(std::map<std::wstring, std::vector<MapObject*>>& mapObjects);

		void LoadBossMonster(const std::wstring& path, GameObject* bossMonster);

		void LoadSkill(const std::wstring& path, SkillManager* skillManager);


		std::wstring ConvertToWString(const std::string& str) {
			std::wstring wstr(str.begin(), str.end());
			return wstr;
		}

	private:
		tinyxml2::XMLDocument mDoc;

	};



}

