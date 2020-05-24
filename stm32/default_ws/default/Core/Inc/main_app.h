/*
 * main_app.h
 *
 *  Created on: Nov 17, 2019
 *      Author: David
 */

#ifndef MAIN_APP_H_
#define MAIN_APP_H_

#ifdef __cplusplus
 extern "C" {
#endif


 /* Includes ------------------------------------------------------------------*/


 /* Defines ------------------------------------------------------------------*/


 /**
  * Initialization called before HAL init
  */
 void mainAppInitPreHAL(void);

 /**
  * Initialization called after HAL init
  */
 void mainAppInit(void);

 /**
  * Called just before main loop. This will be called after
  * all other initialization.
  */
 void mainAppPreLoop(void);

 /**
  * Main app loop
  */
 void mainAppLoop(void);


#ifdef __cplusplus
}
#endif

#endif /* MAIN_APP_H_ */
