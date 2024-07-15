#pragma once
#include "MApplication.h"
#include "MInput.h"
#include "MTime.h"
#include "MSceneManager.h"
#include "MResources.h"
#include "MCollisionManager.h"
#include "MUIManager.h"
#include "MFmod.h"
#include "MRenderer.h"

namespace maple {
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(nullptr)
		, mBackBitmap(nullptr)
		, mbLoaded(false)
	{

	}
	Application::~Application() {
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height) {
		
		AdjustWindowRect(hwnd, width, height);
		InitializeEtc();

		mGraphicDevice = std::make_unique<graphics::GraphicDevice_DX11>();
		//renderer::Initialize();
		mGraphicDevice->Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();

	}

	void Application::AdjustWindowRect(HWND hwnd, UINT width, UINT height) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::InitializeEtc() {
		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run() {
		if (mbLoaded == false)
			mbLoaded = true;
		Update();
		LateUpdate();
		Render();
		Destroy();
	}
	void Application::Update() {
		Input::Update();
		Time::Update();
		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();

	}
	void Application::LateUpdate() {
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render() {
		graphics::GetDevice()->ClearRenderTargetView();
		graphics::GetDevice()->ClearDepthStencilView();
		graphics::GetDevice()->BindViewPort();
		graphics::GetDevice()->BindDefaultRenderTarget();

		Time::Render();
		CollisionManager::Render();
		UIManager::Render();
		SceneManager::Render();

		graphics::GetDevice()->Present();
	}

	void Application::Destroy() {
		SceneManager::Destroy();
	}

	void Application::Release() {
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();
		renderer::Release();
	}

	
}

