#pragma once
#include "Core.h"
namespace cs {
	class CS_UTIL archive
	{

		/* A base class which will be derived by the classes which will be
		* used to implement different de/compression algorithms
		*/
	protected:
		cs_int originalSize;
		cs_int finalSize;
		cs_int ratio;
	public:
		virtual int compress() = 0;
		virtual int decompress() = 0;
		cs_int getOriginalSize();
		cs_int getFinalSize();
		cs_int getCompressionRatio();
	};

}