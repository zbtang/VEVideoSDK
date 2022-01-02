//
//  SXEditExtension.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/3/31.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#ifndef SXEditExtension_h
#define SXEditExtension_h

#import "SXEditOptions.h"
#import "SXVEOptions.h"
#import "SXEditManager.h"
#import "SXVEEditManager.h"
#import "SXEditManagerInternal.h"
#import "SXTrack.h"
#import "SXVETrack.h"
#import "SXEffect.h"
#import "SXVEBaseEffect.h"
#import "SXTrackGroup.h"
#import "SXVETrackGroup.h"
#import "SXVEEditManager.h"
#import "SXShape.h"
#import "SXVEShape.h"
#import "SXComposite.h"
#import "SXResource.h"
#import "SXVEResource.h"

using namespace SXEdit;

@interface SXEditOptions(Get)

- (SXVEOptions)getOptions;

@end

@interface SXEditManager(Get)

- (SXVEEditManager *)getManager;

@end

@interface SXTrackGroup(Category)

- (instancetype)initWith:(SXVETrackGroup *)trackGroup;

- (SXVETrackGroup *)getGroup;

@end

@interface SXTrack(Category)

+ (instancetype)trackWith:(SXVETrack *)track;

- (instancetype)initWith:(SXVETrack *)track;

- (SXVETrack *)getTrack;

- (SXEditManagerInternal *)getManager;
@end

@interface SXEffect(Category)

- (instancetype)initWith:(SXVEBaseEffect *)effect;

- (SXEditManagerInternal *)getManager;

- (SXVETrack *)getTrack;

- (SXVEBaseEffect *)getEffect;
@end

@interface SXShape(Category)

+ (SXVESegmentPath *)convertUIPathToVEPath:(UIBezierPath *)path;

+ (UIBezierPath *)convertVEPathToUIPath:(SXVESegmentPath &)path;

- (instancetype)initWithShape:(const SXVEShape *)shape;

- (SXVEShape *)getShape;

@end

@interface SXComposite(Category)

+ (instancetype)compositeWith:(SXVEComposite *)composite;

- (instancetype)initWith:(SXVEComposite *)composite;

- (SXVEComposite *)getComposite;

@end

@interface SXResource(Category)

+ (instancetype)resourceWith:(SXVEResource *)resource;

- (instancetype)initWith:(SXVEResource *)resource;

- (SXVEResource *)getResource;

@end

#endif /* SXEditExtension_h */
