// ======================================================================
// \title  MathSender/test/ut/Tester.hpp
// \author noahbraasch
// \brief  hpp file for MathSender test harness implementation class
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "Drivers/MCP9600.c"

namespace Ref {

  class Tester :
    public MathSenderGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:
      // Maximum size of histories storing events, telemetry, and port outputs
      static const NATIVE_INT_TYPE MAX_HISTORY_SIZE = 10;
      // Instance ID supplied to the component instance under test
      static const NATIVE_INT_TYPE TEST_INSTANCE_ID = 0;
      // Queue depth supplied to component instance under test
      static const NATIVE_INT_TYPE TEST_INSTANCE_QUEUE_DEPTH = 10;

      //! Construct object Tester
      //!
      Tester();

      //! Destroy object Tester
      //!
      ~Tester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      //!
      void testAddCommand(); 
      void testSubCommand();
      void testMulCommand();
      void testDivCommand();
      void testResult();

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_mathOpOut
      //!
      void from_mathOpOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 val1, /*!< 
      Operand one
      */
          const Ref::MathOp &op, /*!< 
      Operation
      */
          F32 val2 /*!< 
      second operand
      */
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

      void testDoMath(MathOp Op);

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      MathSender component;

  };

} // end namespace Ref

#endif
