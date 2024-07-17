#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <wrl/client.h>


namespace maple {

	class MGraphics {
	public:
		MGraphics();
		~MGraphics();

		bool Initialize(HWND hwnd, int screenWidth, int screenHeight);
		void BeginScene(float red, float green, float blue, float alpha);
		void EndScene();
		bool LoadBitmapFromFile(PCWSTR uri);

	private:
		bool InitializeDirect2D(HWND hwnd, int screenWidth, int screenHeight);
		void CleanUp();

	private:
		Microsoft::WRL::ComPtr<ID2D1Factory> d2dFactory;
		Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> renderTarget;
		Microsoft::WRL::ComPtr<IWICImagingFactory> wicFactory;
		Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap;
	};

}
