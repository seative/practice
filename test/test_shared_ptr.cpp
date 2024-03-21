#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class A
{
public:
    A(std::shared_ptr<int> temp):b(temp)
    {
       std::cout<<b.use_count()<<std::endl;
       std::cout<<temp.use_count()<<std::endl;
       if(!temp)
       {
        temp=shared_ptr<int>(new int);
        // std::cout<<temp.use_count()<<std::endl;
        
        b=temp;
        std::cout<<b.use_count()<<std::endl;
       }

    }
    std::shared_ptr<int> b;
};

std::vector<int> func()
{
    std::vector<int> a;
    a.reserve(1e8);
    std::cout<<a.data()<<std::endl;
    return a;
}

int main()
{
    shared_ptr<int> sp1(new int(180)); // 强引用计数从0变1
    // shared_ptr<int> spytemp(sp1);
    
    
    shared_ptr<int> sp2;
    std::cout<<sp2.use_count()<<std::endl;

    
    sp2 = std::move(sp1); // 移动赋值，sp1变成空，sp2指向该内存，强引用计数仍为1
    A a(sp2);

    std::cout<<sp2.use_count()<<std::endl;
    std::cout<<sp2.get()<<std::endl;

    std::cout<<a.b.use_count()<<std::endl;
    std::cout<<a.b.get()<<std::endl;


    std::vector<int> b=func();
    std::cout<<b.data()<<std::endl;

	return 0;
}