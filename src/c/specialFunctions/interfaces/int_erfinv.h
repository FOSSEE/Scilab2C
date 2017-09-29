/* Copyright (C) 2017 - IIT Bombay - FOSSEE

 This file must be used under the terms of the CeCILL.
 This source file is licensed as described in the file COPYING, which
 you should have received as part of this distribution.  The terms
 are also available at
 http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 Author: Brijesh Gupta C R
 Organization: FOSSEE, IIT Bombay
 Email: toolbox@scilab.in
 */
#ifndef __INT_ERFINV_H__
#define __INT_ERFINV_H__

#ifdef  __cplusplus
extern "C" {
#endif



#define d0erfinvd0(in1) derfinvs(in1)
#define s0erfinvs0(in1) serfinvs(in1)
#define d2erfinvd2(in1,size,out) derfinva(in1,size[0],size[1],out)
#define s2erfinvs2(in1,size,out) serfinva(in1,size[0],size[1],out)

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif /*__INT_ERFINV_H__*/
