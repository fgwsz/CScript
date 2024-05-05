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
    BoxManager<typename Variant::value_type>::print_object_pool();
    BoxManager<typename Variant::value_type>::print_memory_pool();
    return 0;
}
```
```txt
=================================================
[INFO]
=================================================
[TIME] 2024-05-05 16:46:19.610
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
BoxManager<std::variant<Null, bool, double, std::__cxx11::basic_string<ch
ar, std::char_traits<char>, std::allocator<char> >, std::vector<Variant,
std::allocator<Variant> >, std::map<std::__cxx11::basic_string<char, std:
:char_traits<char>, std::allocator<char> >, Variant, std::less<std::__cxx
11::basic_string<char, std::char_traits<char>, std::allocator<char> > >,
std::allocator<std::pair<const std::__cxx11::basic_string<char, std::char
_traits<char>, std::allocator<char> >, Variant> > >, std::function<Varian
t(Variant)> >>::object_pool

object_begin___________________________
[0]{pointer:2195958930688,ref count:1}
null
object_end_____________________________


object_begin___________________________
[1]{pointer:2195958930816,ref count:1}
true
object_end_____________________________


object_begin___________________________
[2]{pointer:2195958930944,ref count:1}
-1
object_end_____________________________


object_begin___________________________
[3]{pointer:2195958931072,ref count:1}
3.140000
object_end_____________________________


object_begin___________________________
[4]{pointer:2195958931200,ref count:1}
"A"
object_end_____________________________


object_begin___________________________
[5]{pointer:2195958931328,ref count:1}
"hello"
object_end_____________________________


object_begin___________________________
[6]{pointer:2195958949536,ref count:1}
null
object_end_____________________________


object_begin___________________________
[7]{pointer:2195958949664,ref count:1}
false
object_end_____________________________


object_begin___________________________
[8]{pointer:2195958949792,ref count:1}
1
object_end_____________________________


object_begin___________________________
[9]{pointer:2195958950256,ref count:1}
"world"
object_end_____________________________


object_begin___________________________
[10]{pointer:2195958950384,ref count:1}
"B"
object_end_____________________________


object_begin___________________________
[11]{pointer:2195958950512,ref count:1}
1
object_end_____________________________


object_begin___________________________
[12]{pointer:2195958950704,ref count:1}
function
object_end_____________________________


object_begin___________________________
[13]{pointer:2195958950832,ref count:1}
[
        1,
        2
]
object_end_____________________________


object_begin___________________________
[14]{pointer:2195958950960,ref count:1}
"Tom"
object_end_____________________________


object_begin___________________________
[15]{pointer:2195958951024,ref count:1}
[
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
]
object_end_____________________________


object_begin___________________________
[16]{pointer:2195958951088,ref count:1}
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
object_end_____________________________


object_begin___________________________
[17]{pointer:2195958951280,ref count:1}
function
object_end_____________________________


object_begin___________________________
[18]{pointer:2195958951408,ref count:1}
2
object_end_____________________________


object_begin___________________________
[19]{pointer:2195958951536,ref count:1}
20
object_end_____________________________


object_begin___________________________
[20]{pointer:2195958951664,ref count:1}
-3.140000
object_end_____________________________


object_begin___________________________
[21]{pointer:2195958951792,ref count:1}
{
        "age":20,
        "name":"Tom"
}
object_end_____________________________


object_begin___________________________
[22]{pointer:2195959068976,ref count:1}
"Jerry"
object_end_____________________________

BoxManager<std::variant<Null, bool, double, std::__cxx11::basic_string<ch
ar, std::char_traits<char>, std::allocator<char> >, std::vector<Variant,
std::allocator<Variant> >, std::map<std::__cxx11::basic_string<char, std:
:char_traits<char>, std::allocator<char> >, Variant, std::less<std::__cxx
11::basic_string<char, std::char_traits<char>, std::allocator<char> > >,
std::allocator<std::pair<const std::__cxx11::basic_string<char, std::char
_traits<char>, std::allocator<char> >, Variant> > >, std::function<Varian
t(Variant)> >>::memory_pool
[0]{pointer:2195959066544}
[1]{pointer:2195958951728}
[2]{pointer:2195959066608}
[3]{pointer:2195958951472}
```
