/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008 - INRIA - Arnaud TORSET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef __CONV2D_H__
#define __CONV2D_H__

#include "floatComplex.h"
#include "doubleComplex.h"

void sconv2da(float *in1, int lines1, int columns1, float *in2, int lines2, int columns2, float *out);

void dconv2da(double *in1, int lines1, int columns1, double *in2, int lines2, int columns2, double *out);

void cconv2da(floatComplex *in1, int lines1, int columns1, floatComplex *in2, int lines2, int columns2, floatComplex *out);

void zconv2da(doubleComplex *in1, int lines1, int columns1, doubleComplex *in2, int lines2, int columns2, doubleComplex *out);

#endif /* !__CONV2D_H__ */
