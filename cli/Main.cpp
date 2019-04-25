#include <iostream>
#include <filesystem>
#include "include/CS.h"
int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cout << "Help: cli.exe [file.zip] [files]";
		return -1;
	}
	cs::zipper zip;
	for (int i = 2; i < argc; i++) {
		zip.add(argv[i]);
	}
	zip.setWhileCompressJob([&zip]() {
		std::cout << "Archiving " << zip.getCurrFile() << "\n";
		std::cout << "Progress: " << zip.getProgress() << std::endl;
	});
	std::string zipPath(argv[1]);
	if (zip.compress(zipPath, true)) {
		std::cout << "compressed Size: " << zip.getFinalSize() / 1024/1024 << "MBs" << std::endl;
		std::cout << "Original Size: " << zip.getOriginalSize() /1024/1024 << "MBs" << std::endl;
		std::cout << "Files in Zip: \n";
		std::cout << "\n\nWithout pattern\n";
		for (std::string str : zip.listArchive(zipPath)) {
			std::cout << str << std::endl;
		}
		std::cout << "\n\nWith pattern \n";
		for (std::string str : zip.listArchive(zipPath, "c*"))
			std::cout << str << std::endl;
		if (zip.decompress(zipPath, "test_decomp"))
			return 0;
		return -1;
	}
}