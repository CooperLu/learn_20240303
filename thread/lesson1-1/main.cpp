#include<iostream>
#include<thread>
void printhelloworld()
{
   std::cout<<"hello world"<<std::endl;
}
void printmsg(std::string msg)
{
   std::cout << msg << std::endl;
}
void mycounter(int num)
{
   for(int i = 0 ;i < num; i++)
      std:: cout<<i;
   std::cout << std::endl;
}
 int main()
 {
    // 创建线程
    std:: thread thread1(printhelloworld);
    // 主线程 等待这个子线程结束
    thread1.join();
    // 传参数
    std:: thread thread2(printmsg,"hello thread");
    thread2.join();
    //  thread2.detach();  这里是主线程不等  子线程会在后台运行 不会报错

    std:: thread thread3(printmsg,"isJoin ok");
    // 是判断该线程能否进行join  一般会先判断一下
    bool isJoin = thread3.joinable(); 
    if(isJoin)
    {
       thread3.join(); // 主线程其实会在这一直等待  不会执行下面的函数
    }

    std:: thread thread4(mycounter,100);
    // 是判断该线程能否进行join  一般会先判断一下
    bool isJoin2 = thread4.joinable(); 
    if(isJoin2)
    {
       thread4.join(); // join 是阻塞的   主线程其实会在这一直等待  不会执行下面的函数
    }
    std::cout<<"mycouter end"<<std::endl;
    return 0;
 }