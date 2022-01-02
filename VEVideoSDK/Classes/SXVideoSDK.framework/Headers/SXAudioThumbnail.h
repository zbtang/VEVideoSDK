//
//  SXAudioThumbnail.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/5/11.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SXAudioThumbDelegate <NSObject>

/// 解析进度回调
/// @param progress 解析完成的比例[0-1]
- (void)analysisProgress:(double)progress;

@end

@interface SXAudioThumbnailCache : NSObject

/// 初始化缓存个数，同时间所需绘制的音频个数最大值
/// 若超过缓存个数，会移除部分音频轨道，造成这部分音频轨道读取失败
/// 按照路径缓存，同一路径算一个音频数据
/// @param maxNumThumbsToCache 缓存个数
- (instancetype)initWithCacheNumber:(int)maxNumThumbsToCache;

/// 情况所有音频缓存
- (void)clear;

/// 移除音频缓存，以路径为主，若还有别的音频使用该路径则不应该删除
/// @param thumbPath 移除的音频路径
- (void)removeThumbnail:(NSString *)thumbPath;
@end

@interface SXAudioThumbnail : NSObject
/// 解析代理
@property (nonatomic, assign) id<SXAudioThumbDelegate> delegate;

/// 音频路径
@property (nonatomic, copy, readonly) NSString *path;

/// 初始化一个音频对应的解析图像对象
/// @param path 音频路径
/// @param cache 解析缓存对象
/// @param singleSamples 一个图像包含的采样数
- (instancetype)initWithPath:(NSString *)path cache:(SXAudioThumbnailCache *)cache singleSamples:(int)singleSamples;

/// 获取指定时间里的图像数组
/// 数组的长度和音频的channel数相同，每个元素对应一个channel的数据
/// 一个channel的数据长度与这个时间段中包含的图像数相等
/// 每个图像数中包含一个最大值和最小值
/// 数组的结构 example:@[@[@[min,max], @[min,max]], @[@[min,max], @[min,max]]]
/// @param startTime 起始时间
/// @param duration 时长
/// @return 图像数组
- (NSArray *)getThumbDataStartTime:(NSTimeInterval)startTime duration:(NSTimeInterval)duration;

/// 当前对象解析进度
/// @return 进度[0-1]
- (double)progress;

@end

NS_ASSUME_NONNULL_END
