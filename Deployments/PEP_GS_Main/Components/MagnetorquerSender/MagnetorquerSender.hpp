// ======================================================================
// \title  MagnetorquerSender.hpp
// \author noahbraasch
// \brief  hpp file for MagnetorquerSender component implementation class
// ======================================================================

#ifndef MagnetorquerSender_HPP
#define MagnetorquerSender_HPP

#include "PEP_GS_Main/Components/MagnetorquerSender/MagnetorquerSenderComponentAc.hpp"

namespace PEP_GS_Main {

  class MagnetorquerSender :
    public MagnetorquerSenderComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object MagnetorquerSender
      //!
      MagnetorquerSender(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object MagnetorquerSender
      //!
      ~MagnetorquerSender();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for torquerResultIn
      //!
      void torquerResultIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 TorquerReturnVal /*!< 
      Return value for torquer command
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SET_DUTY_CYCLE command handler
      //! Set duty cycle
      void SET_DUTY_CYCLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 nodeid, /*!< 
          ID FOr torquer
          */
          F64 torquerX, 
          F64 torquerY, 
          F64 torquerZ 
      );


    };

} // end namespace PEP_GS_Main

#endif
