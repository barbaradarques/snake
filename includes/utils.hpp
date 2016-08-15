#ifndef UTILS_H
#define UTILS_H
#include <utility>

template <typename Type1, typename Type2>                                                   
std::pair<Type1,Type2> operator+(const std::pair<Type1,Type2> & l,const std::pair<Type1,Type2> & r){   
    return {l.first + r.first, l.second + r.second};                                    
}

template <typename Type1, typename Type2>                                                   
std::pair<Type1,Type2> operator-(const std::pair<Type1,Type2> & l,const std::pair<Type1,Type2> & r){   
    return {l.first - r.first, l.second - r.second};                                    
}

template <typename Type1, typename Type2>                                                   
bool operator==(std::pair<Type1,Type2> & l, std::pair<Type1,Type2> & r){   
    return (l.first == r.first) && (l.second == r.second);                                    
}

template <typename Type1, typename Type2>                                                   
bool operator!=(std::pair<Type1,Type2> & l, std::pair<Type1,Type2> & r){   
    return !(l==r);                                    
} 

#endif