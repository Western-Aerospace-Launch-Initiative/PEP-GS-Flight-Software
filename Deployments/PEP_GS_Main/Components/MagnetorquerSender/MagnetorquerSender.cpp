// ======================================================================
// \title  MagnetorquerSender.cpp
// \author noahbraasch
// \brief  cpp file for MagnetorquerSender component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/MagnetorquerSender/MagnetorquerSender.hpp>
#include <FpConfig.hpp>

namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  MagnetorquerSender ::
    MagnetorquerSender(
        const char *const compName
    ) : MagnetorquerSenderComponentBase(compName)
  {

  }

  MagnetorquerSender ::
    ~MagnetorquerSender()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void MagnetorquerSender ::
    torquerResultIn_handler(
        const NATIVE_INT_TYPE portNum,
        U16 TorquerReturnVal
    )
  {
    this->log_ACTIVITY_HI_RESULT(TorquerReturnVal);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void MagnetorquerSender ::
    SET_DUTY_CYCLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 nodeid,
        F64 torquerX,
        F64 torquerY,
        F64 torquerZ
    )
  {
    this->torquerParamsOut_out(0, nodeid, torquerX, torquerY, torquerZ);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
