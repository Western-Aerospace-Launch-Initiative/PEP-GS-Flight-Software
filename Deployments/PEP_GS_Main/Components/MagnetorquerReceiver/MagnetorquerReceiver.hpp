// ======================================================================
// \title  MagnetorquerReceiver.hpp
// \author noahbraasch
// \brief  hpp file for MagnetorquerReceiver component implementation class
// ======================================================================

#ifndef MagnetorquerReceiver_HPP
#define MagnetorquerReceiver_HPP

#include "PEP_GS_Main/Components/MagnetorquerReceiver/MagnetorquerReceiverComponentAc.hpp"

namespace PEP_GS_Main {

  class MagnetorquerReceiver :
    public MagnetorquerReceiverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object MagnetorquerReceiver
      //!
      MagnetorquerReceiver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object MagnetorquerReceiver
      //!
      ~MagnetorquerReceiver();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for torquerParamsIn
      //!
      void torquerParamsIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 Nodeid, /*!< 
      Node id for torquer
      */
          F64 TorquerX, /*!< 
      X torquer duty cycle
      */
          F64 TorquerY, /*!< 
      Y Torquer duty cycle
      */
          F64 TorquerZ /*!< 
      Z torquer duty cycle
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for TODO command handler
      //! 
      void TODO_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace PEP_GS_Main

#endif
