//
//  SXEffectDelegate.h
//  VEEdit
//
//  Created by Yin Xie on 2021/1/11.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#ifndef SXEffectDelegate_h
#define SXEffectDelegate_h

#import "SXGenericEffect.h"
#import "SXResource.h"
#pragma mark - SXFilterDelegate
@protocol SXFilterDelegate <NSObject>
/**
 * 添加滤镜，时间处理方式为伸缩
 * @param resource 滤镜资源
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 滤镜对象，失败返回nullptr
*/
- (SXFilterEffect *)addFilter:(SXResource *)resource index:(int)index;
/**
 * 通过复制已有的effect添加滤镜，时间处理方式为伸缩
 * @param effect 被拷贝的对象
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 滤镜对象，失败返回nullptr
*/
- (SXFilterEffect *)addFilterByCopy:(SXFilterEffect *)effect index:(int)index;;

/**
 * 移除滤镜
 * @param filterId 滤镜ID
*/
- (void)removeFilter:(NSString *)filterId;

/**
 * 获取当前对象所有应用的滤镜对象
 * @return 滤镜数组
*/
- (NSArray *)getFilters;

@end

#pragma mark - SXAnimationDelegate
@protocol SXAnimationDelegate <NSObject>
/**
 * 添加视频动画，时间处理方式为伸缩
 * @param resource 动画资源
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 视频动画对象，失败返回nullptr
*/
- (SXAnimationEffect *)addAnimation:(SXResource *)resource index:(int)index;;
/**
 * 通过复制已有的effect添加视频动画，时间处理方式为伸缩
 * @param effect 被拷贝的对象
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 视频动画对象，失败返回nullptr
*/
- (SXAnimationEffect *)addAnimationByCopy:(SXAnimationEffect *)effect index:(int)index;;

/**
 * 移除视频动画
 * @param animationId 视频动画ID
*/
- (void)removeAnimation:(NSString *)animationId;

/**
 * 获取当前对象所有应用的视频动画对象
 * @return 视频动画数组
*/
- (NSArray *)getAnimations;
@end

#pragma mark - SXVideoEffectDelegate
@protocol SXVideoEffectDelegate <NSObject>
/**
 * 添加视频特效，时间处理方式为重复
 * @param resource 视频特效资源
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 视频特效对象，失败返回nullptr
*/
- (SXVideoEffect *)addVideoEffect:(SXResource *)resource index:(int)index;;
/**
 * 通过复制已有的effect添加视频特效，时间处理方式为重复
 * @param effect 被拷贝的对象
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 视频特效对象，失败返回nullptr
*/
- (SXVideoEffect *)addVideoEffectByCopy:(SXVideoEffect *)effect index:(int)index;;

/**
 * 移除视频特效
 * @param videoEffectId 视频特效ID
*/
- (void)removeVideoEffect:(NSString *)videoEffectId;

/**
 * 获取当前对象所有应用的视频特效对象
 * @return 视频特效数组
*/
- (NSArray *)getVideoEffects;

@end

#pragma mark - SXTrackAnimationDelegate
@protocol SXTrackAnimationDelegate <NSObject>
/**
 * 添加轨道动画
 * @param resource  轨道动画资源
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 轨道动画对象t，失败返回nullptr
*/
- (SXTrackAnimationEffect *)addTrackAnimation:(SXResource *)resource index:(int)index;;

/**
 * 移除轨道动画
 * @param trackAnimationId 轨道动画ID
*/
- (void)removeTrackAnimation:(NSString *)trackAnimationId;

/**
 * 获取当前对象所有应用的轨道动画对象
 * @return 轨道动画数组
*/
- (NSArray *)getTrackAnimations;

@end

#pragma mark - SXTextAnimationDelegate
@protocol SXTextAnimationDelegate <NSObject>
/**
 * 添加文字动画
 * @param resource 文字动画资源
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 文字动画对象，失败时返回nullptr
*/
- (SXTextAnimationEffect *)addTextAnimation:(SXResource *)resource index:(int)index;

/**
 * 移除文字动画
 * @param textAnimationId 文字动画ID
*/
- (void)removeTextAnimation:(NSString *)textAnimationId;

/**
 * 获取当前对象所有应用的文字动画对象
 * @return 文字动画数组
*/
- (NSArray *)getTextAnimations;

@end

#pragma mark - SXGenericEffectDelegate
@protocol SXGenericEffectDelegate <NSObject>
/**
 * 添加内置特效
 * @param type 内置特效类型
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 内置特效，失败返回nullptr
 */
- (SXGenericEffect *)addGenericEffect:(SXGenericEffectType)type index:(int)index;
/**
 * 通过复制另一个内置特效来添加内置特效
 * @param genericEffect 内置特效
 * @param index 添加后的位置索引，0表示添加到首位，小于0或者大于总数均添加到末尾
 * @return 内置特效对象，失败返回nullptr
 */
- (SXGenericEffect *)addGenericEffectByCopy:(SXGenericEffect *)genericEffect index:(int)index;
/**
 * 删除内置特效
 * @param genericEffectId 内置特效id
 */
- (void)removeGenericEffect:(NSString *)genericEffectId;
/**
 * 获取所有内置特效
 * @return 内置特效数组
 */
- (NSArray *)getGenericEffects;

/**
 * 获取某种类型的内置特效
 * @return 内置特效数组
 */
- (NSArray *)getGenericEffectsForType:(SXGenericEffectType)type;

@end

#endif /* SXEffectDelegate_h */
