#include"Object.hpp"
#include"object_to_string.hpp"
#define LambdaBegin \
Function([](Object argument_list)->Object{
//
#define LambdaEnd \
})
//
#define Argument(index__,type__,name__) \
auto& name__=argument_list.vector()[index__].data<type__>(); \
//
void log(Object object){
    ::std::cout<<object_to_string(object)<<"\n";
}
int main(int argc,char* argv[]){
    Object object=Map{
        {"null",Null{}},
        {"boolean",true},
        {"integer",-1},
        {"float",3.14},
        {"char",'A'},
        {"string","hello"},
        {"vector",
            Vector{
                Null{},false,1,-3.14,'B',"world",
                Vector{1,2},Map{{"name","Tom"},{"age",20}},
                LambdaBegin
                    return Null{};
                LambdaEnd
            },
        },
        {"set_name",
            LambdaBegin 
                Argument(0,Map,self)
                Argument(1,String,name)
                    self["name"]=name;
                    return self;
            LambdaEnd
        }
    };
    log(object);
    return 0;
}
