#pragma once

#include "..\\Maple_Engine_SOURCE\\MResources.h"
#include "..\\Maple_Engine_SOURCE\\MTexture.h"


namespace maple {

	void LoadResources() {
		Resources::Load<graphics::Texture>(L"Map", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PacMan", L"..\\Resources\\img\\pacman\\0.png");
		Resources::Load<graphics::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"Bubble", L"..\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>(L"Gathering", L"..\\Resources\\gathering.png");
		Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
		Resources::Load<graphics::Texture>(L"PixelMap", L"..\\Resources\\pixelMap.bmp");

	}


}