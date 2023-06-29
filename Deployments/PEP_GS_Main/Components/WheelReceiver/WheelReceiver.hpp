// ======================================================================
// \title  WheelReceiver.hpp
// \author noahbraasch
// \brief  hpp file for WheelReceiver component implementation class
// ======================================================================

#ifndef WheelReceiver_HPP
#define WheelReceiver_HPP

#include "PEP_GS_Main/Components/WheelReceiver/WheelReceiverComponentAc.hpp"

namespace PEP_GS_Main {

  class WheelReceiver :
    public WheelReceiverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object WheelReceiver
      //!
      WheelReceiver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object WheelReceiver
      //!
      ~WheelReceiver();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for wheelParamsIn
      //!
      void wheelParamsIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 Nodeid, /*!< 
      node id for wheels
      */
          I16 Xspeed, /*!< 
      Speed for x wheels
      */
          I16 Yspeed, /*!< 
      Speed for Y wheels
      */
          I16 Zspeed /*!< 
      Speed for z wheels
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
