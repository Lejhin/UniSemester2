#ifndef _STRING
#define _STRING

#include <iostream>
#include <cstring>



class String{

    private:

        char* str;
        size_t length;

    public:

        String(const char* String) : str(new char +1){
            length = strlen(String);
            strcpy(str, String);
        }

        ~String(){
            delete[] str;
        }

        //Kopierkonstruktor
        String(const String& s){
            length = s.length;
            str = new char[length+1];
            strcpy(str, s.str);   
        }
        void print(){
            std::cout << str << std::endl;
        }
};


#endif