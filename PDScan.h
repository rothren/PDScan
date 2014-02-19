/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2014. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_TABLE                      2       /* control type: table, callback function: cbTABLE */
#define  PANEL_COMMANDBUTTON              3       /* control type: command, callback function: cbRefresh */
#define  PANEL_TEXTBOX                    4       /* control type: textBox, callback function: cbTEXTBOX */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK cbRefresh(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbTABLE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbTEXTBOX(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
