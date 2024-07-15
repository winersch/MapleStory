#pragma once
#include "MEntity.h"

namespace maple {

	class Resource : public Entity{ // 메모리할당 X only 상속

	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		// 순수가상함수가 하나라도 들어가 있는 클래스는 abstract class
		virtual HRESULT Load(const std::wstring& path) = 0; // 순수가상함수 실제메모리 할당 불가능해짐 무조건 상속으로 사용

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		enums::eResourceType mType;
		std::wstring mPath;

	};

	
}

