#include "utility.h"

bool utility::sscanf(const std::string &params, const std::string &command, std::vector<std::string> &elements)
{
	int splited = 0, begin = 0;
	int pSize = params.size();

	if (pSize == 1)
	{
		elements.push_back(command);
		return true;
	}
	else if (pSize > 1)
		for (int i = 0; i < command.length(); ++i)
			if (command[i] == ' ')
			{
				elements.push_back(command.substr(begin, i - begin));

				if (++splited == params.length() - 1)
				{
					begin = i + 1;

					elements.push_back(command.substr(begin, command.length() - begin));
					return true;
				}

				begin = i + 1;
			}

	return false;
}

std::string utility::RGBtoHex(int r, int g, int b)
{
	if (r > 255 || r < 0) r = 255;
	if (g > 255 || g < 0) r = 255;
	if (b > 255 || b < 0) r = 255;

	char hexColor[16];
	sprintf(hexColor, "%02x%02x%02x", r, g, b);

	return std::string(hexColor);
}

void utility::HextoRGB(const char *colorHex, int *r, int *g, int *b)
{
	char color[7]; // With #
	memcpy(color, colorHex, 7);

	if (color[0] == '#') memmove(color, color + 1, 7);

	int hex = strtol(color, 0, 16);

	*r = hex / 0x10000;
	*g = (hex / 0x100) % 0x100;
	*b = hex % 0x100;
}

void utility::splitString(const std::string &text, const std::string &delim, std::vector<std::string> &splited)
{
	int pos = 0, charPos = text.find(delim);

	while (charPos != std::string::npos)
	{
		splited.push_back(text.substr(pos, charPos - pos));
		pos = ++charPos; charPos = text.find(delim, pos);

		if (charPos == std::string::npos) // End, then copy all
			splited.push_back(text.substr(pos));
	}
}

#ifdef __LINUX__
unsigned GetTickCount()
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL) != 0)
			return 0;

	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
#endif