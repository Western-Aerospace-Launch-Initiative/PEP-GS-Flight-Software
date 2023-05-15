// ======================================================================
// \title  TlmPortAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for Tlm port
// ======================================================================

#include "F-Prime/Fw/Tlm/TlmPortAc.hpp"
#include "Fw/Types/Assert.hpp"
#include "Fw/Types/StringUtils.hpp"

namespace Fw {

  namespace {

    // ----------------------------------------------------------------------
    // Port buffer class
    // ----------------------------------------------------------------------

    class TlmPortBuffer : public Fw::SerializeBufferBase {

      public:

        NATIVE_UINT_TYPE getBuffCapacity() const {
          return InputTlmPort::SERIALIZED_SIZE;
        }

        U8* getBuffAddr() {
          return m_buff;
        }

        const U8* getBuffAddr() const {
          return m_buff;
        }

      private:

        U8 m_buff[InputTlmPort::SERIALIZED_SIZE];

    };

  }

  // ----------------------------------------------------------------------
  // Input Port Member functions
  // ----------------------------------------------------------------------

  InputTlmPort ::
    InputTlmPort() :
      Fw::InputPortBase(),
      m_func(nullptr)
  {

  }

  void InputTlmPort ::
    init()
  {
    Fw::InputPortBase::init();
  }

  void InputTlmPort ::
    addCallComp(
        Fw::PassiveComponentBase* callComp,
        CompFuncPtr funcPtr
    )
  {
    FW_ASSERT(callComp != nullptr);
    FW_ASSERT(funcPtr != nullptr);

    this->m_comp = callComp;
    this->m_func = funcPtr;
    this->m_connObj = callComp;
  }

  void InputTlmPort ::
    invoke(
        FwChanIdType id,
        Fw::Time& timeTag,
        Fw::TlmBuffer& val
    )
  {
#if FW_PORT_TRACING == 1
    this->trace();
#endif

    FW_ASSERT(this->m_comp != nullptr);
    FW_ASSERT(this->m_func != nullptr);

    return this->m_func(this->m_comp, this->m_portNum, id, timeTag, val);
  }

#if FW_PORT_SERIALIZATION == 1

  Fw::SerializeStatus InputTlmPort ::
    invokeSerial(Fw::SerializeBufferBase& _buffer)
  {
    Fw::SerializeStatus _status;

#if FW_PORT_SERIALIZATION == 1
    this->trace();
#endif

    FW_ASSERT(this->m_comp != nullptr);
    FW_ASSERT(this->m_func != nullptr);

    FwChanIdType id;
    _status = _buffer.deserialize(id);
    if (_status != Fw::FW_SERIALIZE_OK) {
      return _status;
    }

    Fw::Time timeTag;
    _status = _buffer.deserialize(timeTag);
    if (_status != Fw::FW_SERIALIZE_OK) {
      return _status;
    }

    Fw::TlmBuffer val;
    _status = _buffer.deserialize(val);
    if (_status != Fw::FW_SERIALIZE_OK) {
      return _status;
    }

    this->m_func(this->m_comp, this->m_portNum, id, timeTag, val);

    return Fw::FW_SERIALIZE_OK;
  }

#endif

  // ----------------------------------------------------------------------
  // Output Port Member functions
  // ----------------------------------------------------------------------

  OutputTlmPort ::
    OutputTlmPort() :
      Fw::OutputPortBase(),
      m_port(nullptr)
  {

  }

  void OutputTlmPort ::
    init()
  {
    Fw::OutputPortBase::init();
  }

  void OutputTlmPort ::
    addCallPort(InputTlmPort* callPort)
  {
    FW_ASSERT(callPort != nullptr);

    this->m_port = callPort;
    this->m_connObj = callPort;

#if FW_PORT_SERIALIZATION == 1
    this->m_serPort = nullptr;
#endif
  }

  void OutputTlmPort ::
    invoke(
        FwChanIdType id,
        Fw::Time& timeTag,
        Fw::TlmBuffer& val
    )
  {
#if FW_PORT_TRACING == 1
    this->trace();
#endif

#if FW_PORT_SERIALIZATION
    FW_ASSERT((this->m_port != nullptr) || (this->m_serPort != nullptr));

    if (this->m_port != nullptr) {
      this->m_port->invoke(id, timeTag, val);
    }
    else {
      Fw::SerializeStatus _status;
      TlmPortBuffer _buffer;

      _status = _buffer.serialize(id);
      FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

      _status = _buffer.serialize(timeTag);
      FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

      _status = _buffer.serialize(val);
      FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

      _status = this->m_serPort->invokeSerial(_buffer);
      FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));
    }
#else
    FW_ASSERT(this->m_port != nullptr);
    this->m_port->invoke(id, timeTag, val);
#endif
  }

}
