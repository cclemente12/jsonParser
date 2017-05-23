#include "jsonUser.h"
#include <iostream>
#include <string.h>

using namespace std;
jsonUser::jsonUser() {
    *patientFound=false;
    int option;
    while(1)
    {
        cout << endl << endl << endl << "Enter option:" << endl <<  "\t(1)Find Patient" << endl << "\t(2)Add Patient" << endl;
        cin >> option;
        if(option ==1)
        {
            Read();
        }
        else 
        {
            write();
        }
    }
}

jsonUser::jsonUser(const jsonUser& orig) {
}

jsonUser::~jsonUser() 
{
    delete patientFound;
    delete pch;
    delete dup;
    delete[] input;
}

void jsonUser::write(){

    buf.clear();
    newData.clear();
    fstream* jsonFile=new fstream;

    jsonFile->open("patientrecord.json", ios::in);

    cout << "write enter" << endl;

    int lines=0;
    getline(cin, buf);
    while(!jsonFile->eof())
    {
            getline(*jsonFile,buffer);
            lines++;
    }

    jsonFile->close();

     string s = to_string(lines);
     for(unsigned long i =0; i <=12-s.length();i++ )
     {
            s = '0'+s;
     }
    newPatientJson(s);
    jsonFile->open("patientrecord.json", ios::app);
    *jsonFile<<newData;
    jsonFile->close();
    delete jsonFile;
}

void jsonUser::newPatientJson(string s){
     newData = "[{Patient ID: "+s+"},";
     cout << "Enter Patient Last Name: ";
     getline(cin, buf);
     newData = newData+"{Last Name: "+buf+"},"; 	
     cout << "Enter Patient First Name: ";
     getline(cin, buf);
     newData = newData+"{First Name: "+buf+"},"; 
     cout << "Enter Patient Middle Name: ";
     getline(cin, buf);
     newData = newData+"{Middle Name: "+buf+"},";
     cout << "Enter House Number: ";
     getline(cin, buf);
     newData = newData+"{House Number: "+buf+"},";
     cout << "Enter Street : ";
     getline(cin, buf);
     newData = newData+"{Street: "+buf+"},";
     cout << "Enter Patient City: ";
     getline(cin, buf);
     newData = newData+"{City: "+buf+"},";
     cout << "Enter Patient Province: ";
     getline(cin, buf);
     newData = newData+"{Province: "+buf+"},";
     cout << "Enter Patient Birthday(d/m/y): ";
     getline(cin, buf);
     newData = newData+"{Birthday: "+buf+"},";
     cout << "Enter Patient Gender: ";
     getline(cin, buf);
     newData = newData+"{Gender: "+buf+"},";
     cout << "Enter Patient Blood type: ";
     getline(cin, buf);
     newData = newData+"{Blood type: "+buf+"},";
     cout << "Enter Patient Weight: ";
     getline(cin, buf);
     newData = newData+"{Weight: "+buf+"},";
     cout << "Enter Patient Height: ";
     getline(cin, buf);
     newData = newData+"{Height: "+buf+"},";
     cout << "Enter Facility ID: ";
     getline(cin, buf);
     newData = newData+"{Facility ID: "+buf+"}]\n";
     cout<<newData;
}

void jsonUser::tokenizeData(string* attribute,string* attributeContent)
{
    dup = strdup(buffer.c_str());
    pch = strtok (dup,"[{,}]");
    while (pch != NULL)
    {
        getAttribute(attribute,attributeContent);	
        pch = strtok (NULL, "[{,}]");
    }
}
void jsonUser::emptyMap()
{
    while(!jsonData.empty())
    {
        jsonData.erase(jsonData.begin());
    }
}
void jsonUser::syncMapAttributes(string* attribute,string* attributeContent)
{
    int i=0;
    while(!(attribute[i].empty()))
    {
        jsonData[attribute[i]]=attributeContent[i];
        i++;
    }
}
void jsonUser::beginFind()
{
    while(!jsonFile1.eof())
    {
        getline(jsonFile1,this->buffer);
        // cout << "After get line" << endl;
        string* attribute = new string[100];
        string* attributeContent= new string[100];

        map <string,string,less<string>>::iterator iter;
        tokenizeData(attribute,attributeContent);

        syncMapAttributes(attribute,attributeContent);
        findPatient(jsonData);
        emptyMap();
        delete[] attribute;
        delete[] attributeContent;
    }
}
void jsonUser::Read()
{
    		
    askUserInput();

    this->jsonFile1.open("patientrecord.json", ios::in);
    *patientFound=false;
    beginFind();
    delete dup;

    if(!*patientFound)
    {
        cout << "PATIENT NOT FOUND" << endl;
    }

    jsonFile1.close();
    delete patientFound;
	
}

void jsonUser::askUserInput()
{

    cout << "Find option:" << endl <<  "\t(1)Type ID" << endl << "\t(2)Name" << endl;
    cin >> option;
    string emptyBuf;
    getline(cin, emptyBuf);
    if(option==1)
    {
            cout << "Enter Patient's ID: ";
            getline(cin, input[0]);
    }
    else
    {
            cout << "Enter Patient's Last Name: ";
            getline(cin, input[0]);
            cout << "Enter Patient's First Name: ";
            getline(cin, input[1]);
            cout << "Enter Patient's Middle Name: ";
            getline(cin, input[2]);
    }

}

void jsonUser::getAttribute(string* attribute,string* attributeContent)
{
    string s(pch);

    int pos,i=0;
    pos=s.find(":");

    for(i=0;!(attribute[i].empty());i++);
    if(i<10)
    {
            attribute[i]=to_string(0) + to_string(i)+s.substr(0,pos);	
    }
    else
    {	
            attribute[i]=to_string(i)+s.substr(0,pos);
    }
    attributeContent[i]=s.substr(pos+1,s.length()-1);
}

void jsonUser::findPatient(map<string,string,less<string>> jsonData)
{
    if(option==1)
    {
            findPatientID(jsonData);
    }
    else
    {
    findPatientName(jsonData);
    }

}

void jsonUser::findPatientID(map<string,string,less<string>> jsonData)
{
    int flagPatientID=0;
    for(map <string,string,less<string>>::iterator iter=jsonData.begin();iter != jsonData.end();iter++)
    {
        if(((*iter).first).substr(2,((*iter).first.length()-1))=="Patient ID" && (*iter).second==input[0])
        {
                flagPatientID=1;
        }
    }
    if(flagPatientID)
    {
        for(map <string,string,less<string>>::iterator iter=jsonData.begin();iter != jsonData.end();iter++)
        {
            *patientFound=true;
            cout << ((*iter).first).substr(2,((*iter).first.length()-1)) << "=" << (*iter).second << endl;
        }
    }
}

void jsonUser::findPatientName(map<string,string,less<string>> jsonData)
{
    int flagLastName=0,flagFirstName=0,flagMiddleName=0;
    for(map <string,string,less<string>>::iterator iter=jsonData.begin();iter != jsonData.end();iter++)
    {
        if(((*iter).first).substr(2,((*iter).first.length()-1))=="Last Name" && (*iter).second==input[0])
        {
                flagLastName=1;
        }
        else if(((*iter).first).substr(2,((*iter).first.length()-1))=="First Name" && (*iter).second==input[1])
        {
                flagFirstName=1;
        }
        else if(((*iter).first).substr(2,((*iter).first.length()-1))=="Middle Name" && (*iter).second==input[2])
        {
                flagMiddleName=1;
        }
    }

    if(flagLastName && flagFirstName && flagMiddleName)
    {
        for(map <string,string,less<string>>::iterator iter=jsonData.begin();iter != jsonData.end();iter++)
        {
            *patientFound=true;
            cout << ((*iter).first).substr(2,((*iter).first.length()-1)) << "=" << (*iter).second << endl;
        }
    }
}
