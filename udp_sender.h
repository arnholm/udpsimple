#ifndef UDP_SENDER_H
#define UDP_SENDER_H

#include "udp_config.h"
#include <boost/asio.hpp>


/*
// example use

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "udp_sender.h"

int main()
{
   // send message to 127.0.0.1 port 10253
   udp_sender udp("127.0.0.1", 10253);

   // just loop and send a message every second forever
   size_t counter=0;
   while(true) {
      udp.send("udp_sender " + std::to_string(++counter));
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   }
}
*/


// udp_sender sends single UDP messages to remote IP and port
class udp_sender {
public:
   // udp_port = remote UDP port (on receiving end)
	udp_sender(const std::string& ipaddress, int udp_port = 10253)
	: m_ipaddress(ipaddress)
	, m_udp_port(udp_port)
   , m_io_service()
	, m_socket(m_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
	, m_receiver_endpoint(boost::asio::ip::address::from_string(ipaddress), udp_port)
	{}

	virtual ~udp_sender()
	{
		m_socket.close();
	}

	// send a single string as UDP message
	void send(const std::string& msg)
	{
		m_socket.send_to(boost::asio::buffer(msg, msg.size()), m_receiver_endpoint);
	}

private:
   std::string                     m_ipaddress;         // remote IP-address (on receiving end)
   int                             m_udp_port;          // remote UDP port (on receiving end)
	boost::asio::io_service         m_io_service;
	boost::asio::ip::udp::socket    m_socket;            // socket used for communication
	boost::asio::ip::udp::endpoint  m_receiver_endpoint; // remote endpoint (on receiving end)
};

#endif // UDP_SENDER_H

