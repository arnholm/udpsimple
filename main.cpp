#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "udp_sender.h"
#include "udp_receiver.h"

// sample program to demonstrate udp_sender/udp_receiver

int main(int argc, char **argv)
{
   if(argc < 2) {
      std::cout << "Insufficient arguments provided, please use one of" << std::endl;
      std::cout << "   -s <ip-receiver>  : send" << std::endl;
      std::cout << "   -r                : receive" << std::endl;
      return 1;
   }
   std::string arg(argv[1]);

   if(arg == "-s" && argc >=3 ) {
      // SENDER
      // ========

      // ip-address for receiver
      std::string ipaddress(argv[2]);

      // loop and send a message every second forever
      udp_sender udp(ipaddress);
      size_t counter=0;
      while(true) {
         std::string msg = "Hello from udp_sender " + std::to_string(++counter);
         std::cout << "Sending: " << msg << std::endl;

         udp.send(msg);
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }

   }
   else if(arg == "-r") {

      // RECEIVER
      // ========
      try  {
         udp_receiver receiver;
         receiver.receive(std::make_shared<udp_consumer>());
      }
      catch (std::exception& e)  {
         std::cerr << e.what() << std::endl;
      }
   }
   else {
      std::cout << "Invalid or insufficient arguments provided '"+arg+"', please use one of" << std::endl;
      std::cout << "   -s <ip-receiver>  : send" << std::endl;
      std::cout << "   -r                : receive" << std::endl;
      return 1;
   }

   return 0;
}


