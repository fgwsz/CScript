#pragma once
//      |U  |U c |U v |U cv
// T    |1  |0   |0   |0       
// T c  |0  |1   |0   |0         
// T v  |0  |0   |1   |0         
// T cv |0  |0   |0   |1          
template<typename T,typename U>
struct IsSame{
    static constexpr bool value=false;
};
template<typename T>
struct IsSame<T,T>{
    static constexpr bool value=true;
};