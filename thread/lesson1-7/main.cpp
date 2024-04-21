#include<iostream>
#include<thread>
#include<memory>
#include<mutex>
//单例设计模式是一种常见的设计模式，用于确保某个类只能创建一个实例。
//由于单例实例是全局唯一的，因此在多线程环境中使用单例模式时，需要考虑线程安全的问题。
//下面是一个简单的单例模式的实现：
// class Singleton {
// public:
//     static Singleton& getInstance() {
//          static Singleton instance;
//          return instance;
//     }    
//     void setData(int data) {
//          m_data = data;
//     }    
//     int getData() const {
//          return m_data;
//     }
// private:
//     Singleton() {}
//     Singleton(const Singleton&) = delete;//禁用拷贝构造函数
//     Singleton& operator=(const Singleton&) = delete;   //禁用赋值运算符 
//     int m_data = 0;
// };
//在这个单例类中，我们使用了一个静态成员函数 getInstance() 来获取单例实例，该函数使用了一个静态局部变量 instance 来存储单例实例。
//由于静态局部变量只会被初始化一次，因此该实现可以确保单例实例只会被创建一次。
//但是，该实现并不是线程安全的。如果多个线程同时调用 getInstance() 函数，可能会导致多个对象被创建，从而违反了单例模式的要求。
//此外，如果多个线程同时调用 setData() 函数来修改单例对象的数据成员 m_data，可能会导致数据不一致或不正确的结果。
//为了解决这些问题，我们可以使用 std::call_once 来实现一次性初始化，从而确保单例实例只会被创建一次。下面是一个使用 std::call_once 的单例实现：
class Singleton {
public:
    static Singleton& getInstance() {
            std::call_once(m_onceFlag, &Singleton::init);
            return *m_instance;
    }    
    void setData(int data) {
        m_data = data;
    }    
    int getData() const {        
    return m_data;
    }
private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;    
    static void init() {
        m_instance.reset(new Singleton);
        std::cout<<__TIME__<<std::endl;
    }    
    static std::unique_ptr<Singleton> m_instance;    
    static std::once_flag m_onceFlag;    
    int m_data = 0;
};
std::unique_ptr<Singleton> Singleton::m_instance;
std::once_flag Singleton::m_onceFlag;
//在这个实现中，我们使用了一个静态成员变量 m_instance 来存储单例实例，使用了一个静态成员变量 m_onceFlag 来标记初始化是否已经完成。
//在 getInstance() 函数中，我们使用 std::call_once 来调用 init() 函数，确保单例实例只会被创建一次。在 init() 函数中，我们使用了 std::unique_ptr 来创建单例实例。
//使用 std::call_once 可以确保单例实例只会被创建一次，从而避免了多个对象被创建的问题。此外，使用 std::unique_ptr 可以确保单例实例被正确地释放，避免了内存泄漏的问题。


// std::call_once` 是 C++11 标准库中的一个函数，用于确保某个函数只会被调用一次。其函数原型如下：

// template<class Callable, class... Args>

// void call_once(std::once_flag& flag, Callable&& func, Args&&... args);

//其中，`flag` 是一个 `std::once_flag` 类型的对象，用于标记函数是否已经被调用；`func` 是需要被调用的函数或可调用对象；`args` 是函数或可调用对象的参数。

//std::call_once` 的作用是，确保在多个线程中同时调用 `call_once` 时，只有一个线程能够成功执行 `func` 函数，而其他线程则会等待该函数执行完成。
void caldata()
{
   Singleton::getInstance().setData(1);
}
 int main()
 {
      std::thread t1(caldata);
      std::thread t2(caldata);
      t1.join();
      t2.join();
      std::cout<<Singleton::getInstance().getData()<<std::endl;
    return 0; 
 }