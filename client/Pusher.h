#include <list> 
#include <string>
#include <vector>
using namespace std;

//typedef list <string> LS;
typedef vector<string> LS;

    class CSingleton  
    {  
    private:  
        CSingleton()  
        {  
        }  
        static CSingleton *m_pInstance;  
        class CGarbo   //����Ψһ��������������������ɾ��CSingleton��ʵ��  
        {  
        public:  
            ~CGarbo()  
            {  
                if(CSingleton::m_pInstance)  
                    delete CSingleton::m_pInstance;  
            }  
        };  
        static CGarbo Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  
    public:  
        static CSingleton * GetInstance()  
        {  
            if(m_pInstance == NULL)  //�ж��Ƿ��һ�ε���  
                m_pInstance = new CSingleton();  
            return m_pInstance;  
        }  
    };  


class SubscriptionCallBack
{
public:
	virtual void receiveSubsription(LS result) = 0;
};

class Pusher
{
private:
	
	Pusher(){
	};
	static Pusher *  pusher;
	SubscriptionCallBack * callBack;
	bool lock ;
	LS result;
	
	/*
	static class InnerClass
	{
	public:
		InnerClass(){
		};
		~InnerClass(){
		};

	public:
		static Pusher SINGLETON;
	};
	*/
	//class CGarbo //����Ψһ��������������������ɾ��Pusher��ʵ��
	//{
	//public:
	//	~CGarbo()
	//	{
	//		if(Pusher::pusher)
	//			delete Pusher::pusher;
	//	}
	//};
	//static CGarbo Garbo;
public:
	static Pusher*  getInstance(){
		//if( ( NULL == pusher) )
		//	pusher  = &InnerClass::SINGLETON;
		if( Pusher::pusher == NULL)
			 Pusher::pusher = new Pusher();
		//return  Pusher::pusher;
		//if(pusher == NULL)
		//	;
		return pusher;
		//return NULL;
	}
	SubscriptionCallBack * getCallBack(){
		return callBack;
	}
	void setCallBack(SubscriptionCallBack *callBack){
		this->callBack = callBack;
	}
	void getSubscription(SubscriptionCallBack *);
	void getSubscription();
	bool isLock(){
		return lock;
	}
	void setLock(bool lock){
		this->lock = lock;
	}
	LS getResult(){
		return result;
	}
	void setResult(LS messages){
		this->result = messages;
	}
};

//Pusher * Pusher::pusher = NULL;