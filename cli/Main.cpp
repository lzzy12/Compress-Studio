#include <iostream>
#include "Utils.h"
int main(int argc, char **argv) {
	cs::zipper zip;
	std::cout << zip.compress();
	std::cin.ignore();
}