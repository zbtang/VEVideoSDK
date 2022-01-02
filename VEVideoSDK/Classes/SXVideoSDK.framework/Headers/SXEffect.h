//
//  SXEffect.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/3/31.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXEditPublic.h"
#import "SXResource.h"
NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    SXEffectTypeTransition,
    SXEffectTypeTextBubble,
    SXEffectTypeTextStyle,
    SXEffectTypeTextAnimation,
    SXEffectTypeFilter,
    SXEffectTypeAnimation,
    SXEffectTypeVideoEffect,
    SXEffectTypeTrackAnimation,
    SXEffectTypeGenericEffect
} SXEffectType;

typedef enum : NSUInteger {
    SXEffectTimeFollowStart,                // 效果时间跟随轨道start time
    SXEffectTimeFollowDisplayTime,          // 效果时间跟随轨道display time
    SXEffectTimeFollowEnd,                  // 效果时间反向跟随轨道out time(display + duration)
    SXEffectTimeFollowWholeProcess          // 效果时间与轨道显示时间保持一致
}SXEffectTimeFollowType;

typedef enum : NSUInteger {
    SXEffectTimeExtendTypeStretchAndLoop, //效果时间可以同时拉伸与循环
    SXEffectTimeExtendTypeLoop,           //效果时间以自身总时长为基础循环
    SXEffectTimeExtendTypeStretch,        //效果时间拉伸
    SXEffectTimeExtendTypeFreezeEnd       //效果时间超出自身总时长则超出部分定格为最后一帧
}SXEffectTimeExtendType;

#pragma mark - SXEffect
/**
 * 特效，被应用在轨道或组上产生效果
 * @warning 注意所有的对象对比是否相等时请使用id对比，引用可能会不同
*/
@interface SXEffect : NSObject<SXEditAttributeDelegate>
//开始时间是相对与轨道in point的时间，修改followType和followOffsetTime可能会引起startTime改变
@property (nonatomic, assign, readonly) double startTime;

//time 时长是相对与startTime的时长，修改followType和followOffsetTime可能会引起duration改变
@property (nonatomic, assign) double duration;

/**
 * 获取效果跟随轨道时间方式
 * @note 例如跟随轨道开始时间与轨道一同开始、跟随轨道的结束时间与轨道一同结束等，默认跟随方式为kFollowDisplayTime
 */
@property (nonatomic, assign) SXEffectTimeFollowType followType;

/**
 * 不同时间跟随方式followOffsetTime的参照时间是不一样的，跟随方式祥见SXEffectTimeFollowType类型说明
 * kFollowStart：效果开始时间为相对于轨道开始时间的局部时间
 * kFollowDisplayTime: 效果开始时间为相对于轨道开始显示时间的局部时间
 * kFollowEnd: 效果开始时间为相对于轨道结束时间的局部时间，并且时间方向为反向
 * kFollowWholeProcess：无效，效果于轨道显示时间一致，同时开始同时结束
 */
@property (nonatomic, assign) double followOffsetTime;

//扩展方式决定当特效时间超出特效自身的时长时如何扩展，默认扩展方式为kStretch
@property (nonatomic, assign) SXEffectTimeExtendType extendType;

//一次循环的时长，时长会转化为倍速，仅扩展方式为kStretchAndLoop时有效
@property (nonatomic, assign) double durationOfOneCycle;

//倍速,默认一倍速，仅扩展方式为kStretchAndLoop时有效
@property (nonatomic, assign) double speed;
/**
 * 效果类型
 * @return  效果类型
 */
- (SXEffectType)type;

/**
 * 效果的唯一id
 * @return uuid
 */
- (NSString *)getEffectId;

@end

#pragma mark - SXFilterEffect
@interface SXFilterEffect : SXEffect<SXResourceDelegate>
//滤镜的不透明度,区间为【0，1】
@property (nonatomic, assign) float alpha;

@end

#pragma mark - SXAnimationEffect
@interface SXAnimationEffect : SXEffect<SXResourceDelegate>

@end

#pragma mark - SXVideoEffect
@interface SXVideoEffect : SXEffect<SXResourceDelegate>

@end

#pragma mark - SXTextAnimationEffect
@interface SXTextAnimationEffect : SXEffect<SXResourceDelegate>


@end

#pragma mark - SXTrackAnimationEffect
@interface SXTrackAnimationEffect : SXEffect<SXResourceDelegate>

@end

NS_ASSUME_NONNULL_END
