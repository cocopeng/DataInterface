/*
 * TestClass.cpp
 *
 *  Created on: 2015-3-18
 *      Author: root
 */
#include "TestClass.h"
#include <iostream>
using namespace std;
void TestClass::hello(){
	cout<<"hello world, I am a TestClass boost thread"<<endl;
}
void TestClass::start(){
	cout<<"enter start"<<endl;
	boost::function0<void> f = boost::bind(&TestClass::hello,this);
	boost::thread thrd(f);
	thrd.join();
	cout<<"end start"<<endl;
}
