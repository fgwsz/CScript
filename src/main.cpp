#include<iostream>
#include"Box.hpp"
int main(int argc,char* argv[]){
    Box<::std::string> str(::std::string{"hello"});
    Box<double> number=3.14;
    ::std::cout<<str.get()<<::std::endl;
    ::std::cout<<number.get()<<::std::endl;
    return 0;
}
