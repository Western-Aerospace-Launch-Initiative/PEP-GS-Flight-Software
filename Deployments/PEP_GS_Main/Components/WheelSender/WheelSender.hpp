// ======================================================================
// \title  WheelSender.hpp
// \author noahbraasch
// \brief  hpp file for WheelSender component implementation class
// ======================================================================

#ifndef WheelSender_HPP
#define WheelSender_HPP

#include "PEP_GS_Main/Components/WheelSender/WheelSenderComponentAc.hpp"

namespace PEP_GS_Main {

  class WheelSender :
    public WheelSenderComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object WheelSender
      //!
      WheelSender(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object WheelSender
      //!
      ~WheelSender();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SET_SPEED command handler
      //! Set wheel speed
      void SET_SPEED_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 nodeid, /*!< 
          ID for wheels
          */
          I16 xspeed, /*!< 
          Speed for x wheels
          */
          I16 yspeed, /*!< 
          Speed for y wheels
          */
          I16 zspeed /*!< 
          Speed for z wheels
          */
      );


    };

} // end namespace PEP_GS_Main

#endif
