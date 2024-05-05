# CScript
```cpp
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
    return 0;
}
```
```txt
=================================================
[INFO]
=================================================
[TIME] 2024-05-05 14:44:02.917
[FILE] D:\MyWorkSpace\GitProjects\CScript\src\main.cpp(30:17)
[MESSAGE]
{
        "array":[
                null,
                false,
                1,
                -3.140000,
                "B",
                "world",
                [
                        1,
                        2
                ],
                {
                        "age":20,
                        "name":"Tom"
                },
                function
        ],
        "boolean":true,
        "character":"A",
        "float":3.140000,
        "integer":-1,
        "name":"Jerry",
        "null":null,
        "set_name":function,
        "string":"hello"
}
=================================================
```