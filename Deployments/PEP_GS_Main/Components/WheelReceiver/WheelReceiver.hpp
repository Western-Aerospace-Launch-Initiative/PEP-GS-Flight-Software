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
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for TODO command handler
      //! TODO
      void TODO_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace PEP_GS_Main

#endif
