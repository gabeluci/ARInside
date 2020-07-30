
/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

/**********************************************************************
*
*	Header %name:	wfd_shared.h %
*	Instance:		wildlife_1
*	Description:	
*	%created_by:	sdillon %
*	%date_created:	Wed May 28 16:18:07 2008 %
*
**********************************************************************/

/* Bit masks for the various places to stop  */
/* and macros to test for them               */
#define WFD_STOP_START_API    0x00000001
#define WfdStopAtStartAPI(mode)     (mode & WFD_STOP_START_API)
#define WFD_STOP_END_API      0x00000002
#define WfdStopAtEndAPI(mode)       (mode & WFD_STOP_END_API)
#define WFD_STOP_QUALIFIER    0x00000004
#define WfdStopAtQualifier(mode)    (mode & WFD_STOP_QUALIFIER)
#define WFD_STOP_P1_ACTION    0x00000008
#define WfdStopAtP1Action(mode)     (mode & WFD_STOP_P1_ACTION)
#define WFD_STOP_P2_ACTION    0x00000010
#define WfdStopAtP2Action(mode)     (mode & WFD_STOP_P2_ACTION)
#define WFD_STOP_P3_ACTION    0x00000020
#define WfdStopAtP3Action(mode)     (mode & WFD_STOP_P3_ACTION)
#define WfdStopAtAnyAction(mode)    (mode & (WFD_STOP_P1_ACTION | WFD_STOP_P2_ACTION | WFD_STOP_P3_ACTION) )
#define WFD_STOP_ESC_ACTION   0x00000040
#define WfdStopAtEscAction(mode)    (mode & WFD_STOP_ESC_ACTION)
#define WFD_STOP_CMDB         0x00000080
#define WfdStopAtCMDB(mode)         (mode & WFD_STOP_CMDB)
#define WFD_STOP_UNUSED_1     0x00000100
#define WfdStopAtUnused1(mode)      (mode & WFD_STOP_UNUSED_1)
#define WFD_STOP_UNUSED_2     0x00000200
#define WfdStopAtUnused2(mode)      (mode & WFD_STOP_UNUSED_2)
#define WFD_STOP_UNUSED_3     0x00000400
#define WfdStopAtUnused3(mode)      (mode & WFD_STOP_UNUSED_3)


#define WFD_DEBUG_STR  "Debug"

