// ======================================================================
// \title  TempSender.cpp
// \author noahbraasch
// \brief  cpp file for TempSender component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/TempSender/TempSender.hpp>
#include <FpConfig.hpp>

namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  TempSender ::
    TempSender(
        const char *const compName
    ) : TempSenderComponentBase(compName)
  {

  }

  TempSender ::
    ~TempSender()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void TempSender ::
    EnabledIn_handler(
        const NATIVE_INT_TYPE portNum,
        bool enabled
    )
  {
    // TODO
  }

  void TempSender ::
    TempIn_handler(
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    // TODO
  }

  void TempSender ::
    statusIn_handler(
        const NATIVE_INT_TYPE portNum,
        U8 statusID
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void TempSender ::
    ENABLE_THERMOCOUPLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& identifier
    )
  {
    this->log_ACTIVITY_LO_THERMOCOUPLE_ENABLED(identifier);
    this->thermocoupleIdOut_out(0, identifier);  
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void TempSender ::
    DISABLE_THERMOCOUPLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& identifier
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void TempSender ::
    GET_TEMPERATURE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& identifier
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void TempSender ::
    GET_STATUS_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& identifier
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
