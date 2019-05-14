#include "idMaker.hpp"

IdMaker::IdMaker()
{
	jeekNumber = 0;
}

std::string IdMaker::getJeekId()
{
	jeekNumber++;
	return "J" + std::to_string(jeekNumber);
}