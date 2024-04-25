#include <iostream>
#include <cstring>
using namespace std;


class String {
    
    char * buffer = nullptr;
    unsigned int size = 0;
    
    public: 
    String() = default; 
    String(const char * p): buffer(new char[strlen(p)+1]), size(strlen(p)) {
        strcpy(buffer, p);    
    };
    ~String(){
        delete [] buffer;
    }
    String(const String & r) : 
        buffer(new char[r.size+1]), size(r.size){
        strcpy(buffer, r.buffer);
    }
    String & operator=(const String & r){
        if(this != &r){
            if(r.size > this->size){
                delete [] buffer;
                buffer = new char[r.size + 1];
            } 
            strcpy(buffer, r.buffer);
            size = r.size;
        }
        return *this;
    }

    const char & operator[](int i) const{
        if( i < 0 || i >= size) exit(1);
        return buffer[i];
    }
    
    char & operator[](int i) {
        if(i < 0 || i >= size) exit(1); 
        return buffer[i];
    }

    String & operator+=(const String & r){
        char * p = new char[size + r.size + 1];
        strcpy(p, buffer);
        strcat(p, r.buffer);
        delete [] buffer;
        buffer = p;
        size = size + r.size;
        return *this;
    }

    bool operator==(const String & r) const{
        if(size == r.size){
            for(int i = 0; i < size; i++){
                if(buffer[i] != r.buffer[i]){
                    return false;
                }
                else continue;
            }
            return true;
        }
        else return false;
    }

    bool operator!=(const String & r) const{
        return strcmp(buffer, r.buffer) != 0;
    }

    bool operator>(const String & r) const{
        return strcmp(buffer, r.buffer) > 0;
    }

    bool operator<(const String & r) const{
        return strcmp(buffer, r.buffer) < 0;
    }

    operator unsigned int () const {
        unsigned int summa = 0;
        for(int i = 0; i < size - 1; i++){
            summa += buffer[i];
        }
        return summa;
    }

    bool operator()(char ch) const{
        return strchr(buffer, ch) != NULL;
    }

    String & operator=(char * p){
        if(strlen(p) > this->size){
            delete [] buffer;
            buffer = new char[strlen(p) + 1];
        }
        strcpy(buffer, p);
        size = strlen(p);
        return *this;
    }

    friend istream & operator>>(istream &, String &);
    friend ostream & operator<<(ostream & , const String & );
};


istream & operator>>(istream & in, String & r){
    char ch;
    char * temp_buffer = NULL;
    int i = 0;
    while((ch = fgetc(stdin)) != '\n'){
        if(i == r.size){
            temp_buffer = new char[r.size*2 + 1];
            temp_buffer[r.size*2] = '\0';
            strcpy(temp_buffer, r.buffer);
            delete [] r.buffer;
            r.buffer = temp_buffer;
            r.size = r.size*2;
            r.buffer[i] = ch;
        }
        r.buffer[i] = ch;
        i++;
    }
    r.buffer[i] = '\0';
    r.size = i;
    return in;
}

ostream & operator<<(ostream & out, const String & r){
        if(r.size == 0) out<<"String is empty : \n";
        else out<<r.buffer<<endl;
        return out;
}
    

int main()
{
    String str1("ABCdfdfD");
    String str2("ABCD");
    String str3("DFDF");
    if(str1 == str2){
        cout << "str1 = str2 : True" << endl;
    }
    else cout << "str1 = str2 : False" << endl;

    str1('F');
    str1 += str2;
    str1[3];
    cin >> str3;
    cout << str3 << endl;
    return 0;
}