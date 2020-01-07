#pragma once

#include <MessagingPattern/ZMqCommunicator.hpp>

class ZMqReqRespCommunicator final: public ZMqCommunicator
{
public:
   ZMqReqRespCommunicator(zmq::socket_type messageType);

   void setupSend(const std::string& address) override;
   void setupReceive(const std::string& address) override;
   bool send(const std::string &address, const HDLCFrameBodyPtr frame) override;
   HDLCFramePtr receive(const std::string &address) override;
   virtual ~ZMqReqRespCommunicator();

private:
   const std::string tcpPortAddressHeader;
   std::string tcpPortAddress;
};
