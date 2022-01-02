#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "SXAudioItem.h"
#import "SXAudioThumbnail.h"
#import "SXCamera.h"
#import "SXCameraTemplate.h"
#import "SXCommon.h"
#import "SXComposite.h"
#import "SXConfigUtils.h"
#import "SXCustomSourceProvider.h"
#import "SXEditExtension.h"
#import "SXEditManager.h"
#import "SXEditOptions.h"
#import "SXEditPublic.h"
#import "SXEffect.h"
#import "SXEffectDelegate.h"
#import "SXFilter.h"
#import "SXGenericEffect.h"
#import "SXLicense.h"
#import "SXPlayerView.h"
#import "SXResource.h"
#import "SXReverseVideo.h"
#import "SXShape.h"
#import "SXStickerManager.h"
#import "SXTemplate.h"
#import "SXTemplatePlayer.h"
#import "SXTemplateRender.h"
#import "SXTextCanvas.h"
#import "SXTrack.h"
#import "SXTrackGroup.h"
#import "SXVideoCompositor.h"
#import "SXVideoSDK.h"

FOUNDATION_EXPORT double VEVideoSDKVersionNumber;
FOUNDATION_EXPORT const unsigned char VEVideoSDKVersionString[];

