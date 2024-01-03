#ifndef STUN_DATA_TYPES_H
#define STUN_DATA_TYPES_H

/* Standard includes. */
#include <stdint.h>
#include <stddef.h>

/*
 * STUN Message Header:
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 0|     STUN Message Type     |         Message Length        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Magic Cookie                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * |                     Transaction ID (96 bits)                  |
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

/* Length and offsets of various members in the STUN header. */
#define STUN_HEADER_LENGTH                  20
#define STUN_HEADER_MESSAGE_LENGTH_OFFSET   2
#define STUN_HEADER_MAGIC_COOKIE_OFFSET     4
#define STUN_HEADER_TRANSACTION_ID_OFFSET   8
#define STUN_HEADER_TRANSACTION_ID_LENGTH   12

/* Cookie value in the header. */
#define STUN_HEADER_MAGIC_COOKIE        0x2112A442

/* Serializer macros. */
#define WRITE_UINT16( pDst, val )   ( *( ( uint16_t * )( pDst ) ) = ( val ) )
#define WRITE_UINT32( pDst, val )   ( *( ( uint32_t * )( pDst ) ) = ( val ) )

/* Deserializer macros. */
#define READ_UINT16( val, pSrc )    ( ( val ) = *( ( uint16_t * )( pSrc ) ) )
#define READ_UINT32( val, pSrc )    ( ( val ) = *( ( uint32_t * )( pSrc ) ) )

/*
 * STUN Attribute:
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |         Type                  |            Length             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Value (variable)                ....
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

/* Length and offsets of various members in a STUN attribute. */
#define STUN_ATTRIBUTE_HEADER_LENGTH            4
#define STUN_ATTRIBUTE_HEADER_LENGTH_OFFSET     2
#define STUN_ATTRIBUTE_HEADER_VALUE_OFFSET      4

/* Helper macros. */
#define ALIGN_SIZE_TO_WORD( size )                  ( ( ( size ) + 0x3 ) & ~( 0x3 ) )
#define REMAINING_LENGTH( pCtx )                    ( ( pCtx )->totalLength - ( pCtx )->currentIndex )
#define STUN_ATTRIBUTE_TOTAL_LENGTH( valueLength )  ( valueLength + STUN_ATTRIBUTE_HEADER_LENGTH )
/*-----------------------------------------------------------*/

typedef enum StunResult
{
    STUN_RESULT_OK,
    STUN_RESULT_BAD_PARAM,
    STUN_RESULT_OUT_OF_MEMORY,
    STUN_RESULT_MALFORMED_MESSAGE,
    STUN_RESULT_MAGIC_COOKIE_MISMATCH,
    STUN_RESULT_NO_MORE_ATTRIBUTE_FOUND,
    STUN_RESULT_INVALID_ATTRIBUTE_LENGTH
} StunResult_t;

typedef enum StunMessageType
{
    STUN_MESSAGE_TYPE_BINDING_REQUEST = 0x0001,
    STUN_MESSAGE_TYPE_BINDING_SUCCESS_RESPONSE = 0x0101,
    STUN_MESSAGE_TYPE_BINDING_FAILURE_RESPONSE = 0x0111,
    STUN_MESSAGE_TYPE_BINDING_INDICATION = 0x0011
} StunMessageType_t;

typedef enum StunAttributeType
{
    STUN_ATTRIBUTE_TYPE_USERNAME = 0x0006,
    STUN_ATTRIBUTE_TYPE_MESSAGE_INTEGRITY = 0x0008,
    STUN_ATTRIBUTE_TYPE_PRIORITY = 0x0024,
    STUN_ATTRIBUTE_TYPE_FINGERPRINT = 0x8028,
} StunAttributeType_t;
/*-----------------------------------------------------------*/

typedef struct StunContext
{
    const char * pStart;
    size_t totalLength;
    size_t currentIndex;
} StunContext_t;

typedef struct StunHeader
{
    StunMessageType_t messageType;
    uint16_t messageLength;
    uint8_t transactionId[ STUN_HEADER_TRANSACTION_ID_LENGTH ];
} StunHeader_t;
/*-----------------------------------------------------------*/

#endif /* STUN_DATA_TYPES_H */