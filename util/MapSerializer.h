#ifndef _MAPSERIALZER_H
#define _MAPSERIALZER_H

#include"json/json.h"
#include"json/value.h"
//#pragma comment(lib, "json_vc71_libmtd.lib")  
#include "fstream"  
#include "assert.h"
#include <string>
#include <map>
using namespace std;

class MapSerialzer {
public:
	static int readFromFile(string filename ,map<string,string>& mappara);
	static int readFromFile(map<string,string>& mappara);

	static int writeToFile(string filename, map<string,string>& mappara);
	static int writeToFile(map<string,string>& mappara);
private:
	static string FILENAME ;

};
#endif
