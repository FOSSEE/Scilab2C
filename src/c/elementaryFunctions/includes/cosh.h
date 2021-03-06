/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2006-2008 - INRIA - Bruno JOFRET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef __COSH_H__
#define __COSH_H__

#include "dynlib_elementaryfunctions.h"
#include "floatComplex.h"
#include "doubleComplex.h"
#include "types.h"


#ifdef  __cplusplus
extern "C" {
#endif
/*
** Compute Cosine for different types .
*/

/*
** \brief Float Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT float		scoshs(float in);

/*
** \brief Double Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT double		dcoshs(double in);

/*
** \brief Float Complex Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT floatComplex	ccoshs(floatComplex in);

/*
** \brief Double Complex Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT doubleComplex	zcoshs(doubleComplex in);

/*
** \brief uint8 Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT float		u8coshs(uint8 in);

/*
** \brief int8 Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT float		i8coshs(int8 in);

/*
** \brief uint16 Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT float		u16coshs(uint16 in);

/*
** \brief int16 Cosine function
** \param in : input value.
*/
EXTERN_ELEMFUNCT float		i16coshs(int16 in);

/*
** \brief Float Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		scosha(float* in, int size, float* out);

/*
** \brief Double Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		dcosha(double* in, int size, double* out);

/*
** \brief Float Complex Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		ccosha(floatComplex* in, int size, floatComplex* out);

/*
** \brief Double Complex Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		zcosha(doubleComplex* in, int size, doubleComplex* out);

/*
** \brief Uint8 Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		u8cosha(uint8* in, int size, uint8* out);

/*
** \brief Int8 Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		i8cosha(int8* in, int size, int8* out);

/*
** \brief Uint16 Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		u16cosha(uint16* in, int size, uint16* out);

/*
** \brief Int16 Matrix Cosine function
** \param in : input array value.
** \param out : output array value.
** \param size : the size of in and out arrays.
*/
EXTERN_ELEMFUNCT void		i16cosha(int16* in, int size, int16* out);


#ifdef  __cplusplus
} /* extern "C" */
#endif


#endif /* !__COSH_H__ */

