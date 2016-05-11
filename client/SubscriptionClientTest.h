#include "Pusher.h"
#include <boost/function/function0.hpp>
#include <boost/thread/thread.hpp>


class SubscriptionClientTest : SubscriptionCallBack {
public:
	SubscriptionClientTest();
	void getSubscription();
	void receiveSubsription(LS result);

	void hello();
	void start();

private:
	Pusher * pusher;
	void registerToPusher();
};

void threadtestSub(int i);
