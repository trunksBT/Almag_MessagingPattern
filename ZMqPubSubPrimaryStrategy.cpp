#include "ZMqPubSubPrimaryStrategy.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <Utils/Functions.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>

using namespace convert;

namespace
{
constexpr uint8_t IS_ON{ 1 };
}

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
   LOG(debug) << "on " << address;
   socket_.bind("ipc://" + address);
}

void ZMqPubSubPrimaryStrategy::setupReceive(const std::string& address)
{
   LOG(debug) << "on " << address;
   throw std::runtime_error("Redundant function");
}

bool ZMqPubSubPrimaryStrategy::send(const std::string& address, HDLCFrameBodyPtr frame)
{
   bool sentState{ true };
   const std::string sentMessage = toString(frame->build());
   LOG(debug) << "Message: " << sentMessage;

   sentState &= s_send(socket_, sentMessage);
   sentState &= s_send(socket_, sentMessage, zmq::send_flags::sndmore);
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
