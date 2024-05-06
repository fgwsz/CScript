#include"Variant.hpp"
#include"Logger.hpp"
#include"variant_to_string.hpp"
#include"FunctionMacro.hpp"

Function_Begin(get_type_name,String const)
Parameter(Variant,any)
    if(any.is_null()){
        return "null";
    }else if(any.is_boolean()){
        return "boolean";
    }else if(any.is_number()){
        return "number";
    }else if(any.is_string()){
        return "string";
    }else if(any.is_array()){
        return "array";
    }else if(any.is_object()){
        return "object";
    }else if(any.is_function()){
        return "function";
    }
    return "undefined";
Function_End

auto lambda_get_type_name=
    Lambda_Begin(String const)
    Parameter(Variant const,any)
        return ::get_type_name(any);
    Lambda_End;

int main(int argc,char* argv[]){
    static_assert(sizeof(Variant)<=sizeof(void*));
    Variant variant=Object{
        {"null",Null{}},
        {"boolean",true},
        {"integer",-1},
        {"float",3.14},
        {"character",'A'},
        {"string","hello"},
        {"array",
            Array{
                Null{},false,1,-3.14,'B',"world",
                Array{1,2},Object{{"name","Tom"},{"age",20}},
                Lambda_Begin(Null)
                Parameter(Number const,num1)
                Parameter(Number const,num2)
                    ::std::cout<<num1<<num2<<"\n";
                Lambda_End
            },
        },
        {"set_value",
            Lambda_Begin(Null,&variant)
            Parameter(String const,name)
            Parameter(Number const,age)
                variant.object()["name"]=name;
                variant.object()["age"]=age;
            Lambda_End
        }
    };
    variant.object()["set_value"].function().Invoke("Jerry",114514);
    Logger::info(variant_to_string(variant));
    BoxManager<typename Variant::value_type>::print_object_pool();
    BoxManager<typename Variant::value_type>::print_memory_pool();
    return 0;
}