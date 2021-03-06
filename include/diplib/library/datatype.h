/*
 * DIPlib 3.0
 * This file contains definitions for the DataType class and support functions.
 *
 * (c)2014-2017, Cris Luengo.
 * Based on original DIPlib code: (c)1995-2014, Delft University of Technology.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


//
// NOTE!
// This file is included through diplib.h -- no need to include directly
//


#ifndef DIP_DATATYPE_H
#define DIP_DATATYPE_H

#include "diplib/library/types.h"


/// \file
/// \brief The `dip::DataType` class and support functions. This file is always included through `diplib.h`.
/// \see infrastructure


namespace dip {


/// \defgroup types Pixel data types
/// \brief Types used for image samples (pixels), and related support functionality
///
/// The following table lists all supported sample data types, together with `dip::DataType` constants and type
/// groups (see `dip::DataType::Classes`) that they belong to.
///
/// C++ type        | Constant                 | Type groups
/// --------------- | ------------------------ | -------------------------------------------------
/// `dip::bin`      | `dip::DT_BIN`            | `Binary`, `IntOrBin`, `FlexBin`, `Unsigned`
/// `dip::uint8`    | `dip::DT_UINT8`          | `UInt`, `Integer`, `IntOrBin`, `Real`, `Unsigned`
/// `dip::uint16`   | `dip::DT_UINT16`         | `UInt`, `Integer`, `IntOrBin`, `Real`, `Unsigned`
/// `dip::uint32`   | `dip::DT_UINT32`         | `UInt`, `Integer`, `IntOrBin`, `Real`, `Unsigned`
/// `dip::sint8`    | `dip::DT_SINT8`          | `SInt`, `Integer`, `IntOrBin`, `Real`, `Signed`
/// `dip::sint16`   | `dip::DT_SINT16`         | `SInt`, `Integer`, `IntOrBin`, `Real`, `Signed`
/// `dip::sint32`   | `dip::DT_SINT32`         | `SInt`, `Integer`, `IntOrBin`, `Real`, `Signed`
/// `dip::sfloat`   | `dip::DT_SFLOAT`         | `Float`, `Real`, `Flex`, `FlexBin`, `Signed`
/// `dip::dfloat`   | `dip::DT_DFLOAT`         | `Float`, `Real`, `Flex`, `FlexBin`, `Signed`
/// `dip::scomplex` | `dip::DT_SCOMPLEX`       | `Complex`, `Flex`, `FlexBin`, `Signed`
/// `dip::dcomplex` | `dip::DT_DCOMPLEX`       | `Complex`, `Flex`, `FlexBin`, `Signed`
///
/// \ingroup infrastructure
/// \{


//
// The DataType class.
//

/// \brief `%DataType` objects are used to indicate what the data type of
/// an image is.
///
/// It is a simple enumeration type, but with some added
/// member functions that can be used to query the data type. A series
/// of constant expressions have been defined that should be used when
/// specifying a data type or testing for specific data types:
/// * `dip::DT_BIN`
/// * `dip::DT_UINT8`
/// * `dip::DT_UINT16`
/// * `dip::DT_UINT32`
/// * `dip::DT_SINT8`
/// * `dip::DT_SINT16`
/// * `dip::DT_SINT32`
/// * `dip::DT_SFLOAT`
/// * `dip::DT_DFLOAT`
/// * `dip::DT_SCOMPLEX`
/// * `dip::DT_DCOMPLEX`
///
/// It is possible to call `%DataType` member functions on these constants:
///
/// ```cpp
///     dip::DT_BIN.SizeOf();
/// ```
struct DIP_NO_EXPORT DataType {

   enum class DT {
         BIN,
         UINT8,
         SINT8,
         UINT16,
         SINT16,
         UINT32,
         SINT32,
         SFLOAT,
         DFLOAT,
         SCOMPLEX,
         DCOMPLEX,
   } dt;

   struct DTString {
      // Undocumented, used to prevent typos in literal strings.
      constexpr static char const* BIN = "BIN";
      constexpr static char const* UINT8 = "UINT8";
      constexpr static char const* SINT8 = "SINT8";
      constexpr static char const* UINT16 = "UINT16";
      constexpr static char const* SINT16 = "SINT16";
      constexpr static char const* UINT32 = "UINT32";
      constexpr static char const* SINT32 = "SINT32";
      constexpr static char const* SFLOAT = "SFLOAT";
      constexpr static char const* DFLOAT = "DFLOAT";
      constexpr static char const* SCOMPLEX = "SCOMPLEX";
      constexpr static char const* DCOMPLEX = "DCOMPLEX";
   };

   constexpr DataType() : dt( DT::SFLOAT ) {}
   constexpr DataType( DT _dt ) : dt( _dt ) {}

   // This is to get the template below to not compile -- please ignore
   template< typename T >
   struct assert_false : std::false_type {};

   /// \brief Get the data type value of any expression, as long as that expression is of one of the known data types
   template< typename T >
   constexpr explicit DataType( T ) {
      // This constructor is not valid. Only the specializations towards the bottom of this file are.
      static_assert( assert_false< T >::value, "You need to cast your constant to one of the known data types" );
   }

   /// \brief A string can be cast to a data type. The recognized names are identical to the enumerator names in `dip::DataType::DT`.
   explicit DataType( String name ) {
      if( name == DTString::BIN      ) { dt = DT::BIN;      } else
      if( name == DTString::UINT8    ) { dt = DT::UINT8;    } else
      if( name == DTString::SINT8    ) { dt = DT::SINT8;    } else
      if( name == DTString::UINT16   ) { dt = DT::UINT16;   } else
      if( name == DTString::SINT16   ) { dt = DT::SINT16;   } else
      if( name == DTString::UINT32   ) { dt = DT::UINT32;   } else
      if( name == DTString::SINT32   ) { dt = DT::SINT32;   } else
      if( name == DTString::SFLOAT   ) { dt = DT::SFLOAT;   } else
      if( name == DTString::DFLOAT   ) { dt = DT::DFLOAT;   } else
      if( name == DTString::SCOMPLEX ) { dt = DT::SCOMPLEX; } else
      if( name == DTString::DCOMPLEX ) { dt = DT::DCOMPLEX; }
      else {
         DIP_THROW( "Illegal data type name: " + name );
      }
   }

   /// \brief Swaps the values of `this` and `other`
   void swap( DataType& other ) {
      using std::swap;
      swap( dt, other.dt );
   }

   /// \brief `%DataType` objects implicitly convert to the enumeration integer.
   constexpr operator int() const { return static_cast< int >( dt ); }   // This one allows the use of DataType in a switch() statement

   /// \brief `%DataType` objects can be compared.
   bool operator==( DataType other ) const { return dt == other.dt; }

   /// \brief Returns a C-style string constant with a representation of the data type name.
   char const* Name() const {
      switch( dt ) {
         case DT::BIN:      return DTString::BIN;
         case DT::UINT8:    return DTString::UINT8;
         case DT::SINT8:    return DTString::SINT8;
         case DT::UINT16:   return DTString::UINT16;
         case DT::SINT16:   return DTString::SINT16;
         case DT::UINT32:   return DTString::UINT32;
         case DT::SINT32:   return DTString::SINT32;
         case DT::SFLOAT:   return DTString::SFLOAT;
         case DT::DFLOAT:   return DTString::DFLOAT;
         case DT::SCOMPLEX: return DTString::SCOMPLEX;
         case DT::DCOMPLEX: return DTString::DCOMPLEX;
      };
      DIP_THROW( "Unknown data type" ); // This should never happen, but GCC complains.
   }

   /// \brief Returns the size in bytes of the data type.
   dip::uint SizeOf() const {
      switch( dt ) {
         case DT::BIN:      return sizeof( dip::bin );
         case DT::UINT8:    return sizeof( dip::uint8 );
         case DT::SINT8:    return sizeof( dip::sint8 );
         case DT::UINT16:   return sizeof( dip::uint16 );
         case DT::SINT16:   return sizeof( dip::sint16 );
         case DT::UINT32:   return sizeof( dip::uint32 );
         case DT::SINT32:   return sizeof( dip::sint32 );
         case DT::SFLOAT:   return sizeof( dip::sfloat );
         case DT::DFLOAT:   return sizeof( dip::dfloat );
         case DT::SCOMPLEX: return sizeof( dip::scomplex );
         case DT::DCOMPLEX: return sizeof( dip::dcomplex );
      };
      DIP_THROW( "Unknown data type" ); // This should never happen, but GCC complains.
   }

   /// \brief Returns true if the integer `value` is within the range representable by the data type.
   bool IsInRange( dip::sint value ) const {
      switch( dt ) {
         case DT::BIN:
            return ( value >= 0 ) && ( value <= 1 );
         case DT::UINT8:
            return ( value >= static_cast< dip::sint >( std::numeric_limits< uint8 >::min() ))
                && ( value <= static_cast< dip::sint >( std::numeric_limits< uint8 >::max() ));
         case DT::SINT8:
            return ( value >= static_cast< dip::sint >( std::numeric_limits< sint8 >::min() ))
                && ( value <= static_cast< dip::sint >( std::numeric_limits< sint8 >::max() ));
         case DT::UINT16:
            return ( value >= static_cast< dip::sint >( std::numeric_limits< uint16 >::min() ))
                && ( value <= static_cast< dip::sint >( std::numeric_limits< uint16 >::max() ));
         case DT::SINT16:
            return ( value >= static_cast< dip::sint >( std::numeric_limits< sint16 >::min() ))
                && ( value <= static_cast< dip::sint >( std::numeric_limits< sint16 >::max() ));
         case DT::UINT32:
            return ( value >= static_cast< dip::sint >( std::numeric_limits< uint32 >::min() ))
                && ( value <= static_cast< dip::sint >( std::numeric_limits< uint32 >::max() ));
         case DT::SINT32:
            return ( value >= static_cast< dip::sint >( std::numeric_limits< sint32 >::min() ))
                && ( value <= static_cast< dip::sint >( std::numeric_limits< sint32 >::max() ));
         default:
            return true;
      };
   }

   /// \brief Returns true if the integer `value` is within the range representable by the data type.
   bool IsInRange( dip::uint value ) const {
      switch( dt ) {
         case DT::BIN:
            return value <= 1;
         case DT::UINT8:
            return value <= static_cast< dip::uint >( std::numeric_limits< uint8 >::max() );
         case DT::SINT8:
            return value <= static_cast< dip::uint >( std::numeric_limits< sint8 >::max() );
         case DT::UINT16:
            return value <= static_cast< dip::uint >( std::numeric_limits< uint16 >::max() );
         case DT::SINT16:
            return value <= static_cast< dip::uint >( std::numeric_limits< sint16 >::max() );
         case DT::UINT32:
            return value <= static_cast< dip::uint >( std::numeric_limits< uint32 >::max() );
         case DT::SINT32:
            return value <= static_cast< dip::uint >( std::numeric_limits< sint32 >::max() );
         default:
            return true;
      };
   }

   /// \brief Returns the real data type corresponding to a complex data type
   DataType Real() {
      switch( dt ) {
         case DT::SCOMPLEX:
            return DT::SFLOAT;
         case DT::DCOMPLEX:
            return DT::DFLOAT;
         default:
            return dt;
      };
   }

   /// \class dip::DataType::Classes
   /// \brief Specifies a collection of data types.
   ///
   /// Valid values are:
   ///
   /// Classes constant | Definition
   /// ---------------- | ----------
   /// Class_Bin        | DT_BIN
   /// Class_UInt8      | DT_UINT8
   /// Class_SInt8      | DT_SINT8
   /// Class_UInt16     | DT_UINT16
   /// Class_SInt16     | DT_SINT16
   /// Class_UInt32     | DT_UINT32
   /// Class_SInt32     | DT_SINT32
   /// Class_SFloat     | DT_SFLOAT
   /// Class_DFloat     | DT_DFLOAT
   /// Class_SComplex   | DT_SCOMPLEX
   /// Class_DComplex   | DT_DCOMPLEX
   /// Class_Binary     | Class_Bin;
   /// Class_UInt       | Class_UInt8 + Class_UInt16 + Class_UInt32
   /// Class_SInt       | Class_SInt8 + Class_SInt16 + Class_SInt32
   /// Class_Integer    | Class_UInt + Class_SInt
   /// Class_IntOrBin   | Class_Integer + Class_Binary
   /// Class_Float      | Class_SFloat + Class_DFloat
   /// Class_Complex    | Class_SComplex + Class_DComplex
   /// Class_Flex       | Class_Float + Class_Complex
   /// Class_FlexBin    | Class_Flex + Class_Binary
   /// Class_Unsigned   | Class_Binary + Class_UInt
   /// Class_Signed     | Class_SInt + Class_Float + Class_Complex
   /// Class_Real       | Class_Integer + Class_Float
   /// Class_SignedReal | Class_SInt + Class_Float
   /// Class_NonBinary  | Class_Real + Class_Complex
   /// Class_NonComplex | Class_Binary + Class_Real
   /// Class_All        | Class_Binary + Class_Real + Class_Complex
   ///
   /// Note that you can add these constants together, for example `dip::DataType::Class_UInt8 + dip::DataType::Class_UInt16`.
   ///
   /// It is possible to see if an image is of a type within a collection using the `Contains` method of
   /// `%dip::DataType::Classes` with a `dip::DataType` as argument:
   /// ```cpp
   ///     if( dip::DataType::Class_Flex.Contains( image.DataType() )) { ... }
   /// ```
   /// But more convenient is to use the `dip::DataType.IsA` method:
   /// ```cpp
   ///     if( image.DataType().IsA( dip::DataType::Class_Flex )) { ... }
   /// ```
   /// This is equivalent to using one of the test functions, if defined for the specific group:
   /// ```cpp
   ///     if( image.DataType().IsFlex() ) { ... }
   /// ```
   ///
   /// The following combination of classes cover all data types, and are non-intersecting:
   /// - `Class_Unsigned` and `Class_Signed`
   /// - `Class_Complex` and `Class_NonComplex`
   /// - `Class_Binary` and `Class_NonBinary`
   /// - `Class_FlexBin` and `Class_Integer`
   /// - `Class_Flex` and `Class_IntOrBin`
   /// - `Class_Binary`, `Class_Real` and `Class_Complex`
   /// - `Class_Binary`, `Class_Integer`, `Class_Float` and `Class_Complex`
   using Classes = dip::detail::dip__Options< DT >;
   DIP_EXPORT constexpr static Classes Class_Bin = DT::BIN;
   DIP_EXPORT constexpr static Classes Class_UInt8 = DT::UINT8;
   DIP_EXPORT constexpr static Classes Class_SInt8 = DT::SINT8;
   DIP_EXPORT constexpr static Classes Class_UInt16 = DT::UINT16;
   DIP_EXPORT constexpr static Classes Class_SInt16 = DT::SINT16;
   DIP_EXPORT constexpr static Classes Class_UInt32 = DT::UINT32;
   DIP_EXPORT constexpr static Classes Class_SInt32 = DT::SINT32;
   DIP_EXPORT constexpr static Classes Class_SFloat = DT::SFLOAT;
   DIP_EXPORT constexpr static Classes Class_DFloat = DT::DFLOAT;
   DIP_EXPORT constexpr static Classes Class_SComplex = DT::SCOMPLEX;
   DIP_EXPORT constexpr static Classes Class_DComplex = DT::DCOMPLEX;
   DIP_EXPORT constexpr static Classes Class_Binary = Class_Bin;
   DIP_EXPORT constexpr static Classes Class_UInt = Class_UInt8 + Class_UInt16 + Class_UInt32;
   DIP_EXPORT constexpr static Classes Class_SInt = Class_SInt8 + Class_SInt16 + Class_SInt32;
   DIP_EXPORT constexpr static Classes Class_Integer = Class_UInt + Class_SInt;
   DIP_EXPORT constexpr static Classes Class_IntOrBin = Class_Integer + Class_Binary;
   DIP_EXPORT constexpr static Classes Class_Float = Class_SFloat + Class_DFloat;
   DIP_EXPORT constexpr static Classes Class_Complex = Class_SComplex + Class_DComplex;
   DIP_EXPORT constexpr static Classes Class_Flex = Class_Float + Class_Complex;
   DIP_EXPORT constexpr static Classes Class_FlexBin = Class_Flex + Class_Binary;
   DIP_EXPORT constexpr static Classes Class_Unsigned = Class_Binary + Class_UInt;
   DIP_EXPORT constexpr static Classes Class_Signed = Class_SInt + Class_Float + Class_Complex;
   DIP_EXPORT constexpr static Classes Class_Real = Class_Integer + Class_Float;
   DIP_EXPORT constexpr static Classes Class_SignedReal = Class_SInt + Class_Float;
   DIP_EXPORT constexpr static Classes Class_NonBinary = Class_Real + Class_Complex;
   DIP_EXPORT constexpr static Classes Class_NonComplex = Class_Binary + Class_Real;
   DIP_EXPORT constexpr static Classes Class_All = Class_Binary + Class_Real + Class_Complex; // == Class_Unsigned + Class_Signed

   /// \brief Implicit conversion to `dip::DataType::Classes` options class.
   constexpr operator Classes() const { return dt; }

   //
   // Functions to query the data type class
   //

   /// \brief Returns `true` if the data type is of the given class.
   constexpr bool IsA( Classes cls ) const {
      return cls.Contains( dt );
   }

   /// \brief Returns `true` if the data type is binary.
   constexpr bool IsBinary() const {
      return IsA( DT::BIN );
   }

   /// \brief Returns `true` if the data type is an unsigned integer type.
   constexpr bool IsUInt() const {
      return IsA( Class_UInt );
   }

   /// \brief Returns `true` if the data type is a signed integer type.
   constexpr bool IsSInt() const {
      return IsA( Class_SInt );
   }

   /// \brief Returns `true` if the data type is an integer type.
   constexpr bool IsInteger() const {
      return IsA( Class_Integer );
   }

   /// \brief Returns `true` if the data type is a floating point type.
   constexpr bool IsFloat() const {
      return IsA( Class_Float );
   }

   /// \brief Returns `true` if the data type is real (floating point or integer).
   constexpr bool IsReal() const {
      return IsA( Class_Real );
   }

   /// \brief Returns `true` if the data type is one of the "flex" types (floating point or complex).
   constexpr bool IsFlex() const {
      return IsA( Class_Flex );
   }

   /// \brief Returns `true` if the data type is floating point, complex or binary.
   constexpr bool IsFlexBin() const {
      return IsA( Class_FlexBin );
   }

   /// \brief Returns `true` if the data type is complex.
   constexpr bool IsComplex() const {
      return IsA( Class_Complex );
   }

   /// \brief Returns `true` if the data type is an unsigned type (binary or unsigned integer).
   constexpr bool IsUnsigned() const {
      return IsA( Class_Unsigned );
   }

   /// \brief Returns `true` if the data type is a signed type (signed integer, floating point or complex)
   constexpr bool IsSigned() const {
      return IsA( Class_Signed );
   }

   //
   // Functions to suggest an output data type for all types of filters and operators
   //

   /// \brief Returns an integer type that is most suitable to hold samples of `type`.
   DIP_EXPORT static DataType SuggestInteger( DataType type );

   /// \brief Returns an integer type that is most suitable to hold samples of `type`.
   DIP_EXPORT static DataType SuggestSigned( DataType type );

   /// \brief Returns a suitable floating-point type that can hold the samples of `type`.
   DIP_EXPORT static DataType SuggestFloat( DataType type );

   /// \brief Returns a suitable double precision floating-point type (real or complex) that can hold large sums of `type`.
   DIP_EXPORT static DataType SuggestDouble( DataType type );

   /// \brief Returns a suitable complex type that can hold the samples of `type`.
   DIP_EXPORT static DataType SuggestComplex( DataType type );

   /// \brief Returns a suitable floating-point or complex type that can hold the samples of `type`.
   DIP_EXPORT static DataType SuggestFlex( DataType type );

   /// \brief Returns a suitable floating-point, complex or binary type that can hold the samples of `type`.
   DIP_EXPORT static DataType SuggestFlexBin( DataType type );

   /// \brief Returns a suitable type that can hold samples of type `abs(type)`.
   DIP_EXPORT static DataType SuggestAbs( DataType type );

   /// \brief Returns a suitable real type that can hold the samples of `type`.
   DIP_EXPORT static DataType SuggestReal( DataType type );

   /// \brief Returns a suitable floating-point, complex or binary type (FlexBin) that can hold the result of an arithmetic computation performed with the two data types.
   DIP_EXPORT static DataType SuggestArithmetic( DataType type1, DataType type2 );

   /// \brief Returns a suitable type that can hold any samples of the two data types.
   DIP_EXPORT static DataType SuggestDyadicOperation( DataType type1, DataType type2 );

};

/// \brief You can output a `dip::Image` to `std::cout` or any other stream. Some
/// information about the image is printed.
inline std::ostream& operator<<( std::ostream& os, DataType type ) {
   os << type.Name();
   return os;
}

inline void swap( DataType& v1, DataType& v2 ) {
   v1.swap( v2 );
}

// This must be declared outside of the `DataType` class. See the definition of the `DIP_DECLARE_OPTIONS` macro.
constexpr DataType::Classes operator+( DataType::DT a, DataType::DT b ) { return DataType::Classes{ a } + b; }

// Here are the specializations for the templated constructor
template<> constexpr DataType::DataType( bin      ) : dt( DT::BIN      ) {}
template<> constexpr DataType::DataType( uint8    ) : dt( DT::UINT8    ) {}
template<> constexpr DataType::DataType( sint8    ) : dt( DT::SINT8    ) {}
template<> constexpr DataType::DataType( uint16   ) : dt( DT::UINT16   ) {}
template<> constexpr DataType::DataType( sint16   ) : dt( DT::SINT16   ) {}
template<> constexpr DataType::DataType( uint32   ) : dt( DT::UINT32   ) {}
template<> constexpr DataType::DataType( sint32   ) : dt( DT::SINT32   ) {}
template<> constexpr DataType::DataType( sfloat   ) : dt( DT::SFLOAT   ) {}
template<> constexpr DataType::DataType( dfloat   ) : dt( DT::DFLOAT   ) {}
template<> constexpr DataType::DataType( scomplex ) : dt( DT::SCOMPLEX ) {}
template<> constexpr DataType::DataType( dcomplex ) : dt( DT::DCOMPLEX ) {}

/// \brief An array to hold data types
using DataTypeArray = DimensionArray< DataType >;

//
// Constants that people will use where a DataType is needed
//

constexpr DataType DT_BIN{ DataType::DT::BIN };
constexpr DataType DT_UINT8{ DataType::DT::UINT8 };
constexpr DataType DT_SINT8{ DataType::DT::SINT8 };
constexpr DataType DT_UINT16{ DataType::DT::UINT16 };
constexpr DataType DT_SINT16{ DataType::DT::SINT16 };
constexpr DataType DT_UINT32{ DataType::DT::UINT32 };
constexpr DataType DT_SINT32{ DataType::DT::SINT32 };
constexpr DataType DT_SFLOAT{ DataType::DT::SFLOAT };
constexpr DataType DT_DFLOAT{ DataType::DT::DFLOAT };
constexpr DataType DT_SCOMPLEX{ DataType::DT::SCOMPLEX };
constexpr DataType DT_DCOMPLEX{ DataType::DT::DCOMPLEX };

constexpr DataType DT_LABEL = DT_UINT32; ///< Type currently used for all labeled images, see `dip::LabelType`.

/// \}

} // namespace dip

#endif // DIP_DATATYPE_H
