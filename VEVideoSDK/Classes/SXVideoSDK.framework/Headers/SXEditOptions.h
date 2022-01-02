//
//  SXEditOptions.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/3/31.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    SXVePreviewScale100 = 100,
    SXVePreviewScale75  = 75,
    SXVePreviewScale50  = 50,
    SXVePreviewScale25  = 25
} SXVePreviewScale;

@interface SXEditOptions : NSObject

//定义渲染宽度
@property (nonatomic, assign) int width;
//定义渲染高度
@property (nonatomic, assign) int height;
//帧速率
@property (nonatomic, assign) int fps;
//所需验证的license
@property (nonatomic, strong) NSString *license;
//设置整体渲染缩放倍数
@property (nonatomic, assign) SXVePreviewScale scale;
//设置一个全局默认字体
@property (nonatomic, strong) NSString *fontFile;
//设置是否开启素材预加载, 默认不开启
@property (nonatomic, assign) BOOL enableSourceManager;
//设置是否开启音频, 默认开启
@property (nonatomic, assign) BOOL enableAudioManager;
//设置素材预加载的预留空间大小, 默认300M
@property (nonatomic, assign) long long cacheSize;

@end

NS_ASSUME_NONNULL_END
