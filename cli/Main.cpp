#include <iostream>
#include "Utils.h"
int main(int argc, char **argv) {
	cs::zipper zip;
	std::string zipPath;
#ifdef  CS_PLATFORM_WINDOWS
	zip.addFile("C:\\dev\\CompressStudio\\CMakeLists.txt");
	zip.addFile("C:\\dev\\CompressStudio\\README.md");
	zipPath = "C:\\dev\\CompressStudio\\build\\test.zip";
#endif //  CS_PLATFORM_WINDOWS
#ifdef CS_PLATFORM_LINUX
	zip.addFile("~/CompressStudio/CMakeLists.txt");
	zip.addFile("~/CompressStudio/README.md");
	zipPath = "~/CompressStudio/test.zip";
#endif // CS_PLATFORM_LINUX

	if (zip.compress(zipPath, true))
		return 0;
	else
		return -1;
}