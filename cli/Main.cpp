#include <iostream>
#include "Utils.h"
int main(int argc, char **argv) {
	cs::zipper zip;
	zip.addFile("C:\\dev\\CompressStudio\\CMakeLists.txt");
	zip.addFile("C:\\dev\\CompressStudio\\README.md");
	return zip.compress(std::string("C:\\dev\\CompressedStudio\\CS.zip"));
}