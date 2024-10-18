#pragma once
#include "MResource.h"
#include <filesystem>



namespace maple {

	class Resources {

	public:
		template <typename T>
		static T* Find(const std::wstring& key) {
			auto iter = mResources.find(key);
			if (iter == mResources.end()) {
				return nullptr;
			}
			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path) {
			T* resource = Resources::Find<T>(key);

			if (resource != nullptr) {
				return resource;
			}
			resource = new T();
			if (FAILED(resource -> Load(path))) {
				assert(false);
			}
			resource->SetName(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return resource;
		}

		template <typename T>
		static std::vector<T*> LoadFromFolder(const std::wstring& folderPath) {
			std::vector<T*> loadedResources;

			// ���� ��ο� �ִ� ��� ������ ��ȸ
			for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
				if (entry.is_regular_file()) {  // ������ ��쿡�� ó��
					std::wstring filePath = entry.path().wstring();  // ���� ���
					std::wstring fileName = entry.path().stem().wstring();  // ���� �̸�

					// ���� �̸��� key�� ����Ͽ� ���ҽ��� �ε�
					T* resource = Load<T>(fileName, filePath);
					if (resource != nullptr) {
						loadedResources.push_back(resource);  // �ε�� ���ҽ��� ���Ϳ� �߰�
					}
				}
			}
			return loadedResources;
		}


		static void Insert(const std::wstring& key, Resource* resource) {
			if (key == L"") {
				return;
			}
			if (resource == nullptr) {
				return;
			}
			mResources.insert(std::make_pair(key, resource));
		}
		static void Release() {
			for (auto& iter : mResources) {
				delete iter.second;
				iter.second = nullptr;
			}
		}




	private:

		static std::map<std::wstring, Resource*> mResources;


	};

}



