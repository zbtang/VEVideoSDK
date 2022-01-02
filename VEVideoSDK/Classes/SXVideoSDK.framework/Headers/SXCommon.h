//
//  SXCommon.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2019/8/8.
//  Copyright © 2019 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Log.h"

NS_ASSUME_NONNULL_BEGIN

@interface SXCommon : NSObject

+ (void)setLogLevel:(int)level;

+ (void)printLog:(NSString *)content level:(int)level;

+ (NSString *)getTempPath;
@end

NS_ASSUME_NONNULL_END
