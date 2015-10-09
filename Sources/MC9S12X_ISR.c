/**
  ******************************************************************************
  * @Copyright (C), 1997-2015, Hangzhou Gold Electronic Equipment Co., Ltd.
  * @file name: MC9S12X_ISR.c
  * @author: Wangjian
  * @Descriptiuon: Provides a set of system interrupt service routines.
  * @Others: None
  * @History: 1. Created by Wangjian.
  * @version: V1.0.0
  * @date:    19-Sep-2015

  ******************************************************************************
  * @attention
  *
  * Licensed under GPLv2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.gnu.org/licenses/gpl-2.0.html
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
#include "MC9S12X_ISR.h"
#include "System_Driver.h"
#include "GPIO_Driver.h"





  
  
#pragma CODE_SEG __NEAR_SEG NON_BANKED


void interrupt VectorNumber_Vrti RTI_ISR(void)
{  
	if (CRGFLG_RTIF)
	{
		/* Clear the RTI interrupt flag by writing 1 to it */
		CRGFLG_RTIF = 1;
		
		/* Call time delay decrement function */
		TimeDelay_Decrement();
	}
}


/* Add your interrupt service routines here. */



#pragma CODE_SEG DEFAULT
