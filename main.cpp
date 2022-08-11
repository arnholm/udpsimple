#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include "udp_sender.h"
#include "udp_receiver.h"

// sample program to demonstrate udp_sender/udp_receiver

int main(int argc, char **argv)
{
   int udp_port = 10253; // default UDP port

   if(argc < 2) {
      std::cout << "Insufficient arguments provided, please use one of (default port=10253):" << std::endl;
      std::cout << "   -s <ip-receiver>  [<port>] : send " << std::endl;
      std::cout << "   -r                [<port>] : receive " << std::endl;
      return 1;
   }
   std::string arg(argv[1]);

   if(arg == "-s" && argc >=3 ) {
      // SENDER
      // ========

      // ip-address for receiver
      std::string ipaddress(argv[2]);

      if(argc >=4) {
         std::istringstream inport(argv[3]);
         inport >> udp_port;
      }

      // loop and send a message every second forever
      udp_sender udp(ipaddress,udp_port);
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

      if(argc >=3) {
         std::istringstream inport(argv[2]);
         inport >> udp_port;
      }

      try  {
         udp_receiver receiver(udp_port);
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


