#pragma once
#include<string>
#include<vector>
#include<map>
#include<functional>
#include"IsSame.hpp"
struct Null final{};
using Boolean=bool;
using Number=double;
using String=::std::string;
class Variant;
using Array=::std::vector<Variant>;
using Object=::std::map<String,Variant>;
using Function=::std::function<Variant(Variant)>;
template<typename Type>
concept VariantType=
    IsSame<Type,Null    >::value||
    IsSame<Type,Boolean >::value||
    IsSame<Type,Number  >::value||
    IsSame<Type,String  >::value||
    IsSame<Type,Array   >::value||
    IsSame<Type,Object  >::value||
    IsSame<Type,Function>::value||
    IsSame<Type,Variant >::value||
    IsSame<Type,Null     const>::value||
    IsSame<Type,Boolean  const>::value||
    IsSame<Type,Number   const>::value||
    IsSame<Type,String   const>::value||
    IsSame<Type,Array    const>::value||
    IsSame<Type,Object   const>::value||
    IsSame<Type,Function const>::value||
    IsSame<Type,Variant  const>::value
;