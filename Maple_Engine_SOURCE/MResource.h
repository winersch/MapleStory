#pragma once
#include "MEntity.h"

namespace maple {

	class Resource : public Entity{ 

	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Save(const std::wstring& path) = 0;
		virtual HRESULT Load(const std::wstring& path) = 0; 

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		enums::eResourceType mType;
		std::wstring mPath;

	};

	
}

