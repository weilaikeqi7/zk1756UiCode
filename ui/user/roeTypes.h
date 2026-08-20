#ifndef __ROE_TYPES_H__
#define __ROE_TYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */
#include <unistd.h>
typedef 		unsigned char      	ROE_U8 ;
typedef 		unsigned short     	ROE_U16;
typedef		    unsigned int       	ROE_U32;
typedef 		signed char        	ROE_S8;
typedef 		short             	ROE_S16;
typedef 		int               	ROE_S32;
typedef 		unsigned long      	ROE_UL;
typedef 		signed long        	ROE_SL;
typedef 		float              	ROE_FLOAT;
typedef 		double             	ROE_DOUBLE;
typedef 		unsigned long long 	ROE_U64;
typedef 		long long          	ROE_S64;
typedef 		char               	ROE_CH8;
typedef 		char               	ROE_CHAR;
//typedef 		wchar_t            	ROE_CH32;
typedef 		size_t             	ROE_SIZE;

#define ROE_VOID void

/*----------------------------------------------*
 * const defination *
 *----------------------------------------------*/
#ifndef NULL
#define NULL 0L
#endif

#define ROE_NULL    0L
#define ROE_SUCCESS 0
#define ROE_FAILURE (-1)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __ROE_TYPES_H__*/
