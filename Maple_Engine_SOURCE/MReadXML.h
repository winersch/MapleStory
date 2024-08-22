#pragma once
#include <tinyxml2.h>
#include "CommonInclude.h"
#include "..\\Maple_Engine_Windows\\MTile.h"


namespace maple {

	class ReadXML {

	public:
		ReadXML();
		~ReadXML();

		void LoadXML(const std::wstring& path);
		void CreateTileMap(std::map<std::wstring, std::vector<Tile*>>& tileMap);

	private:
		tinyxml2::XMLDocument mDoc;

	};



}

