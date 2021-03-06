/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : Bookmark Manager
 #	author : miyako
 #	2016/05/02
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- Bookmarks

		case 1 :
			BOOKMARK_Create(pResult, pParams);
			break;

		case 2 :
			BOOKMARK_Resolve(pResult, pParams);
			break;

		case 3 :
			BOOKMARK_Export_to_file(pResult, pParams);
			break;

	}
}

// ----------------------------------- Bookmarks ----------------------------------

void BOOKMARK_Export_to_file(sLONG_PTR *pResult, PackagePtr pParams)
{
#if VERSIONMAC
	C_BLOB Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	// --- write the code of BOOKMARK_EXPORT_TO_FILE here...
	
	NSData *bookmark = [[NSData alloc]initWithBytes:Param1.getBytesPtr() length:Param1.getBytesLength()];
	
	NSURL *url = Param2.copyUrl();
	
	if(url)
	{
		NSError *error = nil;
		
		[NSURL
		 writeBookmarkData:bookmark
		 toURL:url
		 options:NSURLBookmarkCreationSuitableForBookmarkFile
		 error:&error];
		
		[url release];
		
		if(error)	returnValue.setIntValue([error code]);
	}else{
		returnValue.setIntValue(NSFileNoSuchFileError);//
	}
	
	returnValue.setReturn(pResult);
	[bookmark release];
#endif
}

void BOOKMARK_Create(sLONG_PTR *pResult, PackagePtr pParams)
{
#if VERSIONMAC
	C_TEXT Param1;
	C_BLOB returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	// --- write the code of BOOKMARK_Create here...
	
	NSURL *url = Param1.copyUrl();
	
	if(url)
	{
		NSArray *keys = [NSArray arrayWithObjects:
										 NSURLNameKey,
										 NSURLLocalizedNameKey,
										 NSURLIsRegularFileKey,
										 NSURLIsDirectoryKey,
										 NSURLIsSymbolicLinkKey,
										 NSURLIsVolumeKey,
										 NSURLIsPackageKey,
										 NSURLIsSystemImmutableKey,
										 NSURLIsUserImmutableKey,
										 NSURLIsHiddenKey,
										 NSURLHasHiddenExtensionKey,
										 NSURLCreationDateKey,
										 NSURLContentAccessDateKey,
										 NSURLContentModificationDateKey,
										 NSURLAttributeModificationDateKey,
										 NSURLLinkCountKey,
										 NSURLParentDirectoryURLKey,
										 NSURLVolumeURLKey,
										 NSURLTypeIdentifierKey,
										 NSURLLocalizedTypeDescriptionKey,
										 NSURLEffectiveIconKey,
										 NSURLFileSizeKey,
										 NSURLFileAllocatedSizeKey,
										 /*
											NSURLLabelNumberKey,
											NSURLLabelColorKey,
											NSURLLocalizedLabelKey,
											NSURLCustomIconKey,
											NSURLVolumeLocalizedFormatDescriptionKey,
											NSURLVolumeTotalCapacityKey,
											NSURLVolumeAvailableCapacityKey,
											NSURLVolumeResourceCountKey,
											NSURLVolumeSupportsPersistentIDsKey,
											NSURLVolumeSupportsSymbolicLinksKey,
											NSURLVolumeSupportsHardLinksKey,
											NSURLVolumeSupportsJournalingKey,
											NSURLVolumeIsJournalingKey,
											NSURLVolumeSupportsSparseFilesKey,
											NSURLVolumeSupportsZeroRunsKey,
											NSURLVolumeSupportsCaseSensitiveNamesKey,
											NSURLVolumeSupportsCasePreservedNamesKey,
											*/
										 nil];
		
		NSData *bookmark = [url
												bookmarkDataWithOptions:NSURLBookmarkCreationSuitableForBookmarkFile
												includingResourceValuesForKeys:keys
												relativeToURL:NULL
												error:NULL];
		
		if(bookmark)
		{
			returnValue.setBytes((const uint8_t *)[bookmark bytes], [bookmark length]);
			returnValue.setReturn(pResult);
		}
		
		[url release];
	}
#endif
}

void BOOKMARK_Resolve(sLONG_PTR *pResult, PackagePtr pParams)
{
#if VERSIONMAC
	C_BLOB Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	// --- write the code of BOOKMARK_Resolve here...
	
	NSData *bookmark = [[NSData alloc]initWithBytes:Param1.getBytesPtr() length:Param1.getBytesLength()];
	
	BOOL isStale = YES;
	
	NSURL *url = [[NSURL alloc]
								initByResolvingBookmarkData:bookmark
								options:NSURLBookmarkResolutionWithoutUI
								relativeToURL:NULL
								bookmarkDataIsStale:&isStale
								error:NULL];
	
	if(url)
	{
		NSString *path = (NSString *)CFURLCopyFileSystemPath((CFURLRef)url, kCFURLHFSPathStyle);
		returnValue.setUTF16String(path);
		returnValue.setReturn(pResult);
		[path release];		
		[url release];	
	}
	
	[bookmark release];
#endif
}

