#include<iostream>
#include<fstream>
#include<string>
// #include "include/sowa.h"
#include "sowa.cpp"

int main()
{
    fstream in;
    in.open("./examples/main.sowa", ios::in);

    string temp, src="";
    if(in.good()){
      while(!in.eof())
      {
        getline(in, temp);
        src += temp;
      }
      in.close();
    }
    else{
      cout<<"Error"<<endl;
    }

    src += "\0";

    // cout<<src;
    sowa_compile(src);

    return 0;
}