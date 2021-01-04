#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <pcap.h>

#include <boost/thread.hpp>
#include <boost/date_time.hpp>

void workFunc(std::string msg, int fct)
{
   //boost::posix_time::seconds workTime(3);
   std::cout << "Worker running" << std::endl;
   std::cout << msg << std::endl;
   //boost::this_thread::sleep(workTime);
   double res = 1;
   for (int i=1; i<=fct; i++){
      res = res * i;
   }
   std::cout << "Worker finished" << std::endl;
   std::cout << "Result = " << res << std::endl;
}
int main(int argc, char* argv[])
{
   boost::thread workerThread(workFunc,"Welkom to my thread", 100);
   std::cout << "main() waiting for thread" << std::endl;
   workerThread.join();
   std::cout << "main() done" << std::endl;
   return 0;
}
