#ifndef JSONUSER_H
#define JSONUSER_H
#include <string>
#include <fstream>
#include <map>
using namespace std;

class jsonUser {
public:
    jsonUser();
    jsonUser(const jsonUser& orig);
    void Read();
    void askUserInput();
    void readLine(fstream jsonFile);
    void getAttribute(string* attribute,string* attributeContent);
    virtual ~jsonUser();
    void findPatient(map<string,string,less<string>> jsonData);
    void findPatientID(map<string,string,less<string>> jsonData);
    void findPatientName(map<string,string,less<string>> jsonData);
    void tokenizeData(string* attribute,string* attributeContent);
    void emptyMap();
    void syncMapAttributes(string* attribute,string* attributeContent);
    void beginFind();
    void write();
    void newPatientJson(string s);
private:
    
    string* input = new string[3];
    int option;
    string buffer;
    char *pch;
    char *dup;
    fstream jsonFile1;
    bool* patientFound = new bool;
    map<string,string,less<string>> jsonData;
    string newData;
    string buf;
};

#endif /* JSONUSER_H */

