#pragma once
#include "MApplication.h"
#include "MInput.h"
#include "MTime.h"
#include "MSceneManager.h"
#include "MResources.h"
#include "MCollisionManager.h"
#include "MUIManager.h"
#include "MFmod.h"

namespace maple {
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(nullptr)
		, mBackBitmap(nullptr)
	{

	}
	Application::~Application() {
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height) {
		
		adjustWindowRect(hwnd, width, height);
		createBuffer(width, height);
		intitializeEct();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();

	}
	void Application::Run() {
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
		clearRenderTarget();
		Time::Render(mBackHdc);

		CollisionManager::Render(mBackHdc);
		UIManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);


		copyRenterTarget(mBackHdc, mHdc);
	}

	void Application::Destroy() {
		SceneManager::Destroy();
	}

	void Application::Release() {
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();
	}

	void Application::clearRenderTarget() {
		//clear
		HBRUSH grayBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);

		Rectangle(mBackHdc, -1, -1, 1601, 901);

		(HBRUSH)SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);

	}

	void Application::copyRenterTarget(HDC source, HDC dest) {
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}
	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height) {
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
		mWidth = width;
		mHeight = height;

		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 30, 30, mWidth, mHeight, 0);
		ShowWindow(mHwnd, true);

	}
	void Application::createBuffer(UINT width, UINT height) {
		// 윈도우 해상도에 맞는 백버퍼(도화지) 생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		// 백버퍼를 가리킬 DC생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}
	void Application::intitializeEct() {

		Input::Initailize();
		Time::Initialize();
	}
}

