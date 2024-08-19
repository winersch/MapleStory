#pragma once
#include <tinyxml2.h>
#include "CommonInclude.h"



namespace maple {

	class ReadXML {

	public:
		ReadXML();
		~ReadXML();



	private:
		tinyxml2::XMLDocument mDoc;

	};



}

