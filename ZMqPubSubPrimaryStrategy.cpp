#include "ZMqPubSubPrimaryStrategy.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <Utils/Functions.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>

using namespace convert;

ZMqPubSubPrimaryStrategy::ZMqPubSubPrimaryStrategy(zmq::socket_type messageType)
   : ZMqCommunicator{messageType}
{
   LOG(trace);
}

ZMqPubSubPrimaryStrategy::~ZMqPubSubPrimaryStrategy()
{
   LOG(trace);
}

void ZMqPubSubPrimaryStrategy::setupSend(const std::string& address)
{
   tcpPortAddress = tcpPortAddressHeader + address;
   LOG(info) << "on " << tcpPortAddress;
   socket_.bind(tcpPortAddress);
}

void ZMqPubSubPrimaryStrategy::setupReceive(const std::string& address)
{
   throw std::runtime_error("Redundant function");
}

bool ZMqPubSubPrimaryStrategy::send(const std::string& address, HDLCFrameBodyPtr frame)
{
   bool sentState{ true };
   const std::string sentMessage = toString(HDLCFrame{ frame }.build());
   LOG(info) << sentMessage;

   sentState &= s_send(socket_, "dupa", zmq::send_flags::sndmore);
   sentState &= s_send(socket_, sentMessage);

   return sentState;
}

HDLCFramePtr ZMqPubSubPrimaryStrategy::receive(const std::string &address)
{
   throw std::runtime_error("Redundant function");
}

HDLCFramePtr ZMqPubSubPrimaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(debug) << "on " << address;
   setupSend(address);
   send(address, frame);
   return nullptr;
}
