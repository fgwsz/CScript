#include<string>
#include<iostream>
#include<stdexcept>
#include"Box.hpp"
Box<::std::string> to_string(Box<int> number){
    return ::std::to_string(number.data());
}
int main(int argc,char* argv[]){
    try{
        Box<::std::string> str(::std::string{"hello"});
        Box<double> number=3.14;
        ::std::cout<<str.data()<<::std::endl;
        ::std::cout<<number.data()<<::std::endl;
        ::std::cout<<to_string(10000).data()<<::std::endl;
    }catch(::std::exception const& exception){
        ::std::cout<<exception.what()<<"\n";
    }
    return 0;
}
