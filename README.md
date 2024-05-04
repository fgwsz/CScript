# CScript
```cpp
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
    static_assert(sizeof(Object)==8);log(object);
    return 0;
}
```
<img decoding="async" src="img/show.png" width="50%")
