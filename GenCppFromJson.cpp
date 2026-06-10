

#include "json/json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#if defined(WIN32) && defined(_WINDOWS)
	#include <Windows.h>
	#include <time.h>
#endif

using namespace std;

/* Create code head file des
 *
 */
void genHeader(Json::Value & res)
{
	string name = res["name"].asString();
	stringstream ss;
	string tmp ;
	tmp.resize(256);
	string oneTab = "    ";
	
    ss << "//" << endl;
    ss << "// " <<name << ".h" << endl;
    ss << "//" << " framework" << endl;
    ss << "//" << endl;
    
    time_t timeNow = time(NULL);
    
    // get local time
    struct tm* p = localtime(&timeNow);
    ss << "// "<< "Created by weitongming on " << p->tm_year + 1900 << "-" << p->tm_mon+1 << "-" << p->tm_mday << endl << endl;
    
    // trans char to UPPER
    transform(name.begin(), name.end(), tmp.begin(), ::toupper);
    
	//tmp += "_H";
	tmp = tmp.substr(0, name.length());
	ss << "#ifndef " << tmp <<"_H" << endl;
	ss << "#define " << tmp <<"_H"<< endl << endl;
	ss << "class " << name << endl;
	ss << "{" << endl;

	ss << "friend ostream & operator << (ostream & os, " << name << " &self);" << endl;
	ss << "friend istream & operator >> (istream & is, " << name << " &self);" << endl;
	ss << "friend bool operator < (" << name << " &left, " << name << " &right);" << endl;
	ss << "friend bool operator == (" << name << " &left, " << name << " &right);" << endl << endl;
	
	ss << "public:" <<endl;
	
    ss << oneTab << name << "();";
    ss << endl;

	ss << oneTab << name << "(const "<<name << " &ano); // 拷贝构造函数" << endl;
    ss << endl;

	ss << oneTab << "virtual ~" << name <<"(); // 析构函数" << endl << endl;

	ss << oneTab << name <<" & operator = " << "(const "<<name << " &ano); // 赋值运算符" << endl << endl;

    ss << "public:" <<endl;
    Json::Value funcs = res["methods"];
	Json::Value::Members funcmems =  funcs.getMemberNames();
    
    for (int i = 0; i < funcmems.size(); i++) {
        string funcName = funcmems[i];
        Json::Value func = funcs[funcName];
        
        ss << oneTab << func["return"].asString() << " " << funcName<< "(" << func["args"].asString() << ")";
        if(func["const"].asString() == "true")
        {
            ss << " const;" << endl;
        }else
        {
            ss<< ";" << endl;
        }
    }
    ss << endl;
	ss << "private: // member" << endl;

	Json::Value props = res["props"];
	Json::Value::Members mems =  props.getMemberNames();
    
	for (int i = 0; i< mems.size();i++)
	{
		string propName = mems[i];
		string propValue = props[propName].asString();
		ss << oneTab <<propValue << " " << propName << ";" << endl; 
	}
	ss << "};" << endl << endl;
	ss << "#endif";

	ofstream os;
    
    string fileName = name + ".h";
    
    string path = "/Users/tuyou/Documents/";
    
    os.open((path + fileName).c_str());

	os << ss.str()<< endl;
	os.flush();
	os.close();
}

/* create cpp file des
 */
void genCppSrc(Json::Value & res)
{
    string name = res["name"].asString();
	stringstream ss;
	string tmp ;
	tmp.resize(256);
	string oneTab = "    ";
    
    ss << "//" << endl;
    ss << "// " <<name << ".cpp" << endl;
    ss << "//" << " framework" << endl;
    ss << "//" << endl;
    
    time_t timeNow = time(NULL);
    
    struct tm* p = localtime(&timeNow);
    ss << "// "<< "Created by weitongming on " << p->tm_year + 1900 << "-" << p->tm_mon+1 << "-" << p->tm_mday << endl << endl;

    ss << name << "::" << name << "(): // Init list";
    
    ss << endl;
	ss << "{" << endl;
	ss << oneTab<<"// Init code" << endl;
	ss << "}" << endl << endl;
    
	ss << name << "::" << name << "(const "<<name << " &ano): // Copy Constructor" << endl;
	ss << "{" << endl;
	ss << oneTab<<"// Funtions" << endl;
	ss << "}" << endl << endl;
    
	ss << name << "::" << "~" << name <<"()" << endl;
	ss << "{" << endl;
	ss << oneTab<<"// Destructor" << endl;
	ss << "}" << endl << endl;
    
	ss << name << " & " << name << "::" << "operator =" << "(const "<<name << " &ano)" << endl;
	ss << "{" << endl;
	ss << oneTab<<"// operator =" << endl;
	ss << "}" << endl << endl;
    
    
    // Normal Function
    Json::Value funcs = res["methods"];
	Json::Value::Members funcmems =  funcs.getMemberNames();
    
    for (int i = 0; i < funcmems.size(); i++) {
        string funcName = funcmems[i];
        Json::Value func = funcs[funcName];
        
        ss << func["return"].asString() << " " << name << "::" << funcName<< "(" << func["args"].asString() << ")" << endl;
        ss << "{" << endl;
        ss << oneTab << "// Function" << endl;
        ss << "}" << endl << endl;
    }

    ofstream os;
    
    string fileName = name + ".cpp";
    string path = "/Users/tuyou/Documents/";
    
    os.open((path + fileName).c_str());
	os << ss.str()<< endl;
	os.flush();
	os.close();
}

int genCpp(const char * jsFileName)
{
	Json::Reader reader;
    Json::Value json_object;
    std::ifstream inf;

    inf.open(jsFileName);
    Json::Value res;
    
    if (reader.parse(inf, res, false))
    {
        genHeader(res);
        genCppSrc(res);
        return 0;
    }else
    {
        cout << "fail to parse" << endl;
        return 1;
    }
    
//
//    cout << "class name:" << res["name"] <<endl;
//    Json::Value::Members mems = (res["funcs"]).getMemberNames();
//    
//    cout << "func names:";
//    for (int i = 0; i< mems.size();i++)
//    {
//        cout << mems[i] << "\t";
//    }
//    cout << endl;
//    
//    mems =  res["props"].getMemberNames();
//    cout << "properties:";
//    for (int i = 0; i< mems.size();i++)
//    {
//        cout << mems[i] << "\t";
//    }
//    cout << endl;
//    
}



