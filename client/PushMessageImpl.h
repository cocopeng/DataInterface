#include "../gen-cpp/PushMessage.h"

#ifndef _PUSHMESSAGEIMP_H
#define _PUSHMESSAGEIMP_H
class PushMessageImpl : virtual public PushMessageIf {
public:
	PushMessageImpl(){

	};
	void push(std::vector<std::string> & _return, const std::vector<std::string> & messages);
	void registerCompleteNotify(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara);
};

#endif  // _PROPERTYUTIL_H
