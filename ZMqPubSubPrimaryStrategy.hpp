#pragma once

#include <MessagingPattern/ZMqCommunicator.hpp>

class ZMqPubSubPrimaryStrategy final: public ZMqCommunicator
{
public:
   ZMqPubSubPrimaryStrategy(zmq::socket_type messageType);

   void setupSend(const std::string& address) override;
   void setupReceive(const std::string& address) override;
   bool send(const std::string &address, const HDLCFrameBodyPtr frame) override;
   HDLCFramePtr receive(const std::string &address) override;
   HDLCFramePtr communicate(const std::string& address, HDLCFrameBodyPtr frame) override;

   virtual ~ZMqPubSubPrimaryStrategy();

private:
   const std::string tcpPortAddressHeader;
   std::string tcpPortAddress;
};
