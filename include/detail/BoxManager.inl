#pragma once
#include"../BoxManager.hpp"
#include<new>//::operator new,::operator delete
#include<stack>//std::stack
#include<unordered_map>//std::unordered_map
#include<iostream>//std:cout
namespace detail{
template<typename Type>
struct BoxManagerClear{
    BoxManagerClear()
    {}
    bool init()const{
        return true;
    }
    ~BoxManagerClear(){
        BoxManager<Type>::clear();
        ::std::cout<<"BoxManager<"<<typeid(Type).name()<<"> Clear!\n";
    }
};
template<typename Type>
static BoxManagerClear<Type> box_manger_clear={};
template<typename Type>
static ::std::unordered_map<Type*,unsigned> object_pool={};
template<typename Type>
static ::std::stack<Type*> memory_pool={};
}//namespace detail
template<typename Type>
constexpr Type* BoxManager<Type>::new_object(){
    bool clear_init=detail::box_manger_clear<Type>.init();
    Type* ret=nullptr;
    if(!detail::memory_pool<Type>.empty()){
        ret=detail::memory_pool<Type>.top();
        detail::memory_pool<Type>.pop();
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
template<typename Type>
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
        detail::memory_pool<Type>.push(object);
        detail::object_pool<Type>.erase(object);
    }
    object=nullptr;
}
template<typename Type>
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
template<typename Type>
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
        object=new_object();
    }
}
template<typename Type>
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
template<typename Type>
constexpr void BoxManager<Type>::clear(){
    for(auto& pair:detail::object_pool<Type>){
        (pair.first)->~Type();
        detail::memory_pool<Type>.push(pair.first); 
    }
    detail::object_pool<Type>.clear();
    Type* object=nullptr;
    while(!detail::memory_pool<Type>.empty()){
        object=detail::memory_pool<Type>.top();
        ::operator delete(object,::std::nothrow);
        detail::memory_pool<Type>.pop();
    }
}
