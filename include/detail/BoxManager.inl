#pragma once
#include"BoxManager.hpp"
#include<new>//::operator new,::operator delete
#include<deque>//::std::deque
#include<map>//::std::map
#include<string>//::std::string
#include<iostream>//::std::cout
#include"type_name.hpp"//type_name
namespace detail{
template<ValueType Type>
struct BoxManagerClear{
    BoxManagerClear()
    {}
    bool init()const{
        return true;
    }
    ~BoxManagerClear(){
        BoxManager<Type>::clear();
    }
};
template<ValueType Type>
static BoxManagerClear<Type> box_manger_clear={};
template<ValueType Type>
static ::std::map<Type*,unsigned> object_pool={};
template<ValueType Type>
static ::std::deque<Type*> memory_pool={};
}//namespace detail
template<ValueType Type>
constexpr Type* BoxManager<Type>::new_object(){
    bool clear_init=detail::box_manger_clear<Type>.init();
    Type* ret=nullptr;
    if(!detail::memory_pool<Type>.empty()){
        ret=detail::memory_pool<Type>.front();
        detail::memory_pool<Type>.pop_front();
    }else{
        for(;;){
            ret=static_cast<Type*>(
                ::operator new(sizeof(Type),::std::nothrow)
            );
            if(!ret){
                ::operator delete(ret,::std::nothrow);
                ret=nullptr;
            }else{
                break;
            }
        }
    }
    new(ret)Type{};
    detail::object_pool<Type>[ret]=1;
    return ret;
}
template<ValueType Type>
constexpr void BoxManager<Type>::delete_object(Type*& object){
    if(!object){
        return;
    }
    if(detail::object_pool<Type>.count(object)==0){
        return;
    }
    if(detail::object_pool<Type>[object]>1){
        --(detail::object_pool<Type>[object]);
    }else{
        object->~Type();
        detail::memory_pool<Type>.emplace_back(object);
        detail::object_pool<Type>.erase(object);
    }
    object=nullptr;
}
template<ValueType Type>
constexpr void BoxManager<Type>::copy_object(Type*& to,Type const* from){
    if(!from){
        return;
    }
    if(to==from){
        return;
    }
    bool to_in_pool=detail::object_pool<Type>.count(to)!=0;
    bool from_in_pool=
        detail::object_pool<Type>.count(const_cast<Type*>(from))!=0;
    if((!to_in_pool)&&(!from_in_pool)){
        if(!to){
            to=new_object();
        }
        *to=*from;
        return;
    }
    if((!to_in_pool)&&from_in_pool){
        if(!to){
            to=const_cast<Type*>(from);
            ++(detail::object_pool<Type>[const_cast<Type*>(from)]);
        }else{
            *to=*from;
        }
        return;
    }
    if(to_in_pool&&(!from_in_pool)){
        if(detail::object_pool<Type>[to]>1){
            --(detail::object_pool<Type>[to]);
            to=new_object();
        }
        *to=*from;
        return;
    }
    if(to_in_pool&&from_in_pool){
        delete_object(to);
        to=const_cast<Type*>(from);
        ++(detail::object_pool<Type>[const_cast<Type*>(from)]);
    }
}
template<ValueType Type>
constexpr void BoxManager<Type>::copy_object(Type*& object){
    if(!object){
        object=new_object();
        return;
    }
    if(detail::object_pool<Type>.count(object)==0){
        return;
    }
    if(detail::object_pool<Type>[object]>1){
        --(detail::object_pool<Type>[object]);
        Type* old_object=object;
        object=new_object();
        *object=*old_object;
    }
}
template<ValueType Type>
constexpr void BoxManager<Type>::move_object(Type*& to,Type*& from){
    if(!from){
        return;
    }
    if(to==from){
        return;
    }
    bool to_in_pool=detail::object_pool<Type>.count(to)!=0;
    bool from_in_pool=detail::object_pool<Type>.count(from)!=0;
    if((!to_in_pool)&&(!from_in_pool)){
        if(!to){
            to=new_object();
        }
        *to=::std::move(*from);
        return;
    }
    if((!to_in_pool)&&from_in_pool){
        if(!to){
            to=from;
            from=nullptr;
        }else{
            *to=::std::move(*from);
            delete_object(from);
        }
        return;
    }
    if(to_in_pool&&(!from_in_pool)){
        if(detail::object_pool<Type>[to]>1){
            --(detail::object_pool<Type>[to]);
            to=new_object();
        }
        *to=::std::move(*from);
        return;
    }
    if(to_in_pool&&from_in_pool){
        delete_object(to);
        to=from;
        from=nullptr;
    }
}
template<ValueType Type>
constexpr void BoxManager<Type>::clear(){
    for(auto const& pair:detail::object_pool<Type>){
        (pair.first)->~Type();
        detail::memory_pool<Type>.emplace_back(pair.first); 
    }
    detail::object_pool<Type>.clear();
    for(auto const& element:detail::memory_pool<Type>){
        ::operator delete(element,::std::nothrow);
    }
    detail::memory_pool<Type>.clear();
}
template<ValueType Type>
constexpr void BoxManager<Type>::print_object_pool(){
    ::std::cout
        <<"BoxManager<"<<type_name<Type>()<<">::object_pool\n";
    for(
        unsigned long long index=0;
        auto const& pair:detail::object_pool<Type>
    ){
        ::std::cout
            <<"\nobject_begin___________________________\n"
            <<"["<<::std::to_string(index)<<"]"
            <<"{pointer:"<<::std::to_string(
                reinterpret_cast<::std::uintptr_t>(pair.first)
            )<<",ref count:"<<::std::to_string(pair.second)<<"}\n"
            <<*(pair.first)
            <<"\nobject_end_____________________________\n"
            <<"\n";
        ++index;
    }
}
template<ValueType Type>
constexpr void BoxManager<Type>::print_memory_pool(){
    ::std::cout
        <<"BoxManager<"<<type_name<Type>()<<">::memory_pool\n";
    for(
        unsigned long long index=0;
        auto const& element:detail::memory_pool<Type>
    ){
        ::std::cout
            <<"["<<::std::to_string(index)<<"]"
            <<"{pointer:"<<::std::to_string(
                reinterpret_cast<::std::uintptr_t>(element)
            )<<"}\n";
        ++index;
    }
}
