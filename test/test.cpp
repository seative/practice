// #include <iostream>
// #include <string>
// #include <vector>

// std::vector<int> func1()
// {
//      std::vector<int> a;
//      a.reserve(100);
//      std::cout<<a.data()<<std::endl;
//      return a;
// }
 
// int main()
// {
//     std::vector<int> b=func1();
//     std::cout<<b.data()<<std::endl;
// }

#include <iostream>
#include <memory>
#include "string.h"
#include<vector>
#include<string>
using namespace std;
 
vector<int> foo_1()
{
	vector<int> p = { 99 };
	cout << "p:vector<int>" << "  p value:" << p.data() << endl;
    cout << "p:vector<int>" << "  p value:" << &p << endl;
	return std::move(p);
}
 
string foo_2()
{
	string p = "a";
    cout << "p:vector<int>" << "  p value:" << p.data() << endl;
	cout << "p:string" << "  p value:" << &p << endl;
	return p;
}
 
bool foo_3()
{
	bool p;
	cout << "p:bool" << "  p value:" << &p << endl;
	return p;
}
 
int foo_4()
{
	bool p;
	cout << "p:int" << "  p value:" << &p << endl;
	return p;
}
 
 
enum MyEnum
{
	AAA,
	BBB,
	CCC
};
 
MyEnum foo_5()
{
	MyEnum p;
	cout << "p:MyEnum" << "  p value:" << &p << endl;
	return p;
}
 
class MyClass {};
MyClass foo_6()
{
	MyClass p;
	cout << "p:Myclass" << "  p value:" << &p << endl;
	return p;
}
 
int main()
{
	{
	vector<int> p = foo_1();
	cout << "p:vector<int>" << "  p value:" << p.data() << endl;
    cout << "p:vector<int>" << "  p value:" << &p << endl;
	cout << endl;
	}
 
	{
	string p = foo_2();
    cout << "p:vector<int>" << "  p value:" << p.data() << endl;
	cout << "p:String" << "  p value:" << &p << endl;
	cout << endl;
	}
 
	{
	bool p = foo_3();
	cout << "p:bool" << "  p value:" << &p << endl;
	cout << endl;
	}
 
	{
	int p = foo_4();
	cout << "p:int" << "  p value:" << &p << endl;
	cout << endl;
	}
 
	{
	MyEnum p = foo_5();
	cout << "p:MyEnum" << "  p value:" << &p << endl;	
	cout << endl;
	}
 
	{
		MyClass p = foo_6();
		cout << "p:Myclass" << "  p value:" << &p << endl;
		cout << endl;
	}
	return 0;
}

// class MyObject
// {
// public:
//     MyObject(){
//         data = new int[1024*1024*1024];
//         std::cout<<"construct "<<this<<", data addr: "<<data<<std::endl;
//     }
//     MyObject(const MyObject& a){
//     	data = new int[1024*1024*1024];
//         memcpy(data, a.data, sizeof(data));
//         std::cout<<"copy "<<this<<", data addr: "<<data<<std::endl;
//     }
//     ~MyObject(){
//         std::cout<<"destroy "<<this<<", data addr: "<<data<<std::endl;
//         std::cout<<"delete"<<std::endl;
//         delete data;
//     }
//     int* data;
// };

// int main()
// {
//     auto obj_a = MyObject();
//     std::cout<<"obj_a addr: "<<&obj_a<<", data addr: "<<obj_a.data<<std::endl;
//     std::cout<<"-----------------"<<std::endl;
//     auto obj_b = obj_a;
//     std::cout<<"obj_b addr: "<<&obj_b<<", data addr: "<<obj_b.data<<std::endl;
//     std::cout<<"-----------------"<<std::endl;
//     return 1;
// }

// class MyObject
// {
// public:
//     MyObject(){
//         data = new int[1024*1024];
//         std::cout<<"construct "<<this<<", data addr: "<<data<<std::endl;
//     }
//     MyObject(const MyObject& a){
//     	data = new int[1024*1024];
//         memcpy(data, a.data, sizeof(data));
//         std::cout<<"copy "<<this<<", data addr: "<<data<<std::endl;
//     }
//     MyObject(MyObject&& a){   //移动构造函数
//         data = a.data;
//         a.data = nullptr;
//         std::cout<<"move "<<this<<", data addr: "<<data<<std::endl;
//     }
//     ~MyObject(){
//         std::cout<<"destroy "<<this<<", data addr: "<<data<<std::endl;
//         if(data){
//             std::cout<<"delete"<<std::endl;
//             delete data;
//         }
//     }
//     int* data;
// };


// decltype(auto) func(){
//     return MyObject();//此函数创建并返回一个MyObject作为rvalue对象
// }

// template<typename T> 
// decltype(auto) move(T&& param)
// {
//     using ReturnType = std::remove_reference_t<T>&&; 
//     return static_cast<ReturnType>(param);
// }

// int main()
// {
//     MyObject obj_a = func();
//     std::cout<<"obj_a addr: "<<&obj_a<<", data addr: "<<obj_a.data<<std::endl;
//     std::cout<<"-----------------"<<std::endl;
//     return 1;
// }

// int main()
// {

//     MyObject obj_a;
//     std::cout<<"obj_a addr: "<<&obj_a<<", data addr: "<<obj_a.data<<std::endl;
//     std::cout<<"-----------------"<<std::endl;
//     MyObject obj_b = move(obj_a); //move(obj_a)将obj_a转为rvalue，不移动任何东西！
//     std::cout<<"obj_b addr: "<<&obj_b<<", data addr: "<<obj_b.data<<std::endl;
//     std::cout<<"obj_a addr: "<<&obj_a<<", data addr: "<<obj_a.data<<std::endl;
//     std::cout<<"-----------------"<<std::endl;
//     return 1;
// }


