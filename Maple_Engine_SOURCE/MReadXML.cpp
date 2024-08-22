#include "MReadXML.h"
#include "MSpriteRenderer.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MObject.h"



namespace maple {


	ReadXML::ReadXML() 
		:mDoc()
	{
	}

	ReadXML::~ReadXML() {
	}

	void ReadXML::LoadXML(const std::wstring& path) {

		int size = WideCharToMultiByte(CP_UTF8, 0, &path[0], (int)path.size(), NULL, 0, NULL, NULL);
		std::string utf8Path(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, &path[0], (int)path.size(), &utf8Path[0], size, NULL, NULL);
		
		tinyxml2::XMLError eResult = mDoc.LoadFile(utf8Path.c_str());
	}

	void ReadXML::CreateTileMap(std::map<std::wstring, std::vector<Tile*>>& tileMap) {
		
		tinyxml2::XMLElement* root = mDoc.FirstChildElement("dir");
		if (!root || std::string(root->Attribute("name")) != "tile") {
			return;
		}
		int x = 0, y = 0, no = 0;
		std::wstring uValue;
		for (tinyxml2::XMLElement* dirElement = root->FirstChildElement("dir"); dirElement != nullptr; dirElement = dirElement->NextSiblingElement("dir")) {
			const char* dirName = dirElement->Attribute("name");
			

			// �� int32�� string �±��� ���� ����
			for (tinyxml2::XMLElement* child = dirElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
				std::string elementName = child->Name();
				if (elementName == "int32") {
					std::string nameAttr = child->Attribute("name");
					if (nameAttr == "x") {
						child->QueryIntAttribute("value", &x);
					}
					else if (nameAttr == "y") {
						child->QueryIntAttribute("value", &y);
					}else if(nameAttr == "no") {
						child->QueryIntAttribute("value", &no);
					}
				}
				else if (elementName == "string" && std::string(child->Attribute("name")) == "u") {
					uValue = std::wstring(child->Attribute("value"), child->Attribute("value") + std::strlen(child->Attribute("value")));
				}
			}
			// Tile ��ü ����
			Tile* tile = object::Instantiate<Tile>(enums::eLayerType::Floor);
			tile->Initialize(uValue, x, y, no);

			// map�� Tile �߰�
			tileMap[uValue].push_back(tile);
		}
	}
}


