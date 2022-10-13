#ifndef _STRING
#define _STRING

#include <iostream>
#include <cstring>



class String{

    private:

        char* str;
        size_t length;
        void deepCopy(const String& newString){
                
                this->length = newString.length;
                this->str = new char[this->length+1];
                strcpy(str, newString.str);
        }

    public:

        String(const char* String) {
            length = strlen(String);
            str = new char[length+1];
            strcpy(str, String);
        }

        ~String(){
            delete[] str;
        }

        //Kopierkonstruktor
        String(const String& s){
            deepCopy(s);
        }

        String& operator=(const String& newString){
            if(this->str != newString.str){
                delete[] this->str;
                deepCopy(newString);
            }
            return *this;
        }

        /* Vorteil : Funktioniert immer!!
        
        String& operator=(const String& newString){
            String local(newString);
            std::swap(length, local.length);
            std::swap(s. local.str);
            return *this;
        }
        */

        void print(){
            std::cout << str << std::endl;
        }
};


#endif