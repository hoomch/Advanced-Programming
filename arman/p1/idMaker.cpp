#include "idMaker.hpp"
using namespace std;

IdMaker::IdMaker()
{
	jeekNumber = 0;
	commentNumber = 0;
	replyNumber = 0;
}

std::string IdMaker::getJeekId()
{
	jeekNumber++;
	return "J" + to_string(jeekNumber);
}

string IdMaker::getCommentId()
{
	commentNumber++;
	return "C" + to_string(commentNumber);
}

string IdMaker::getReplyId()
{
	replyNumber++;
	return "R" + to_string(replyNumber);
}
