// ======================================================================
// \title  WheelReceiver.cpp
// \author noahbraasch
// \brief  cpp file for WheelReceiver component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/WheelReceiver/WheelReceiver.hpp>
#include <FpConfig.hpp>

namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  WheelReceiver ::
    WheelReceiver(
        const char *const compName
    ) : WheelReceiverComponentBase(compName)
  {

  }

  WheelReceiver ::
    ~WheelReceiver()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void WheelReceiver ::
    TODO_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
