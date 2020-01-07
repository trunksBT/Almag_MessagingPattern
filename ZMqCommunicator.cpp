#include "ZMqCommunicator.hpp"

namespace{ constexpr int NUM_OF_IO_THREADS = 1; }

ZMqCommunicator::ZMqCommunicator(zmq::socket_type messageType)
   : context_{NUM_OF_IO_THREADS}
   , socket_{context_, messageType}
{
   LOG(trace);
}

ZMqCommunicator::~ZMqCommunicator()
{
   LOG(trace);
}
