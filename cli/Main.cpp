#include <iostream>
#include "Utils.h"
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
	zip.setPreCompressJob([&zip]() {
		std::cout << "Archiving " << zip.getCurrFile() << "\n";
	});
	std::string zipPath(argv[1]);
	if (zip.compress(zipPath, true)) {
		std::cout << "compressed \n";
		if (zip.decompress(zipPath, "test_decomp"))
			return 0;
		return -1;
	}
}