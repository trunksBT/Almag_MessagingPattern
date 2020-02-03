#include "ZMqReqRepPrimaryStrategy.hpp"
#include <chrono>
#include <thread>
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>

using namespace convert;
using namespace std::chrono_literals;

ZMqReqRepPrimaryStrategy::ZMqReqRepPrimaryStrategy(zmq::socket_type messageType)
   : ZMqCommunicator{messageType}
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
   LOG(info) << "on " << tcpPortAddress;
   socket_.connect(tcpPortAddress);
}

void ZMqReqRepPrimaryStrategy::setupReceive(const std::string& address)
{
   throw std::runtime_error("Redundant function");
}

bool ZMqReqRepPrimaryStrategy::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   const std::string sentMessage = toString(HDLCFrame{ frame }.build());
   LOG(info) << sentMessage;
   return s_send(socket_, sentMessage);
}

HDLCFramePtr ZMqReqRepPrimaryStrategy::receive(const std::string &address)
{
   std::string message = s_recv(socket_);
   auto recFrame{
           std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   LOG(info) << toString(recFrame->build());
   return recFrame;
}

HDLCFramePtr ZMqReqRepPrimaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(debug) << "on " << tcpPortAddress;
   send(tcpPortAddress, frame);
   std::this_thread::sleep_for(1s);
   return receive(tcpPortAddress);
}
