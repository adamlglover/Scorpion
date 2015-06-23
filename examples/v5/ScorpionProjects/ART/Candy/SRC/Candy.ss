/*
* Copyright (C) 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
* Candy.ss
* Calculate the total cost of 
* a candy bar.
*
* Author: Braxton Nunnally
* Date: 5/31/2015
*/

dload Reeses_Big_Cup 1.34
dload SalesTax 0.20
dload TotalCost 0.0

.main:
   mov i1 double
   mult TotalCost Reeses_Big_Cup,SalesTax
   add TotalCost TotalCost,Reeses_Big_Cup
   printf 'The total cost is <v,TotalCost>'
   ret

call main 
   
halt
   