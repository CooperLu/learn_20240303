#include<iostream>
#include<thread>
#include<memory>
#include<mutex>

int shared_data=0;
std::mutex mtx;
//std::lock_guard 是 C++ 标准库中的一种互斥量封装类，用于保护共享数据，防止多个线程同时访问同一资源而导致的数据竞争问题。

//std::lock_guard 的特点如下：

//当构造函数被调用时，该互斥量会被自动锁定。

//当析构函数被调用时，该互斥量会被自动解锁。

//std::lock_guard 对象不能复制或移动，因此它只能在局部作用域中使用。 
void func()
{
   for(int i=0;i<100000;i++)
   {
     std::lock_guard<std::mutex> lg(mtx); // 巧妙阿通过局部变量(lg)的释放来自动完成 方便加锁和解锁
     // mtx.lock();
      shared_data++;
     // mtx.unlock();

   }
}

//std::unique_lock 是 C++ 标准库中提供的一个互斥量封装类，用于在多线程程序中对互斥量进行加锁和解锁操作。
//它的主要特点是可以对互斥量进行更加灵活的管理，包括延迟加锁、条件变量、超时等。
//std::unique_lock 提供了以下几个成员函数
//lock()：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁。

//try_lock()：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则函数立即返回 false，否则返回 true。

//try_lock_for(const std::chrono::duration<Rep, Period>& rel_time)：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁，或者超过了指定的时间。

//try_lock_until(const std::chrono::time_point<Clock, Duration>& abs_time)：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁，或者超过了指定的时间点。

//unlock()：对互斥量进行解锁操作。
std::timed_mutex mtx2;
void func2()
{
   for(int i=0;i<2;i++)
   {
     std::unique_lock<std::timed_mutex> lg(mtx2,std::defer_lock); //这里是先不加锁
     if(lg.try_lock_for(std::chrono::seconds(2)))
     {
        std::this_thread::sleep_for(std::chrono::seconds(0));
        shared_data++;
     }


   }
}

 int main()
 {
    std:: thread t1(func2);
    std:: thread t2(func2);
    t1.join();
    t2.join();
    std::cout << "shared_data = " << shared_data << std::endl;    
    //上面的代码中，定义了一个名为 shared_data 的全局变量，并在两个线程中对其进行累加操作。在 main 函数中，创建了两个线程，并分别调用了 func 函数。
    //在 func 函数中，对 shared_data 变量进行了累加操作。
    //由于 shared_data 变量是全局变量，因此在两个线程中共享。对于这种共享的情况，需要使用互斥量等同步机制来确保多个线程之间对共享数据的访问是安全的。
    //如果不使用同步机制，就会出现数据竞争问题，导致得到错误的结果。
    return 0; 
 }