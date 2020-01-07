#include "ZMqReqRepPrimaryStrategy.hpp"
#include <chrono>
#include <thread>
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>
#include <Utils/Utils.hpp>
#include <Utils/PrintUtils.hpp>

using namespace convert;
using namespace printUtils;
using namespace std::chrono_literals;

ZMqReqRepPrimaryStrategy::ZMqReqRepPrimaryStrategy(zmq::socket_type messageType)
   : ZMqCommunicator{messageType}
   , tcpPortAddressHeader{"tcp://127.0.0.1:"}
   , tcpPortAddress{defaultVals::FOR_STRING}
{
   LOG(trace);
}

ZMqReqRepPrimaryStrategy::~ZMqReqRepPrimaryStrategy()
{
   LOG(trace);
}

void ZMqReqRepPrimaryStrategy::setupSend(const std::string& address)
{
   tcpPortAddress = tcpPortAddressHeader + address;
   LOG(debug) << "on " << tcpPortAddress;
   socket_.connect(tcpPortAddress);
}

void ZMqReqRepPrimaryStrategy::setupReceive(const std::string& address)
{
   throw std::runtime_error("Redundant function");
}

bool ZMqReqRepPrimaryStrategy::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   const std::string sentMessage = toString(frame->build());
   LOG(debug) << "Message: " << sentMessage;
   return s_send(socket_, sentMessage);
}

HDLCFramePtr ZMqReqRepPrimaryStrategy::receive(const std::string &address)
{
   std::string message = s_recv(socket_);
   auto recFrame{
           std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   printFrame("Received Message: ", recFrame->build());
   return recFrame;
}

HDLCFramePtr ZMqReqRepPrimaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(debug) << "on " << tcpPortAddress;
   send(tcpPortAddress, frame);
   std::this_thread::sleep_for(1s);
   receive(tcpPortAddress);
   return nullptr;
}
