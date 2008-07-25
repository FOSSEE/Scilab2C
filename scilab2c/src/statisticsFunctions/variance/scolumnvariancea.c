/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008-2008 - INRIA - Allan SIMON
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */


#include "variance.h"


void scolumnvariancea(float *in, int lines, int columns, float* out){
    int i = 0 ;
    
    
    float* mean = (float*) malloc( sizeof (float) * (unsigned int) columns );

    
    for ( i = 0; i < lines ; i++)
    out[i] = svariancea ( in + i*columns , columns ) ;
    
    free ( mean );
}

