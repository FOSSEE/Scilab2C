/* Copyright (C) 2017 - IIT Bombay - FOSSEE

 This file must be used under the terms of the CeCILL.
 This source file is licensed as described in the file COPYING, which
 you should have received as part of this distribution.  The terms
 are also available at
 http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 Author: Ankit Raj
 Organization: FOSSEE, IIT Bombay
 Email: toolbox@scilab.in
 */

#include<stdio.h>
#include "modsn.h"
#include "ell1mag.h"
#include "doubleComplex.h"
#include "multiplication.h"
#include "addition.h"
#include "division.h"

void zell1maga(double eps,double m1,doubleComplex* z,int size,double* oup )
{
	doubleComplex s[size];
	int i;
	for(i=0;i<size;i++)
	{
	s[i]=zmodsns(z[i],m1);
	}
	double un[size];
	int j;
	for(j=0;j<size;j++)
	{
	un[j]=1;
	}
	doubleComplex v;
	int k;
	double ml;
	ml=eps*eps;
	doubleComplex tp1,tp2,tp3;
	for(k=0;k<size;k++)
	{
	tp1=zmuls(s[k],s[k]);
	tp2=DoubleComplex(ml,0);
	tp3=DoubleComplex(un[k],0);
	v=zrdivs(tp3,zadds(tp3,(zmuls(tp2,tp1))));
	oup[k]=zreals(v);
	}
}
	
