#include "MReadXML.h"
#include "MSpriteRenderer.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MObject.h"
#include "MAnimator.h"


namespace maple {


	ReadXML::ReadXML()
		:mDoc() {
	}

	ReadXML::~ReadXML() {
		mDoc.Clear();
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


			// 각 int32와 string 태그의 값을 읽음
			for (tinyxml2::XMLElement* child = dirElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
				std::string elementName = child->Name();
				if (elementName == "int32") {
					std::string nameAttr = child->Attribute("name");
					if (nameAttr == "x") {
						child->QueryIntAttribute("value", &x);
					}
					else if (nameAttr == "y") {
						child->QueryIntAttribute("value", &y);
					}
					else if (nameAttr == "no") {
						child->QueryIntAttribute("value", &no);
					}
				}
				else if (elementName == "string" && std::string(child->Attribute("name")) == "u") {
					uValue = std::wstring(child->Attribute("value"), child->Attribute("value") + std::strlen(child->Attribute("value")));
				}
			}
			// Tile 객체 생성
			Tile* tile = object::Instantiate<Tile>(enums::eLayerType::Floor);
			tile->Initialize(uValue, x, y, no);

			// map에 Tile 추가
			tileMap[uValue].push_back(tile);
		}
	}
	void ReadXML::CreateMapObject(std::map<std::wstring, std::vector<MapObject*>>& mapObjects) {

		tinyxml2::XMLElement* root = mDoc.FirstChildElement("dir");

		if (!root || std::string(root->Attribute("name")) != "obj") {
			return;
		}
		int x = 0, y = 0;
		std::wstring oS, l0, l1, l2;
		for (tinyxml2::XMLElement* dirElement = root->FirstChildElement("dir"); dirElement != nullptr; dirElement = dirElement->NextSiblingElement("dir")) {
			const char* dirName = dirElement->Attribute("name");


			// 각 int32와 string 태그의 값을 읽음
			for (tinyxml2::XMLElement* child = dirElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
				std::string elementName = child->Name();
				if (elementName == "int32") {
					std::string nameAttr = child->Attribute("name");
					if (nameAttr == "x") {
						child->QueryIntAttribute("value", &x);
					}
					else if (nameAttr == "y") {
						child->QueryIntAttribute("value", &y);
					}
				}
				else if (elementName == "string" && std::string(child->Attribute("name")) == "oS") {
					oS = std::wstring(child->Attribute("value"), child->Attribute("value") + std::strlen(child->Attribute("value")));
				}
				else if (elementName == "string" && std::string(child->Attribute("name")) == "l0") {
					l0 = std::wstring(child->Attribute("value"), child->Attribute("value") + std::strlen(child->Attribute("value")));
				}
				else if (elementName == "string" && std::string(child->Attribute("name")) == "l1") {
					l1 = std::wstring(child->Attribute("value"), child->Attribute("value") + std::strlen(child->Attribute("value")));
				}
				else if (elementName == "string" && std::string(child->Attribute("name")) == "l2") {
					l2 = std::wstring(child->Attribute("value"), child->Attribute("value") + std::strlen(child->Attribute("value")));
				}
			}
			std::wstring path;
			if (l1 == L"torch") {
				path = oS + L"\\" + l0 + L"\\" + l1 + L"\\" + l2;
			}
			else {
				path = oS + L"\\" + l0 + L"\\" + l1 + L"\\" + l2 + L".png";
			}
			// mapObject 객체 생성
			MapObject* mapObject = object::Instantiate<MapObject>(enums::eLayerType::Object);
			mapObject->Initialize(path, x, y);


			// map에 mapObject 추가
			mapObjects[path].push_back(mapObject);
		}
	}
	void ReadXML::LoadBossMonster(const std::wstring& path, GameObject* bossMonster) {

		tinyxml2::XMLElement* root = mDoc.FirstChildElement("dir");
		Animator* animator = bossMonster->GetComponent<Animator>();

		if (animator == nullptr) {
			animator = bossMonster->AddComponent<Animator>();
		}

		if (!root) {
			return;
		}

		for (tinyxml2::XMLElement* dirElement = root->FirstChildElement("dir"); dirElement != nullptr; dirElement = dirElement->NextSiblingElement("dir")) {
			const char* dirName = dirElement->Attribute("name");
			// info 태그의 값을 읽음
			if (strcmp(dirName, "info") == 0) {
				for (tinyxml2::XMLElement* child = dirElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {

				}
			}
			// 나머지 태그의 값을 읽음
			else {
				std::vector<float> duration;
				std::vector<std::wstring> path;
				std::vector<Vector3> offset;
				std::vector<std::vector<Animation::Hitbox>> hitboxes;
				std::vector<bool> hide;

				for (tinyxml2::XMLElement* child = dirElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
					std::string elementName = child->Attribute("name");
					std::vector<Animation::Hitbox> hitbox;
					bool tmpHide = false;
					Vector3 lt, rb;

					// info 태그의 값을 읽음
					if (elementName == "info") {

					}
					// 나머지 태그의 값을 읽어 애니메이션을 생성
					else {
						for (tinyxml2::XMLElement* childNext = child->FirstChildElement(); childNext != nullptr; childNext = childNext->NextSiblingElement()) {
							std::string elementNameNext = childNext->Attribute("name");
							if (elementNameNext == "origin") {
								Vector3 tmpOffset;
								std::string tmpOffsetStr = childNext->Attribute("value");
								size_t pos = tmpOffsetStr.find(',');
								tmpOffset.x = std::stoi(tmpOffsetStr.substr(0, pos));
								tmpOffset.y = -std::stoi(tmpOffsetStr.substr(pos + 1));
								offset.push_back(tmpOffset);
							}
							else if (elementNameNext == "lt") {
								std::string tmpOffsetStr = childNext->Attribute("value");
								size_t pos = tmpOffsetStr.find(',');
								lt.x = std::stoi(tmpOffsetStr.substr(0, pos));
								lt.y = -std::stoi(tmpOffsetStr.substr(pos + 1));
							}
							else if (elementNameNext == "rb") {
								std::string tmpOffsetStr = childNext->Attribute("value");
								size_t pos = tmpOffsetStr.find(',');
								rb.x = std::stoi(tmpOffsetStr.substr(0, pos));
								rb.y = -std::stoi(tmpOffsetStr.substr(pos + 1));
							}
							else if (elementNameNext == "delay") {
								int tmp = std::stoi(childNext->Attribute("value"));
								duration.push_back(tmp / 1000.0f);
							}
							else if (elementNameNext == "_outlink") {
								path.push_back(ConvertToWString(childNext->Attribute("value")) + L".png");
							}
							//else if (elementNameNext == "multiRect") {
							//	for (tinyxml2::XMLElement* multiRectElement = childNext->FirstChildElement("dir"); multiRectElement != nullptr; multiRectElement = multiRectElement->NextSiblingElement("dir")) {
							//		Vector3 lt, rb;

							//		for (tinyxml2::XMLElement* vectorElement = multiRectElement->FirstChildElement("vector"); vectorElement != nullptr; vectorElement = vectorElement->NextSiblingElement("vector")) {
							//			std::string vectorName = vectorElement->Attribute("name");
							//			std::string vectorValue = vectorElement->Attribute("value");

							//			// 좌표값을 파싱
							//			size_t pos = vectorValue.find(',');
							//			float x = std::stof(vectorValue.substr(0, pos));
							//			float y = std::stof(vectorValue.substr(pos + 1));

							//			if (vectorName == "lt") {
							//				lt = Vector3(x, y, 0);  // 좌측 상단 좌표
							//			}
							//			else if (vectorName == "rb") {
							//				rb = Vector3(x, y, 0);  // 우측 하단 좌표
							//			}
							//		}
							//		hitbox.push_back(Animation::Hitbox(lt, rb));
							//	}

							//}
							else if (elementNameNext == "hide") {
								tmpHide = true;
							}
						}
						if (lt == Vector3::Zero) {
							hitbox.push_back(Animation::Hitbox());
						}
						else {
							hitbox.push_back(Animation::Hitbox(lt, rb));
						}
						hitboxes.push_back(hitbox);
						hide.push_back(tmpHide);
					}

				}
				animator->CreateAnimationWithOffset(ConvertToWString(dirName), path, duration, offset, hitboxes, hide);
			}


		}


	}
}


