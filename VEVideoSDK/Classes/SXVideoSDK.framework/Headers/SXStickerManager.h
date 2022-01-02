//
//  SXStickerManager.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/5/18.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface SXStickerManager : NSObject

/// 增加一个贴纸
/// @param stickerPath 贴纸文件夹的路径
/// @return 贴纸ID
- (NSString *)addSticker:(NSString *)stickerPath;

/// 获取某个坐标上的贴纸
/// @param point 坐标点
/// @return 贴纸ID
- (NSString *)getStickerAtPoint:(CGPoint)point;

/// 获取贴纸原始尺寸
/// @param stickerId 贴纸ID
/// @return 贴纸原始尺寸
- (CGSize)getStickerOriginalSize:(NSString *)stickerId;

/// 获取贴纸的边框
/// @param stickerId 贴纸ID
/// @return 贴纸在context中的frame
- (CGRect)getBoundingBox:(NSString *)stickerId;

/// 暂停指定的贴纸
/// @param stickerId 贴纸ID
- (void)pauseSticker:(NSString *)stickerId;

/// 续播指定的贴纸
/// @param stickerId 贴纸ID
- (void)resumeSticker:(NSString *)stickerId;

/// 获取贴纸是否处于暂停状态
/// @param stickerId 贴纸ID
/// @return 暂停中返回true
- (bool)getStickerPaused:(NSString *)stickerId;

/// 移除贴纸
/// @param stickerId 贴纸ID
- (void)removeSticker:(NSString *)stickerId;

/// 替换贴纸中的素材
/// @note 可能会引起素材位置信息变化，需要设置旋转位移缩放的素材使用此方法
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @param sourcePath 替换使用的素材路径
- (BOOL)replaceSource:(NSString *)stickerId sourceIndex:(int)sourceIndex withSource:(NSString *)sourcePath;

/// 替换贴纸中的素材
/// @note 可能会引起素材位置信息变化，需要设置旋转位移缩放的素材使用此方法
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @param sourcePath 替换使用的素材路径
/// @param isAdapt 是否按素材时长适配
- (BOOL)replaceSource:(NSString *)stickerId sourceIndex:(int)sourceIndex withSource:(NSString *)sourcePath isAdapt:(BOOL)isAdapt;

/// 替换贴纸中的素材,SDK不对素材进行裁剪
/// @note 不会重置素材原本的位置信息，文本素材替换建议只用此方法，后续不建议修改素材的位置信息
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @param sourcePath 替换使用的素材路径
- (BOOL)replaceSourceWithNoCrop:(NSString *)stickerId sourceIndex:(int)sourceIndex withSource:(NSString *)sourcePath;

/// 设置素材的旋转
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @param rotation 旋转角度
- (void)setSourceRotate:(NSString *)stickerId sourceIndex:(int)sourceIndex rotation:(float)rotation;

/// 设置素材的缩放
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @param scaleX  宽度缩放比例
/// @param scaleY 高度缩放比例
- (void)setSourceScale:(NSString *)stickerId sourceIndex:(int)sourceIndex scaleX:(float)scaleX scaleY:(float)scaleY;

/// 设置素材的位置
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @param position 位置坐标
- (void)setSourcePosition:(NSString *)stickerId sourceIndex:(int)sourceIndex position:(CGPoint)position;

/// 设置贴纸的旋转
/// @param stickerId 贴纸ID
/// @param rotation 旋转角度
- (void)setStickerRotate:(NSString *)stickerId rotation:(float)rotation;

/// 设置贴纸的缩放
/// @param stickerId 贴纸ID
/// @param scaleX  X方向缩放比例
/// @param scaleY Y方向缩放比例
- (void)setStickerScale:(NSString *)stickerId scaleX:(float)scaleX scaleY:(float)scaleY;

/// 设置贴纸的位置
/// @param stickerId 贴纸ID
/// @param position 位置坐标
- (void)setStickerPosition:(NSString *)stickerId position:(CGPoint)position;

/// 设置贴纸的锚点
/// @param stickerId 贴纸ID
/// @param anchor 锚点坐标
- (void)setStickerAnchor:(NSString *)stickerId anchor:(CGPoint)anchor;

/// 获取素材旋转信息
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @return 素材旋转信息
- (float)getSourceRotation:(NSString *)stickerId sourceIndex:(int)sourceIndex;

/// 获取素材缩放信息
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @return 素材缩放信息 宽高缩放
- (CGPoint)getSourceScale:(NSString *)stickerId sourceIndex:(int)sourceIndex;

/// 获取素材位置信息
/// @param stickerId 贴纸ID
/// @param sourceIndex 素材索引
/// @return 素材位置坐标
- (CGPoint)getSourcePositon:(NSString *)stickerId sourceIndex:(int)sourceIndex;

/// 获取贴纸旋转信息
/// @param stickerId 贴纸ID
/// @return 贴纸旋转信息
- (float)getStickerRotation:(NSString *)stickerId;

/// 获取贴纸缩放信息
/// @param stickerId 贴纸ID
/// @return 贴纸缩放信息 宽高缩放
- (CGPoint)getStickerScale:(NSString *)stickerId;

/// 获取贴纸位置信息
/// @param stickerId 贴纸ID
/// @return 贴纸位置坐标
- (CGPoint)getStickerPositon:(NSString *)stickerId;

/// 获取贴纸锚点信息
/// @param stickerId 贴纸ID
/// @return 贴纸锚点坐标
- (CGPoint)getStickerAnchor:(NSString *)stickerId;
@end

NS_ASSUME_NONNULL_END
