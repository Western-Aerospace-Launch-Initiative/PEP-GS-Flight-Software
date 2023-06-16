

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>
#include <stdbool.h>

typedef _Bool Boolean;

#define FALSE ((Boolean)0U)
#define TRUE  ((Boolean)1U)

typedef uint8_t U8;
typedef int8_t S8;
typedef uint16_t U16;
typedef int16_t S16;
typedef uint32_t U32;
typedef int32_t S32;
typedef uint64_t U64;
typedef int64_t S64;
typedef float F32;
typedef double F64;
typedef char Text;

/// Sensor/actuator interface function result enumeration
typedef enum
{
	CubeLibOk             = 0,
	PointerIsNull         = 1,
	TcInvalidParam        = 2,
	TlmRangeError         = 3,
	TcAckTimeout          = 4
} CUBEADCS_Result_t;

#endif /* _TYPES_H_ */
