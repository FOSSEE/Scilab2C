/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008-2008 - INRIA - Arnaud TORSET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */


#include "multiplication.h"

i8 i8mulv(i8* in1, i8* in2, i16 size)
{
  i8 out = 0;
  u16 i = 0;
  
  for (i = 0 ; i < size ; ++i)
    {
      out += i8muls(in1[i], in2[i]);
    }

  return out;
}
