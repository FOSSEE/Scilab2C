 /* Copyright (C) 2016 - IIT Bombay - FOSSEE

 This file must be used under the terms of the CeCILL.
 This source file is licensed as described in the file COPYING, which
 you should have received as part of this distribution.  The terms
 are also available at
 http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 Author: Siddhesh Wani, Jorawar Singh
 Organization: FOSSEE, IIT Bombay
 Email: toolbox@scilab.in
 */
#ifndef __RPIPERIPHERALPINMAP_H__
#define __RPIPERIPHERALPINMAP_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include "types.h"

int8 u8RPI_physToGpios(uint8 pin);
int8 u8RPI_wpiToGpios(uint8 pin);

#ifdef  __cplusplus 
} /* extern "C" */
#endif

#endif /*__RPIPERIPHERALPINMAP_H__*/
