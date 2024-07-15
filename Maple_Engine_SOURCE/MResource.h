#pragma once
#include "MEntity.h"

namespace maple {

	class Resource : public Entity{ // �޸��Ҵ� X only ���

	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		// ���������Լ��� �ϳ��� �� �ִ� Ŭ������ abstract class
		virtual HRESULT Load(const std::wstring& path) = 0; // ���������Լ� �����޸� �Ҵ� �Ұ������� ������ ������� ���

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		enums::eResourceType mType;
		std::wstring mPath;

	};

	
}

