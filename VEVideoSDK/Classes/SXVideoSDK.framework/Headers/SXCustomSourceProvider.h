//
//  SXCustomSourceProvider.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2021/10/13.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGLES/gltypes.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SXCustomSourceProviderDelegate <NSObject>
/**
 * 按时间读取数据
 * @param texture 纹理数据
 * @param time 时间
 * @param flip 纹理是否需要翻转
 * @return 是否有纹理数据
 */
- (BOOL)updateTexture:(GLuint *)texture time:(double)time flip:(BOOL *)flip;

@end

@interface SXCustomSourceProvider : NSObject

@property(nonatomic, weak) id<SXCustomSourceProviderDelegate> delegate;

/**
 * 初始化
 * @param width 素材宽度
 * @param height 素材高度
 * @param frameRate 素材帧速率
 * @param duration 素材时长
 * @return 是否有纹理数据
 */
- (instancetype)initWithWidth:(int)width height:(int)height frameRate:(double)frameRate duration:(double)duration;

@end

NS_ASSUME_NONNULL_END
