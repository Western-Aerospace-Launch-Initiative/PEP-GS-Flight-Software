// ======================================================================
// \title  Ports_RateGroupsEnumAc.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for Ports_RateGroups enum
// ======================================================================

#ifndef PEP_GS_Main_Ports_RateGroupsEnumAc_HPP
#define PEP_GS_Main_Ports_RateGroupsEnumAc_HPP

#include "FpConfig.hpp"
#include "Fw/Types/Serializable.hpp"
#include "Fw/Types/String.hpp"

namespace PEP_GS_Main {

  class Ports_RateGroups :
    public Fw::Serializable
  {

    public:

      // ----------------------------------------------------------------------
      // Types
      // ----------------------------------------------------------------------

      //! The serial representation type
      typedef I32 SerialType;

      //! The raw enum type
      enum T {
        rateGroup1 = 0,
        rateGroup2 = 1,
        rateGroup3 = 2,
      };

      //! For backwards compatibility
      typedef T t;

    public:

      // ----------------------------------------------------------------------
      // Constants
      // ----------------------------------------------------------------------

      enum {
        //! The size of the serial representation
        SERIALIZED_SIZE = sizeof(SerialType),
        //! The number of enumerated constants
        NUM_CONSTANTS = 3,
      };

    public:

      // ----------------------------------------------------------------------
      // Constructors
      // ----------------------------------------------------------------------

      //! Constructor (default value of rateGroup1)
      Ports_RateGroups()
      {
        this->e = rateGroup1;
      }

      //! Constructor (user-provided value)
      Ports_RateGroups(
          const T e //!< The raw enum value
      )
      {
        this->e = e;
      }

      //! Copy constructor
      Ports_RateGroups(
          const Ports_RateGroups& obj //!< The source object
      )
      {
        this->e = obj.e;
      }

    public:

      // ----------------------------------------------------------------------
      // Operators
      // ----------------------------------------------------------------------

      //! Copy assignment operator (object)
      Ports_RateGroups& operator=(
          const Ports_RateGroups& obj //!< The source object
      );

      //! Copy assignment operator (raw enum)
      Ports_RateGroups& operator=(
          T e //!< The enum value
      );

      //! Conversion operator
      operator T() const
      {
        return this->e;
      }

      //! Equality operator
      bool operator==(T e) const
      {
        return this->e == e;
      }

      //! Inequality operator
      bool operator!=(T e) const
      {
        return !(*this == e);
      }

#ifdef BUILD_UT

      //! Ostream operator
      friend std::ostream& operator<<(
          std::ostream& os, //!< The ostream
          const Ports_RateGroups& obj //!< The object
      );

#endif

    public:

      // ----------------------------------------------------------------------
      // Member functions
      // ----------------------------------------------------------------------

      //! Check raw enum value for validity
      bool isValid() const;

      //! Serialize raw enum value to SerialType
      Fw::SerializeStatus serialize(
          Fw::SerializeBufferBase& buffer //!< The serial buffer
      ) const;

      //! Deserialize raw enum value from SerialType
      Fw::SerializeStatus deserialize(
          Fw::SerializeBufferBase& buffer //!< The serial buffer
      );

#if FW_SERIALIZABLE_TO_STRING || BUILD_UT

      //! Convert enum to string
      void toString(
          Fw::StringBase& sb //!< The StringBase object to hold the result
      ) const;

#endif

    public:

      // ----------------------------------------------------------------------
      // Member variables
      // ----------------------------------------------------------------------

      //! The raw enum value
      T e;

  };

}

#endif
