#include <iostream>
#include <utility>
#include <vector>
#include <deque>

typedef std::pair<int, int> PAIR;

using namespace std;

template <typename Type1, typename Type2>                                                   
std::pair<Type1,Type2> operator+(const std::pair<Type1,Type2> & l,const std::pair<Type1,Type2> & r) {   
    return {l.first + r.first, l.second + r.second};                                    
}

template <typename Type1, typename Type2>                                                   
std::pair<Type1,Type2> operator-(const std::pair<Type1,Type2> & l,const std::pair<Type1,Type2> & r) {   
    return {l.first - r.first, l.second - r.second};                                    
}

template <typename Type1, typename Type2>                                                   
bool operator== ( std::pair<Type1,Type2> & l, std::pair<Type1,Type2> & r) {   
    return (l.first == r.first && l.second == r.second);                                    
}

template <typename Type1, typename Type2>                                                   
bool operator!=( std::pair<Type1,Type2> & l, std::pair<Type1,Type2> & r) {   
    return !(l==r);                                    
} 

int main(){
	PAIR a = make_pair(1, 1);
	PAIR b = make_pair(1, 1);
	PAIR c = a;
	++c.first;
	cout<<c.first<<" "<<c.second<<endl;
	bool res = (a!=b);
	cout<< res <<endl;
	return 0;
}