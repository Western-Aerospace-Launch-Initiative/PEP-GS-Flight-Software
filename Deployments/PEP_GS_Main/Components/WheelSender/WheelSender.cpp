// ======================================================================
// \title  WheelSender.cpp
// \author noahbraasch
// \brief  cpp file for WheelSender component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/WheelSender/WheelSender.hpp>
#include <FpConfig.hpp>

namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  WheelSender ::
    WheelSender(
        const char *const compName
    ) : WheelSenderComponentBase(compName)
  {

  }

  WheelSender ::
    ~WheelSender()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void WheelSender ::
    SET_SPEED_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 nodeid,
        I16 xspeed,
        I16 yspeed,
        I16 zspeed
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
