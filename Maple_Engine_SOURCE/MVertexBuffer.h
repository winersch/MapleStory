#pragma once
#include "MGraphicDevice_DX11.h"

namespace maple::graphics {


	class VertexBuffer : public GpuBuffer{
	public:
		VertexBuffer();
		~VertexBuffer();

		bool Create(const std::vector<Vertex>& vertexes);
		void Bind();

	private:

	};

}


