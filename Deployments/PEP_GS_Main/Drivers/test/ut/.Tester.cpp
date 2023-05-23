// ======================================================================
// \title  MathSender.hpp
// \author noahbraasch
// \brief  cpp file for MathSender test harness implementation class
// ======================================================================

#include "Tester.hpp"
#include "STest/Pick/Pick.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
      MathSenderGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      component("MathSender")
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------
  
  void Tester :: testResult()
  {
    const F32 result = 10.0;
    this->clearHistory();
    this->invoke_to_mathResultIn(0, result);
    this->component.doDispatch();
    ASSERT_TLM_SIZE(1);
    ASSERT_TLM_RESULT_SIZE(1);
    ASSERT_TLM_RESULT(0, result);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_RESULT_SIZE(1);
    ASSERT_EVENTS_RESULT(0, result);
  }

  void Tester :: testAddCommand()
  {
    this->testDoMath(MathOp::ADD);
  }

  void Tester :: testSubCommand()
  {
    this->testDoMath(MathOp::SUB);
  }

  void Tester :: testMulCommand()
  {
    this->testDoMath(MathOp::MUL);
  }

  void Tester:: testDivCommand()
  {
    this->testDoMath(MathOp::DIV);
  }

  void Tester ::
    testDoMath(MathOp Op)
  {
    // Pick values
    const F32 val1 = 2.0;
    const F32 val2 = 3.0;

    // Send command

    // Pick command sequence number?
    const U32 cmdSeq = 10;
    // Send command
    this->sendCmd_DO_MATH(0, cmdSeq, val1, Op, val2);
    // Dispatch command
    this->component.doDispatch();

    // This above section is the thing we are testing

    // Assertions
    
    // Verify CMD response
    ASSERT_CMD_RESPONSE_SIZE(1);

    // Verify command response was correct
    ASSERT_CMD_RESPONSE(0, MathSenderComponentBase::OPCODE_DO_MATH, cmdSeq, Fw::CmdResponse::OK);

    // Verify port was invoked
    ASSERT_FROM_PORT_HISTORY_SIZE(1);
    // Verify that math was invoked once
    ASSERT_from_mathOpOut_SIZE(1);
    // Verify that arguments are correct
    ASSERT_from_mathOpOut(0, val1, Op, val2)

    // Verify telemetry
    // verify 3 channels written
    ASSERT_TLM_SIZE(3);
    //Verify that values were sent once
    ASSERT_TLM_VAL1_SIZE(1);
    ASSERT_TLM_VAL2_SIZE(1);
    ASSERT_TLM_OP_SIZE(1);
    // Verify correct values
    ASSERT_TLM_VAL1(0, val1);
    ASSERT_TLM_VAL2(0, val2);
    ASSERT_TLM_OP(0, Op);

    // Verify event reports
    // very only one event was sent
    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_COMMAND_RECV_SIZE(1);
    ASSERT_EVENTS_COMMAND_RECV(0, val1, Op, val2);
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_mathOpOut_handler(
        const NATIVE_INT_TYPE portNum,
        F32 val1,
        const Ref::MathOp &op,
        F32 val2
    )
  {
    this->pushFromPortEntry_mathOpOut(val1, op, val2);
  }


} // end namespace Ref
