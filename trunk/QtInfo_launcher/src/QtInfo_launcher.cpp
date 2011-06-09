/*
 ============================================================================
 Name		: QtInfo_launcher.cpp
 Author	  : Lucian Tomuta
 Copyright   : 2011 Forum Nokia
 Description : Exe source file
 ============================================================================
 */

//  Include Files  

#include "QtInfo_launcher.h"
#include <e32base.h>
#include <e32std.h>

#include <apgcli.h> // for RApaLsSession
#include <apacmdln.h> // for CApaCommandLine
#include <aknglobalnote.h>

//  Constants
const TUid KQtInfoAppUid = {0xA00002D6};
_LIT(KMessage, "Failed to start QtInfo(%d).\nDo you have Qt installed?");

//  Local Functions


void ShowNoteL(const TDesC& aMessage)
{
	CAknGlobalNote* note = CAknGlobalNote::NewL();
	TInt noteId = note->ShowNoteL(EAknGlobalInformationNote ,aMessage);
	User::After(3000000);
	note->CancelNoteL(noteId);
}

void LaunchAppL(const TUid aAppUid)
{
	RApaLsSession apaLsSession;
	User::LeaveIfError(apaLsSession.Connect());
	CleanupClosePushL(apaLsSession);
	TApaAppInfo appInfo;
	
	User::LeaveIfError(apaLsSession.GetAppInfo(appInfo, aAppUid));
	
	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
	cmdLine->SetExecutableNameL(appInfo.iFullName);
	cmdLine->SetCommandL(EApaCommandRun);
	
	User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );
	
	CleanupStack::PopAndDestroy(cmdLine);        
	CleanupStack::PopAndDestroy(&apaLsSession);    
}


LOCAL_C void MainL()
	{
	//
	// add your program code here, example code below
	//
	TRAPD(error, LaunchAppL(KQtInfoAppUid));
	if(error != KErrNone)
		{
			TBuf <100> message;
			message.Format(KMessage, error);
			ShowNoteL(message);
		}
	}

LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
//	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
//	CleanupStack::PushL(scheduler);
//	CActiveScheduler::Install(scheduler);

	TRAPD(ignore, MainL());
	
	// Delete active scheduler
//	CleanupStack::PopAndDestroy(scheduler);
	}

//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();

	// Run application code inside TRAP harness
	TRAPD(mainError, DoStartL());
	
	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}

