#include"Variant.hpp"
#include"Lambda.hpp"
#include"Logger.hpp"
#include"variant_to_string.hpp"
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
                Lambda_End
            },
        },
        {"set_name",
            Lambda_Begin(Null,&variant)
            Lambda_Arg(0,String const,name)
                variant.object()["name"]=name;
            Lambda_End
        }
    };
    variant.object()["set_name"].function().Invoke("Jerry");
    Logger::info(variant_to_string(variant));
    BoxManager<typename Variant::value_type>::print_object_pool();
    BoxManager<typename Variant::value_type>::print_memory_pool();
    return 0;
}
