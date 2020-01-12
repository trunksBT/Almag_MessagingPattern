#include "ZMqCommunicator.hpp"
#include <Utils/Utils.hpp>

namespace{ constexpr int NUM_OF_IO_THREADS = 1; }

ZMqCommunicator::ZMqCommunicator(zmq::socket_type messageType)
   : context_{NUM_OF_IO_THREADS}
   , socket_{context_, messageType}
   , tcpPortAddressHeader{"tcp://127.0.0.1:"}
   , tcpPortAddress{defaultVals::FOR_STRING}
{
   LOG(trace);
}

ZMqCommunicator::~ZMqCommunicator()
{
   LOG(trace);
}
