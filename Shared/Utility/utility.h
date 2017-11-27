#ifndef _GO_UTILITY
#define _GO_UTILITY

#include "../ExternalDefines.h"

#include <string>
#include <vector>
#include <cstdlib>

#ifdef __LINUX__
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#endif

namespace utility
{
	bool sscanf(const std::string &params, const std::string &command, std::vector<std::string> &elements);
	std::string RGBtoHex(int r, int g, int b);
	void HextoRGB(const char *colorHex, int *r, int *g, int *b);
	void splitString(const std::string &text, const std::string &delim, std::vector<std::string> &splited);
};

#ifdef __LINUX__
unsigned GetTickCount();
#endif

#endif //_GO_MATH_H
