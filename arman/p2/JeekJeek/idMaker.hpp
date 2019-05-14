#ifndef __ID_MAKER_H__
#define __ID_MAKER_H__

#include <string>

class IdMaker
{
public:
	IdMaker();
	std::string getJeekId();
private:
	long long unsigned int jeekNumber;
};

#endif