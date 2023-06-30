// ======================================================================
// \title  WheelReceiver.cpp
// \author noahbraasch
// \brief  cpp file for WheelReceiver component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/WheelReceiver/WheelReceiver.hpp>
#include <FpConfig.hpp>
#include "bootloader.h"
#include "common.h"
#include "cubeacp.h"
#include "cubeadcs.h"

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
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void WheelReceiver ::
    wheelParamsIn_handler(
        const NATIVE_INT_TYPE portNum,
        U8 Nodeid,
        I16 Xspeed,
        I16 Yspeed,
        I16 Zspeed
    )
  {
    // Do we need to Set the speed and then say "go"? Not sure.
    CUBEACP_WheelSpeedCmd_t params = {Xspeed, Yspeed, Zspeed};
    U16 result = CUBEACP_FormatWheelSpeedCmdCmd(&Nodeid, &params);
    this->wheelResultOut_out(0, result);
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
