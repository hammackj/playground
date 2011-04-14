/*
 * Copyright (c) 2008
 * Evan Teran
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appears in all copies and that both the
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the same name not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission. We make no representations about the
 * suitability this software for any purpose. It is provided "as is"
 * without express or implied warranty.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#include <iomanip>

int main(int argc, char *argv[]) {

	int ret = 0;
	std::vector<std::string> args(argv, argv + argc);
	if(args.size() < 2) {
		std::cerr << "usage: ./bgrep <byte>..." << std::endl;
		ret = -1;
	} else {	
		const size_t count = args.size() - 1;
		uint8_t *pattern = 0; 
		uint8_t *compare = 0; 

		try {
			pattern = new uint8_t[count];
			compare = new uint8_t[count + 1]();

			std::vector<std::string>::iterator i = args.begin() + 1; // skip program name
			uint8_t *p = pattern;
			while(i != args.end()) {
				*p++ = strtoul(i++->c_str(), 0, 16);
			}

			uint32_t offset = 0;

			// we use fread cause std::cin isn't a binary stream and strips certain values
			while(fread(&compare[count], 1, 1, stdin) == 1) {
				for(std::size_t i = 0; i < count; ++i) {
					compare[i] = compare[i + 1];
				}

				if(std::memcmp(pattern, compare, count) == 0) {
					std::cout << "pattern found at " << std::hex << std::setw(8) << std::setfill('0') << (offset - count + 1) << std::endl;
				}
				++offset;
			}
		} catch(const std::bad_alloc &e) {
			std::cerr << e.what() << std::endl;
			ret = -1;
		}

		delete [] pattern;
		delete [] compare;
	}
	return ret;
}
