//
//  SXAudioTrack.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2019/11/23.
//  Copyright © 2019 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
* 音频信息结构
* 所有字段时间为秒
* */

@interface SXAudioItem : NSObject

//音频文件路径
@property (nonatomic, copy) NSString *filePath;
//在视频中相对视频起始时间的音频插入点（默认值0，从视频起点开始）
@property (nonatomic, assign) float inPoint;
//在视频中的持续时长（默认值0，到视频终点为止）
@property (nonatomic, assign) float duration;
//当前音频截取的开始时间（默认值0，从音频起点开始）
@property (nonatomic, assign) float startTime;
//当前音频截取的截止时间（默认值0，到音频终点为止）
@property (nonatomic, assign) float endTime;
//若音频长度不够是否在插入范围内循环（默认值NO，不循环）
@property (nonatomic, assign) BOOL  isLoop;
//音频音量（0-1，默认值1，音量最大）
@property (nonatomic, assign) float volume;

- (instancetype)initWithPath:(NSString *)filePath;

- (BOOL)isVaild;

@end

NS_ASSUME_NONNULL_END
