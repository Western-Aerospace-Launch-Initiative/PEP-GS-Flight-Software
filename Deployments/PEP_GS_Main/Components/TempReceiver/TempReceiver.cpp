// ======================================================================
// \title  TempReceiver.cpp
// \author noahbraasch
// \brief  cpp file for TempReceiver component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/TempReceiver/TempReceiver.hpp>
#include <FpConfig.hpp>
extern "C" {
    #include "../../libs/MCP9600/src/MCP9600.h"
}
namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  TempReceiver ::
    TempReceiver(
        const char *const compName
    ) : TempReceiverComponentBase(compName)
  {
    
  }

  TempReceiver ::
    ~TempReceiver()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void TempReceiver ::
    thermocoupleIdIn_handler(
        const NATIVE_INT_TYPE portNum,
        const id_stringString &id_string
    )
  {
      i2c_thermocouple* device;
      device = mcp_thermocouple_init(2,0x60,K_TYPE,"Test");
   bool enabled = true;
    F32 temp = 32.0;
    U8 status = 0x65;
    this->EnabledOut_out(0, enabled);
    this->TempOut_out(0, temp);
    this->statusOut_out(0, status); 
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void TempReceiver ::
    TODO_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
