#ifndef __ID_MAKER_H__
#define __ID_MAKER_H__

#include <string>

class IdMaker
{
public:
	IdMaker();
	std::string getJeekId();
	std::string getCommentId();
	std::string getReplyId();
private:
	long long unsigned int jeekNumber;
	long long unsigned int commentNumber;
	long long unsigned int replyNumber;
};

#endif