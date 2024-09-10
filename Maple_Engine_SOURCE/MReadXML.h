#pragma once
#include <tinyxml2.h>
#include "CommonInclude.h"
#include "..\\Maple_Engine_Windows\\MTile.h"
#include "..\\Maple_Engine_Windows\\MMapObject.h"

namespace maple {

	class ReadXML {

	public:
		ReadXML();
		~ReadXML();

		void LoadXML(const std::wstring& path);
		void CreateTileMap(std::map<std::wstring, std::vector<Tile*>>& tileMap);
		void CreateMapObject(std::map<std::wstring, std::vector<MapObject*>>& mapObjects);

		void LoadBossMonster(const std::wstring& path, GameObject* bossMonster);

		std::wstring ConvertToWString(const std::string& str) {
			std::wstring wstr(str.begin(), str.end());
			return wstr;
		}

	private:
		tinyxml2::XMLDocument mDoc;

	};



}

