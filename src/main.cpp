#include"Object.hpp"
#include"object_to_string.hpp"
void log(Object object){
    ::std::cout<<object_to_string(object)<<"\n";
}
Object foo(Object){
    return {};
}
#define LambdaBegin \
Function([](Object argument_list)->Object{
//
#define LambdaEnd \
})
//
#define Argument(index__,type__,name__) \
auto& name__=argument_list.vector()[index__].type__(); \
//
Object object=Map{
    {"null",Null{}},
    {"boolean",true},
    {"integr",-1},
    {"float",3.14},
    {"char",'A'},
    {"string","hello"},
    {"vector",
        Vector{
            Null{},false,1,-3.14,'B',"world",
            Vector{1,2},Map{{"name","Tom"},{"age",20}}
        },
    },
    {"set_name",
        LambdaBegin 
            Argument(0,map,self)
            Argument(1,string,name)
                self["name"]=name;
                return self;
        LambdaEnd
    }
};
int main(int argc,char* argv[]){
    Object obj;
    log(obj);
    obj=Null{};
    log(obj);
    obj=true;
    log(obj);
    obj=3.1415926;
    log(obj);
    obj="hello world!";
    log(obj);
    obj=Vector{
        Null{},
        false,
        100,
        "Str",
        Vector{1,2,3},
        Map{{"name","Tom"},{"age",20}},
        foo
    };
    log(obj);
    obj=Map{
        {"name","Jerry"},
        {"age",10},
        {"foo",foo},
        {"is_mouse",true},
        {"array",Vector{0,1,2,Vector{3,4,Vector{5}},6,Vector{7,8}}}
    };
    log(obj);
    obj=foo;
    log(obj);
    log(object);
    return 0;
}
