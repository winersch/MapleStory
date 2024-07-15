#pragma once
#include "MGraphicDevice_DX11.h"


namespace maple::graphics {

	class IndexBuffer : public GpuBuffer {
	public:
		IndexBuffer();
		~IndexBuffer();

		bool Create(const std::vector<UINT>& indices);
		void Bind() const;

		UINT GetIndexCount() const { return mIndexCount; }

	private:
		UINT mIndexCount;
	};

}

