

#ifndef PEP_GS_MainPackets_header_h
#define PEP_GS_MainPackets_header_h

#include <Svc/TlmPacketizer/TlmPacketizerTypes.hpp>

namespace PEP_GS_Main {

    // set of packets to send
    extern const Svc::TlmPacketizerPacketList PEP_GS_MainPacketsPkts;
    // set of channels to ignore
    extern const Svc::TlmPacketizerPacket PEP_GS_MainPacketsIgnore;

}

#endif // PEP_GS_MainPackets_header_h

