#include<iostream>
#include<thread>
#include<memory>
//变量作为入口函数，类对象被提前释放
std:: thread t;
void foo(int &x)
{
   x+=1;
}
int a = 1; 
void test()
{
   //int a = 1; // 这里回报错 执行完test a就会释放  而线程没释放
   t=std::thread(foo,std::ref(a));
}
//类成员函数作为入口函数，类对象被提前释放
class MyClass {
public:
    void func() {
        std::cout << "Thread " << std::this_thread::get_id() 
        << " started" << std::endl;
        // do some work
        std::cout << "Thread " << std::this_thread::get_id() 
        << " finished" << std::endl;
    }
};

//类的私有成员函数作为入口函数
class A
{
   private:
      friend void thread_foo(); // 添加友元函数  让他能调用私有函数foo
      void foo()
      {
         std:: cout<< "A private foo"<< std::endl;
      }
};

void thread_foo()
{
   std::shared_ptr<A> a_ptr =std::make_shared<A>();
   std::thread t2(&A::foo,a_ptr);
   t2.join();
}
 int main()
 {
    test();
    t.join();
    std:: cout<<a<<std::endl;

    //类成员函数作为入口函数，类对象被提前释放
    MyClass obj;
    std::thread t(&MyClass::func, &obj); //在C++中，当使用std::thread创建线程并传递类成员函数时，需要使用&来获取成员函数的地址，同时还需要传递对象的指针（或引用）作为第一个参数。
    //在这里 obj可能会被销毁掉 delect 那样线程会出错误
    t.join();
    // 如果obj 被提前销毁了，会导致未定义的行为
    //上面的代码中，在创建线程之后，obj 对象立即被销毁了，这会导致在线程执行时无法访问 obj 对象，可能会导致程序崩溃或者产生未定义的行为。

    //为了避免这个问题，可以使用 std::shared_ptr 智能指针 来管理类对象的生命周期，确保在线程执行期间对象不会被销毁。
    //具体来说，可以在创建线程之前，将类对象的指针封装在一个 std::shared_ptr 对象中，并将其作为参数传递给线程。
    //这样，在线程执行期间，即使类对象的所有者释放了其所有权，std::shared_ptr 仍然会保持对象的生命周期，直到线程结束

    std::shared_ptr<MyClass> obj_pr = std::make_shared<MyClass>();
    std::thread t1(&MyClass::func, obj_pr);
    t1.join();
    //上面的代码中，使用 std::make_shared 创建了一个 MyClass 类对象，
    //并将其封装在一个 std::shared_ptr 对象中。然后，将 std::shared_ptr 对象作为参数传递给线程。
    //这样，在线程执行期间，即使 obj 对象的所有者释放了其所有权，std::shared_ptr 仍然会保持对象的生命周期，直到线程结束。

    //类的私有成员函数作为入口函数
    thread_foo();

    return 0; 
 }