//
//  SXReverseVideo.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/12/14.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SXReverseVideo : NSObject

@property(nonatomic, copy) NSError *error;

- (instancetype)initWithInput:(NSString *)inputPath output:(NSString *)output;

- (void)exportAsynchronouslyWithCompletionHandler:(void (^)(void))handler progress:(void (^)(float))progress;

@end

NS_ASSUME_NONNULL_END
