// ======================================================================
// \title  MagnetorquerReceiver.cpp
// \author noahbraasch
// \brief  cpp file for MagnetorquerReceiver component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/MagnetorquerReceiver/MagnetorquerReceiver.hpp>
#include <FpConfig.hpp>
#include "bootloader.h"
#include "common.h"
#include "cubeacp.h"
#include "cubeadcs.h"

namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  MagnetorquerReceiver ::
    MagnetorquerReceiver(
        const char *const compName
    ) : MagnetorquerReceiverComponentBase(compName)
  {

  }

  MagnetorquerReceiver ::
    ~MagnetorquerReceiver()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void MagnetorquerReceiver ::
    torquerParamsIn_handler(
        const NATIVE_INT_TYPE portNum,
        U8 Nodeid,
        F64 TorquerX,
        F64 TorquerY,
        F64 TorquerZ
    )
  {
    CUBEACP_TorquerCmd_t params = {TorquerX, TorquerY, TorquerZ};
    U16 result = CUBEACP_FormatTorquerCmdCmd(&Nodeid, &params);
    this->torquerResultOut_out(0, result);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void MagnetorquerReceiver ::
    TODO_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
