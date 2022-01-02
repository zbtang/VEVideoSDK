//
//  SXTrack.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/3/31.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SXEditPublic.h"
#import "SXShape.h"
#import "SXEffectDelegate.h"
#import "SXResource.h"
#import "SXConfigUtils.h"
#import "SXCustomSourceProvider.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    SXTrackTypeMedia,
    SXTrackTypeSticker,
    SXTrackTypeText,
    SXTrackTypeAudio,
    SXTrackTypeTemplate
} SXTrackType;

@class SXEditManager;

#pragma mark - SXTrack

/**
 * 轨道，分为多媒体轨道，贴纸轨道和文字轨道
 * @warning 注意所有的对象对比是否相等时请使用id对比，引用可能会不同
*/
@interface SXTrack : NSObject<SXEditAttributeDelegate>
//是否启用,默认启用
@property (nonatomic, assign) BOOL enabled;
//设置轨道时长超出素材时长是否循环，默认不循环
@property (nonatomic, assign) BOOL loop;
//轨道开始显示的时间,由start和offset决定
//轨道开始时间（start） + 偏移时间（offset） = 显示时间（display）
//修改该值会通过修改offset实现，startTime保持不变
@property (nonatomic, assign) double displayTime;
//轨道的开始时间，即整体移动轨道到对应的时间
@property (nonatomic, assign) double startTime;
//轨道的自身的偏移时间
@property (nonatomic, assign) double offsetTime;
//设置轨道显示的时长
@property (nonatomic, assign) double duration;
/**
 * 获取当前track的类型
 * @return 类型
*/
- (SXTrackType)type;

/**
 * 获取当前track是否可用
 * @return YES可用 NO不可用
*/
- (BOOL)isValid;

/**
 * 判断是否在可见区间内
 * @param time 时间
 * @return ture表示在时间time上可见
 */
- (BOOL)visibleAtTime:(double)time;
/**
 * 获取当前track的ID
 * @return ID
*/
- (NSString *)getTrackId;
/**
 * 获取所在组的id
 * @return 不在组中时返回空字符串
 */
- (NSString *)groupId;

@end

#pragma mark - SXAudioTrack

@interface SXAudioTrack : SXTrack
/// 音频文件路径
@property (nonatomic, copy, readonly) NSString *filePath;
/// 音频素材原始时长
@property (nonatomic, assign, readonly) float resourceDuration;
///音量
@property (nonatomic, assign) float volume;
/// 淡入时长
@property (nonatomic, assign) float fadeInDuration;
///淡出时长
@property (nonatomic, assign) float fadeOutDuration;
///变速的系数
@property (nonatomic, assign) float speed;
///变调的系数
@property (nonatomic, assign) float pitch;
@end

#pragma mark - SXRenderTrack
typedef enum : NSUInteger {
    SXKeyFrameOptionsHold,
    SXKeyFrameOptionsLinear,
    SXKeyFrameOptionsQuadraticEaseIn,
    SXKeyFrameOptionsQuadraticEaseOut,
    SXKeyFrameOptionsQuadraticEaseInOut,
    SXKeyFrameOptionsCubicIn,
    SXKeyFrameOptionsCubicOut,
    SXKeyFrameOptionsCubicInOut,
    SXKeyFrameOptionsQuarticIn,
    SXKeyFrameOptionsQuarticOut,
    SXKeyFrameOptionsQuarticInOut,
    SXKeyFrameOptionsQuinticIn,
    SXKeyFrameOptionsQuinticOut,
    SXKeyFrameOptionsQuinticInOut,
    SXKeyFrameOptionsSineIn,
    SXKeyFrameOptionsSineOut,
    SXKeyFrameOptionsSineInOut,
    SXKeyFrameOptionsCircleIn,
    SXKeyFrameOptionsCircleOut,
    SXKeyFrameOptionsCircleInOut,
    SXKeyFrameOptionsExponentialIn,
    SXKeyFrameOptionsExponentialOut,
    SXKeyFrameOptionsExponentialInOut,
    SXKeyFrameOptionsElasticIn,
    SXKeyFrameOptionsElasticOut,
    SXKeyFrameOptionsElasticInOut,
    SXKeyFrameOptionsBackEaseIn,
    SXKeyFrameOptionsBackEaseOut,
    SXKeyFrameOptionsBackEaseInOut,
    SXKeyFrameOptionsBounceIn,
    SXKeyFrameOptionsBounceOut,
    SXKeyFrameOptionsBounceInOut,
    SXKeyFrameOptionsPath
}SXKeyFrameOptions;

typedef enum : NSUInteger {
    SXKeyframeTypeOpacity,
    SXKeyframeTypePosition,
    SXKeyframeTypeScale,
    SXKeyframeTypeRotation,
    SXKeyframeTypeCount
}SXKeyframeType;
@interface SXRenderTrack : SXTrack
//位移
@property (nonatomic, assign) CGPoint position;
//缩放
@property (nonatomic, assign) CGPoint scale;
//旋转
@property (nonatomic, assign) CGFloat rotation;
//当前应用的变化矩阵
@property (nonatomic, assign) CGAffineTransform transform;
//不透明度
@property (nonatomic, assign) float opacity;
//是否纵向翻转
@property (nonatomic, assign) BOOL verticalFlip;
//是否横向翻转
@property (nonatomic, assign) BOOL horizontalFlip;

/**
 * 调整track的位置，会改变track的transform
 * @param coverAll 是否填充满整个画面
 * @param margin 当coverAll为NO时，track在整个画面留边边距为margin的范围里适配宽高完整展示
*/
- (void)fitToEditContext:(BOOL)coverAll margin:(int)margin;

/**
 * 获取当前track的尺寸
 * @return size
*/
- (CGSize)getTrackSize;

//帧动画——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
/**
 * 添加关键帧帧动画数据，如已存在对应关键帧则会修改对应的关键帧数据
 * @param type 关键帧类型
 * @param mill 相对于start time的局部关键帧时间，单位为毫秒
 * @param value 关键帧数据，不同类型的关键帧拥有不同的数据类型
 * Opacity，Rotation为NSNumber封装的float类型，Position，Scale为NSValue封装的CGPoint类型
 * Rotation为角度值
 * @param options 插值类型，影响自身与下一个关键帧之间的插值
 * @return 数据类型错误返回false
 */
- (BOOL)addKeyframeData:(SXKeyframeType)type time:(int64_t)mill value:(id)value options:(SXKeyFrameOptions)options;
/**
 * 添加关键帧帧动画数据，如已存在对应关键帧则会修改对应的关键帧
 * @param type 关键帧类型
 * @param mill 相对于start time的局部关键帧时间，单位为毫秒
 * @param value 关键帧数据，不同类型的关键帧拥有不同的数据类型
 * Opacity，Rotation为NSNumber封装的float类型，Position，Scale为NSValue封装的CGPoint类型
 * @param inTangent 插值曲线的结束点（1，1）的控制点，影响当前帧与上一帧间的插值
 * @param outTangent 插值曲线的起始点（0，0）的控制点，影响当前帧与下一帧间的插值
 * @return 数据类型错误返回false
 */
- (BOOL)addKeyframeData:(SXKeyframeType)type time:(int64_t)mill value:(id)value inTangent:(CGPoint)inTangent outTangent:(CGPoint)outTangent;
/**
 * 修改关键帧动画数据
 * @param type 关键帧类型
 * @param mill 相对于start time的局部关键帧时间，单位为毫秒
 * @param value 关键帧数据，不同类型的关键帧拥有不同的数据类型
 * Opacity，Rotation为NSNumber封装的float类型，Position，Scale为NSValue封装的CGPoint类型
 * @return 数据类型错误或不存在对应关键帧返回false
 */
- (BOOL)setKeyframeData:(SXKeyframeType)type time:(int64_t)mill value:(id)value;
/**
 * 获取对应时间的插值比例x，当前数据为（a * (1 - x) + bx），a代表前一关键帧数据，b代表后一关键帧数据
 * @param type 关键帧类型
 * @param mill 时间
 * Opacity，Rotation为NSNumber封装的float类型，Position，Scale为NSValue封装的CGPoint类型
 * @return 字典中包含的key@"ratio"：插值比例x,@"a"：前一关键帧数据,@"b"：b代表后一关键帧数据
*/
- (NSDictionary<NSString *, id> *)keyframeInterpolateRatio:(SXKeyframeType)type time:(int64_t)mill;
/**
 * 根据当前时间的值修改前一个或后一个关键帧的值，不增加关键帧
 * @param type 关键帧类型
 * @param keyframeTime 需要修改的关键帧时间，只能是当前时间的前一个或后一个关键帧的值，否则效果会出错，单位为毫秒
 * @param currentTime 当前的时间，单位为毫秒
 * @param currentValue 当前的数值
 * Opacity，Rotation为NSNumber封装的float类型，Position，Scale为NSValue封装的CGPoint类型
 * @return 数据类型错误或不存在对应关键帧返回false
 */
- (BOOL)setKeyframeData:(SXKeyframeType)type keyframeTime:(int64_t)keyframeTime currentTime:(int64_t)currentTime currentValue:(id)currentValue;
/**
 * 移除关键帧
 * @note 当移除最后一个关键帧时，轨道相应数据会保留为最后一个关键帧的数据
 * @param type 关键帧类型
 * @param mill 相对于start time的局部关键帧时间，单位为毫秒
 */
- (void)removeKeyframeData:(SXKeyframeType)type time:(int64_t)mill;
/**
 * 获取某类型的所有关键帧
 * @param type 关键帧类型
 * @return 关键帧数据 key为关键帧时间， value为关键帧属性
 * 其中关键帧属性中可能包含的key@"value"：关键帧数值,@"type"：关键帧类型,@"options"：关键帧差值类型,@"inTangent"：插值曲线的结束点（1，1）的控制点,@"outTangent"：插值曲线的起始点（0，0）的控制点
 */
- (NSDictionary<NSNumber *, NSDictionary<NSString *, id> *> *)keyframesWithType:(SXKeyframeType)type;
/**
 * 获取所有关键帧
 * @return 关键帧数据  key为关键帧时间， value为当前关键帧时间所有关键帧属性
 */
- (NSDictionary<NSNumber *, NSArray<NSDictionary<NSString *, id> *> *> *)keyframes;
/**
 * 清除某一类型所有关键帧
 * @note 轨道对应类型的数据保留第一个关键帧的数据
 * @param type 关键帧类型
 */
- (void)clearKeyFrames:(SXKeyframeType)type;

/**
 * 在轨道后附加一个转场效果，转场仅存在于轨道末尾，设置转场后，此轨道会与其后第一个渲染的轨道a进行转场，其他轨道不受影响.
 * 如果此时a也有转场且时间重叠则a的转场会失效
 * 如果此轨道已存在转场则会替换调已存在的转场
 * @warning 请注意转场时长的设置，超过轨道时长可能造成转场效果与预期不符
 * @param resource 转场资源，资源类型需为转场且资源有效
 * @param duration 转场时长
 * @return 是否添加成功
 */
- (BOOL)setTransition:(SXResource *)resource
             duration:(double)duration;

/**
 * 设置转场时长，转场时长受自身轨道时长与下一个相衔接的轨道显示时长影响
 * @warning 转场时长不得大于前后轨道显示时长的最小值
 * @param duration 转场时长
 */
- (void)setTransitionDuration:(double)duration;

/**
 * 获取轨道所附加的转场时间
 * @return 转场时长
 */
- (double)getTransitionDuration;

/**
 * 移除转场
 */
- (void)removeTransition;

/**
 * 查询轨道是否有转场
 * @return 查询轨道成功且有转场返回true，否则返回false
 */
- (BOOL)hasTransition;

/**
 * 获取轨道所附加的转场资源
 * @return 转场资源，如轨道查找失败或无转场资源返回nil
 */
- (SXResource *)getTranistionResource;

@end

#pragma mark - SXMediaTrack

typedef enum : NSUInteger {
    SXBlendNormal    = 0,
    SXBlendLighten,
    SXBlendDarken,
    SXBlendMultiply,
    SXBlendAverage,
    SXBlendAdd,
    SXBlendSubtract,
    SXBlendDifference,
    SXBlendNegation,
    SXBlendExclusion,
    SXBlendScreen,
    SXBlendOverlay
} SXBlendMode;

@class SXComposite;
@interface SXMediaTrack : SXRenderTrack<SXResourceDelegate, SXFilterDelegate, SXAnimationDelegate, SXVideoEffectDelegate, SXGenericEffectDelegate, SXTrackAnimationDelegate>

//颜色混合模式
@property (nonatomic, assign) SXBlendMode blendMode;
//是否在变速时需要声音轨道变调
//@property (nonatomic, assign) BOOL needParaphonia;
//设置常规变速数值, 获取当为曲线变速时返回平均速度, 变速后所有时间相关数据都会受影响
@property (nonatomic, assign) double speed;

/**
 * 获取合成
 * @return 若用合成创建媒体轨道，获取该合成，否则返回空
*/
- (SXComposite *)composite;

/**
 * 是否是静态图片
 * @return 是静态图片返回true，否则返回false
*/
- (BOOL)isStaticImage;

/**
 * 设置曲线变速
 * @warning 变速后所有时间相关数据都会受影响
 * @param path 变速曲线
 * @param ratio 速度超过1以后部分的倍率
 */
- (void)setSpeedByCurve:(UIBezierPath *)path ratio:(double)ratio;

/**
 * 获取曲线变速对应的曲线
 * @return 曲线
 */
- (UIBezierPath *)speedCurvePath;

/**
 * 获取曲线变速超过一倍速后Y值的倍率
 */
- (double)speedCurveRatio;

/**
 * 当前是否为曲线变速
 */
- (BOOL)hasSpeedCurve;

/**
 * 定格
 * @param time 相对于start time的局部时间
 */
- (void)setFreezeTime:(double)time;

/**
 * 取消定格
 */
- (void)cancelFreeze;
/**
 * 获取定格时间
 * @return 返回定格时间
 */
- (double)freezeTime;

/**
 * 是否有定格
 * @return 有定格返回true
*/
- (BOOL)hasFreeze;
/**
 * 获取是否含有音频
 * @return 是否含有音频
 */
- (BOOL)hasAudio;
/**
 * 设置是否启用音频
 * @param enable 是否启用
 */
- (void)setAudioEnable:(BOOL)enable;
/**
 * 设置音频淡入时长
 * @note 时长不受变速影响
 * @param fade 时长，单位为秒
 */
- (void)setFadeInDuration:(double)fade;
/**
 * 设置音频淡出时长
 * @note 时长不受变速影响
 * @param fade 时长，单位为秒
 */
- (void)setFadeOutDuration:(double)fade;
/**
 * 设置音量大小，默认音量为1
 * @param volume 音量
 */
- (void)setVolume:(float)volume;
/**
 * 设置音调大小，默认值为1
 * @param pitch 音调大小
 */
- (void)setPitch:(float)pitch;
/**
 * 获取是否启用
 * @return true表示启用
 */
- (BOOL)audioEnabled;
/**
 * 获取淡入时长
 * @return 单位为秒
 */
- (double)fadeInDuration;
/**
 * 获取淡出时长
 * @return 单位为秒
 */
- (double)fadeOutDuration;
/**
 * 获取音量
 * @return 音量
 */
- (float)volume;
/**
 * 获取音调
 * @return 音调
 */
- (float)pitch;

/**
 * 设置蒙版形状
 * @param shape 蒙版形状
*/
- (void)setMaskShape:(SXShape *)shape;

/**
 * 是否需要反转蒙版
 * @param inverse YES 反转 NO 不反转
*/
- (void)setInverseMaskShape:(BOOL)inverse;

/**
 * 当前是否反转了蒙版
 * @return 是否反转
*/
- (BOOL)isInverseMaskShape;

/**
 * 获取当前蒙版的形状
 * @return 形状数组
*/
- (SXShape *)getMaskShape;

/**
 * 裁剪素材
 * @param size 裁剪的大小
 * @param transform 裁剪应用的变化，以左上角为锚点
*/
- (void)cropMediaWithSize:(CGSize)size transform:(CGAffineTransform)transform;

/**
 * 获取裁剪矩阵
 *  @return 裁剪矩阵
*/
- (CGAffineTransform)cropTransform;
      
@end

#pragma mark - SXStickerTrack

@interface SXStickerTrack : SXRenderTrack<SXFilterDelegate, SXAnimationDelegate, SXVideoEffectDelegate, SXGenericEffectDelegate, SXTrackAnimationDelegate>

/**
 * 获取资源
 * @return 获取当前的资源
 */
- (SXResource *)getResource;

@end

#pragma mark - SXTextTrack

typedef enum : NSUInteger {
    SXStrokeStyleStrokeOverFill,
    SXStrokeStyleFillOverStroke,
} SXStrokeStyle;

typedef enum : NSUInteger {
    SXFontCacheModeImmediately,//不缓存字体，用完即释放
    SXFontCacheModeCache,//缓存字体，可能占用较告内存
} SXFontCacheMode;

typedef enum : NSUInteger {
    SXTextTypeLine,
    SXTextTypeBox,
} SXTextType;

typedef enum : NSUInteger {
    SXTextDirectionTypeHorizontal,
    SXTextDirectionTypeVertical,
} SXTextDirectionType;

typedef enum : NSUInteger {
    SXTextAlignmentTypeLeft,
    SXTextAlignmentTypeRight,
    SXTextAlignmentTypeCenter,
} SXTextAlignmentType;

@interface SXTextTrack : SXRenderTrack<SXTextAnimationDelegate, SXAnimationDelegate>
//设置文字内容
@property (nonatomic, strong) NSString *content;
//设置描边宽度，默认为0
@property (nonatomic, assign) float strokeWidth;
//设置文字大小，单位为像素
@property (nonatomic, assign) float fontSize;
//设置字符间距，单位为像素
@property (nonatomic, assign) int tracking;
//设置字体文件，默认使用初始设置的默认字体文件
@property (nonatomic, strong) NSString *fontFile;
//设置描边绘制方式，默认描边画在文字之下
@property (nonatomic, assign) SXStrokeStyle strokeStyle;
//设置文字方向
@property (nonatomic, assign) SXTextDirectionType direction;
//设置排版方式
@property (nonatomic, assign) SXTextAlignmentType alignment;
//设置文字类型, 默认为行文字，即不受文本框限制可自由编辑，支持手动换行
@property (nonatomic, assign) SXTextType textType;

/**
 * 设置文本框大小，仅文字类型为kBox时可用
 * @note 文本框大小默认为200*200
 * @param width 宽度
 * @param height 高度
 */
- (void)setBoxWidth:(int)width height:(int)height;
/**
 * 获取文本框宽度
 * @warning 有气泡时文本框实际宽度为气泡中定义的宽度，此函数仅返回
 * 接口设置的文本框宽度
 * @return 文本框宽度
 */
- (int)boxWidth;
/**
 * 获取文本框高度
 * @warning 有气泡时文本框实际宽度为气泡中定义的高度，此函数仅返回
 * 接口设置的文本框高度
 * @return 文本框高度
 */
- (int)boxHeight;
/**
 * 设置填充颜色，默认为白色
 * @param red [0-1]
 * @param green [0-1]
 * @param blue [0-1]
*/
- (void)setFillColorRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue;

/**
 * 设置描边颜色， 默认为白色
 * @param red [0-1]
 * @param green [0-1]
 * @param blue [0-1]
*/
- (void)setStrokeColorRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue;

/**
 * 设置文字气泡
 * @param resource 文字气泡资源
 * @return 设置成功返回true，否则返回false
 */
- (BOOL)setBubble:(SXResource *)resource;

/**
 * 移除文字气泡
 */
- (void)removeBubble;

/**
 * 气泡资源
 * @return 气泡资源路径，无气泡资源时，不可用
 */
- (SXResource *)bubbleResource;

/**
  * 设置预设样式
  * @param resource 预设样式资源
  * @return 设置成功返回true，否则返回false
  */
- (BOOL)setTextStyle:(SXResource *)resource;

/**
 * 重置文字样式为默认值
 */
- (void)resetTextStyle;

/**
 * 样式资源
 * @return 样式资源路径，无样式资源时，不可用
 */
- (SXResource *)styleResource;

/**
 * 设置是否向上自适应，即是否最大适配文本框大小
 * 默认值为true
 * @param up 是否向上自适应
 */
- (void)setAdaptUpToMaxSize:(BOOL)up;
@end


#pragma mark - SXVideoAssetTimeRange

@interface SXVideoAssetTimeRange : NSObject
@property (nonatomic,strong) SXTemplateAsset* asset;
//数组中每一个元素代表出现的一个时间段，每个时间段包含两个元素
//每个时间段中第一个元素表示在主合成中的开始显示时间 单位为秒
//每个时间段中第二个元素表示在主合成中的结束显示时间 单位为秒
@property(nonatomic, strong) NSMutableArray<NSArray<NSNumber *> *> *timeRanges;
@end

#pragma mark - SXTrackConfigUtils

@interface SXTrackConfigUtils : NSObject


/**
 获取模版对应底层渲染引擎的版本号
 
 @return 版本号
 */
-(NSString *)getUIVersion;

/**
 获取可替换素材
 
 @return 获取当前可替换素材
 */
- (NSArray<SXTemplateAsset *> *)getReplaceableAsset;

/**
 根据uikey获取可替换素材
 
 @return 根据uikey获取可替换素材
 */
- (SXTemplateAsset *)getAssetByUIKey:(NSString *)key;

/**
 获取所有可替换素材的时间区间
 
 @return 获取所有可替换素材的时间区间
 */
- (NSArray<SXVideoAssetTimeRange *> *)getReplaceableAssetTimeRange;

@end

#pragma mark - SXTemplateTrack

@interface SXTemplateTrack : SXRenderTrack<SXFilterDelegate, SXAnimationDelegate, SXVideoEffectDelegate, SXGenericEffectDelegate, SXTrackAnimationDelegate>

/**
 * 获取资源
 * @return 获取当前的资源
 */
- (SXResource *)getResource;

/**
 * 设置替换素材json
 * @param jsonString 替换json
 */
- (void)replaceWithJson:(NSString *)jsonString;

/**
 * 设置替换素材json
 * @param jsonString 替换json
 * @param customSourceProvider replaceJson中main_file对应的值，需要以"customProvider_"作为前缀表示用户自定义素材
 */
- (void)replaceWithJson:(NSString *)jsonString
   customSourceProvider:(NSDictionary<NSString *, SXCustomSourceProvider *> *)customSourceProvider;

/**
 * 获取资源信息
 * @return 获取当前资源信息
 */
- (SXTrackConfigUtils *)getConfigUtils;

/**
 根据uikey获取对应layer的当前时长
 
 @return 根据uikey获取对应layer的当前时长
 */
- (double)getLayerDurationByUIKey:(NSString *)key;

/**
 根据uikey获取对应layer的保护区时长
 
 @return 返回两段保护区的时长，第一个表示前保护区时长，第二个表示后保护区时长
 */
- (NSArray<NSNumber *> *)getLayerProtectTimeByUIKey:(NSString *)key;
@end

NS_ASSUME_NONNULL_END
