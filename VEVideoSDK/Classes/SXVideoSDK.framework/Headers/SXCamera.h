      //
//  SXCamera.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2019/4/15.
//  Copyright © 2019 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    SXCameraSize480,
    SXCameraSize720,
    SXCameraSize1080,
} SXCameraSize;

typedef enum : NSUInteger {
    SXCameraFrameRate15,
    SXCameraFrameRate20,
    SXCameraFrameRate25,
    SXCameraFrameRate30
} SXCameraFrameRate;

typedef enum : NSUInteger {
    SXCameraPositionFront,
    SXCameraPositionBack,
} SXCameraPosition;

typedef enum : NSUInteger {
    SXCameraSourceTypeVideoOnly,
    SXCameraSourceTypeAudioAndVideo,
} SXCameraSourceType;

@interface SXCamera : NSObject

@property (nonatomic, assign, readonly) SXCameraSize size;
@property (nonatomic, assign, readonly) SXCameraFrameRate frameRate;
@property (nonatomic, assign, readonly) SXCameraSourceType type;
@property (nonatomic, assign)           SXCameraPosition position;


/// 初始化相机对象
/// @param size 相机尺寸
/// @param frameRate 相机帧速率
/// @param position 前置或者后置
/// @param type 相机类型
- (instancetype)initWithSize:(SXCameraSize)size
                   frameRate:(SXCameraFrameRate)frameRate
                    position:(SXCameraPosition)position
                        type:(SXCameraSourceType)type;


/// 启动相机
- (void)start;

/// 停止相机
- (void)stop;

/// 设置相机焦点
/// @param point 焦点
- (void)focusAt:(CGPoint)point;

/// 是否启用闪光灯
/// @param enable YES启用 NO不启用
- (void)enableTorch:(BOOL)enable;

/// 镜像相机画面
- (void)videoMirrored:(BOOL)isMirrored;

- (void)setMattingEnabled:(BOOL)enabled;

- (BOOL)isMattingEnabled;

@end

NS_ASSUME_NONNULL_END
