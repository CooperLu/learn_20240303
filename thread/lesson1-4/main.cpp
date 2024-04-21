#include<iostream>
#include<thread>
#include<memory>
#include<mutex>
//假设有两个线程 T1 和 T2，它们需要对两个互斥量 mtx1 和 mtx2 进行访问，而且需要按照以下顺序获取互斥量的所有权：


//- T1 先获取 mtx1 的所有权，再获取 mtx2 的所有权。

//- T2 先获取 mtx2 的所有权，再获取 mtx1 的所有权。


//如果两个线程同时执行，就会出现死锁问题。因为 T1 获取了 mtx1 的所有权，但是无法获取 mtx2 的所有权，而 T2 获取了 mtx2 的所有权，但是无法获取 mtx1 的所有权，两个线程互相等待对方释放互斥量，导致死锁。

//顺序锁
//为了解决这个问题，可以让两个线程按照相同的顺序获取互斥量的所有权。例如，都先获取 mtx1 的所有权，再获取 mtx2 的所有权，或者都先获取 mtx2 的所有权，再获取 mtx1 的所有权。这样就可以避免死锁问题。
 std::mutex mtx1, mtx2;
 void func1() 
 {    
   mtx2.lock();    
   std::cout << "Thread 1 locked mutex 2" << std::endl;    
   mtx1.lock();    std::cout << "Thread 1 locked mutex 1" << std::endl;    
   mtx1.unlock();    std::cout << "Thread 1 unlocked mutex 1" << std::endl;    
   mtx2.unlock();    std::cout << "Thread 1 unlocked mutex 2" << std::endl;
 }
 void func2() 
 {    
   mtx2.lock();    std::cout << "Thread 2 locked mutex 2" << std::endl;    
   mtx1.lock();    std::cout << "Thread 2 locked mutex 1" << std::endl;   
   mtx1.unlock();    
   std::cout << "Thread 2 unlocked mutex 1" << std::endl;    
   mtx2.unlock();    
   std::cout << "Thread 2 unlocked mutex 2" << std::endl;
 }
 int main()
 {
   std::thread t1(func1);   
   std::thread t2(func2);   
   t1.join();   
   t2.join();   
   return 0;
 }