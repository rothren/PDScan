//==============================================================================
//
// Title:		PDScan
// Purpose:		A short description of the application.
//
// Created on:	19.02.2014 at 13:51:26 by Corporate IT.
// Copyright:	Fr. Sauter AG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "PDScan.h"
#include "toolbox.h"
#include "inifile.h" 

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
char searchPath[512] = "C:\\ProzessDaten\\4-20mAP6200Zub\\*.ini";
char pathName[512] =    "C:\\ProzessDaten\\4-20mAP6200Zub\\"; 
char SECTION[128] = "Ergebnis";
char KEY[128]	=	"Testresultat";
char VALUE[128] =	"GES";


//==============================================================================
// Global functions

int CVICALLBACK scan(void* functionData);

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "PDScan.uir", PANEL));
		
	IniText iniConf;
	iniConf = Ini_New(TRUE);
	Ini_ReadFromFile(iniConf,"config.ini");
	
	Ini_GetStringIntoBuffer(iniConf,"MAIN","search",searchPath,512); 
	Ini_GetStringIntoBuffer(iniConf,"MAIN","path",pathName,512); 
	Ini_GetStringIntoBuffer(iniConf,"MAIN","section",SECTION,128); 
	Ini_GetStringIntoBuffer(iniConf,"MAIN","key",KEY,128); 
	Ini_GetStringIntoBuffer(iniConf,"MAIN","triggerValue",VALUE,128); 
	
	
	Ini_Dispose(iniConf);
							  
	
	
	
	/* display the panel and run the user interface */
	errChk (DisplayPanel (panelHandle));
	errChk (RunUserInterface ());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}


int CVICALLBACK scan(void* functionData)
{
	int res=-1;
	char fileName[MAX_FILENAME_LEN]="";
	char path[MAX_PATHNAME_LEN] = "";
	char date[15]="";
	char time[15]="";
	
	DeleteTableRows(panelHandle,PANEL_TABLE,1,-1);
	
	
	
	res =  GetFirstFile(searchPath,1,1,0,0,0,0,fileName);
	while(res == 0)
	{
		 IniText iniFile;
		 char _value[255];
		 int nrows = 0;
		 iniFile = Ini_New(TRUE);
		 MakePathname(pathName,fileName,path);
		 Ini_ReadFromFile(iniFile,path);
		 if((Ini_SectionExists(iniFile,SECTION)) && (Ini_ItemExists(iniFile,SECTION,KEY)))
		 {
		 
			 Ini_GetStringIntoBuffer(iniFile,SECTION,KEY,_value,255);
			 if (strncmp(_value,VALUE,3) == 0)
			 {
				 //fail!!!
				 Ini_GetStringIntoBuffer(iniFile,"Pruefung","Datum",date,15);
				 Ini_GetStringIntoBuffer(iniFile,"Pruefung","Zeit",time,15);
				 InsertTableRows(panelHandle,PANEL_TABLE,-1,1,VAL_CELL_STRING);
				 GetNumTableRows(panelHandle,PANEL_TABLE,&nrows);
				 SetTableCellVal(panelHandle,PANEL_TABLE,MakePoint(1,nrows),fileName);
				 SetTableCellVal(panelHandle,PANEL_TABLE,MakePoint(2,nrows),date);
				 SetTableCellVal(panelHandle,PANEL_TABLE,MakePoint(3,nrows),time);
				 
				 
			 
			 
			 }else{
				//no fail

			 
			 }
		 }
		  Ini_Dispose(iniFile);

		res = GetNextFile(fileName);
	}
	
	
	
	SetCtrlAttribute(panelHandle,PANEL_COMMANDBUTTON,ATTR_LABEL_TEXT,"refresh list");
	SetCtrlAttribute(panelHandle,PANEL_COMMANDBUTTON,ATTR_DIMMED,0);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}

int CVICALLBACK cbTEXTBOX (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK cbTABLE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_TABLE_ROW_COL_LABEL_CLICK:
			if(eventData1 == 0)
			{break;}
			char iniToOpen[512]="";
			char path[512]="";
			GetTableCellVal(panelHandle,PANEL_TABLE,MakePoint(1,eventData1),iniToOpen);
			MakePathname(pathName,iniToOpen,path);

			 /**/
				  FILE * pFile;
				  long lSize;
				  char * buffer;
				  size_t result;

				  pFile = fopen ( path , "rb" );
				  if (pFile==NULL) { break;}

				  // obtain file size:
				  fseek (pFile , 0 , SEEK_END);
				  lSize = (ftell (pFile)+1);
				  rewind (pFile);

				  // allocate memory to contain the whole file:
				  buffer = (char*) malloc (sizeof(char)*lSize);
				  if (buffer == NULL) {break;}

				  // copy the file into the buffer:
				  result = fread (buffer,1,(lSize-1),pFile);
				  
				  buffer[lSize-1]='\0';
				  if (result != (lSize-1)) {break;}

				  /* the whole file is now loaded in the memory buffer. */

				  // terminate
				  
				 
				  
				  
				 /**/
			ResetTextBox(panelHandle,PANEL_TEXTBOX,buffer);
			fclose (pFile); 
			 free (buffer);

			
			
			break;
	}
	return 0;
}

int CVICALLBACK cbRefresh (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panelHandle,PANEL_COMMANDBUTTON,ATTR_LABEL_TEXT,"refreshing list...");
			SetCtrlAttribute(panelHandle,PANEL_COMMANDBUTTON,ATTR_DIMMED,1);
			CmtThreadFunctionID functionID;
			CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,scan,(void*)NULL,&functionID);
			break;
	}
	return 0;
}
