//
//  SXResource.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2021/4/13.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXEditPublic.h"
NS_ASSUME_NONNULL_BEGIN

#pragma mark - SXResourceDelegate
@class SXResource;
@protocol SXResourceDelegate <NSObject>

/**
 * 设置资源
 * @param resource 资源对象
 * @return 设置成功返回true，否则返回false
 */
- (BOOL)setResource:(SXResource *)resource;

/**
 * 获取资源
 * @return 获取当前的资源
 */
- (SXResource *)getResource;

@end

typedef enum : NSUInteger {
    SXResourceTypeUnknown,
    SXResourceTypeTexture,
    SXResourceTypeComposite,
    SXResourceTypeAudioFile,             // 音频文件或有音轨的视频文件
    SXResourceTypeMediaFile,             // 媒体文件包（图片或视频）
    SXResourceTypeSticker,               // 贴纸包
    SXResourceTypeTextStyle,             // 文字样式(与SXEffect类型对应)
    SXResourceTypeTextBubble,            // 文字气泡(与SXEffect类型对应)
    SXResourceTypeTextAnimation,         // 文字动画(与SXEffect类型对应)
    SXResourceTypeFilter,                // 滤镜(与SXEffect类型对应)
    SXResourceTypeTransition,            // 转场(与SXEffect类型对应)
    SXResourceTypeAnimation,             // 视频动画(与SXEffect类型对应)
    SXResourceTypeVideoEffect,           // 视频特效(与SXEffect类型对应)
    SXResourceTypeTrackAnimation,        // 轨道动画(与SXEffect类型对应)
    SXResourceTypeFontFile,              // 字体文件
    SXResourceTypeTemplate               // 模板文件
}SXResourceType;

typedef enum : NSUInteger {
    SXFileTypeUnknownFile,
    SXFileTypePackage,
    SXFileTypeAudio,
    SXFileTypeVideo,
    SXFileTypeImage,
    SXFileTypeGif,
    SXFileTypeVideoSequence,
    SXFileTypeFontFile
}SXFileType;

@class SXComposite;
@interface SXResource : NSObject <SXEditAttributeDelegate>

/**
 * 初始化资源
 * @param type 资源类型
 * @param path 资源路径
 */
- (instancetype)initWithType:(SXResourceType)type path:(NSString *)path;

/**
 * 初始化资源
 * @param composite 合成对象
 */
- (instancetype)initWithComposite:(SXComposite *)composite;

/**
 * 资源绝对路径，kPackage类型资源为资源包主文件夹路径
 * @return 绝对路径
 */
- (NSString *)resourcePath;

/**
 * 获取资源类型，不同资源有不同的属性
 * @return 资源类型
 */
- (SXResourceType)resourceType;

/**
 * 资源是否有效
 * @return 资源无效返回false
 */
- (BOOL)isValid;

/**
 * 获取宽度
 * @return 宽度
 */
- (int)width;

/**
 * 获取高度
 * @return 高度
 */
- (int)height;

/**
 * 获取时长
 * @return 单位为秒
 */
- (double)duration;

/**
 * 获取文件类型
 * @return 文件类型
 */
- (SXFileType)fileType;
/**
 * 资源包的id，资源包带有唯一id，仅kPackage类型资源有效
 * @return 资源id
 */
- (NSString *)packageUUid;
/**
 * 资源描述，kPackage类型的文件一般会带有描述信息
 * @return 描述信息
 */
- (NSString *)description;

//音频相关
/**
 * 获取音频采样率
 * @return 采样率，单位Hz
 */
- (double)sampleRate;
/**
 * 获取音频声道数
 * @return 声道数
 */
- (unsigned int)channels;

//合成相关
- (NSString *)compositeId;

/**
 * 设置是否应用设计师定义的模板包设置
 * @note 模板包设置包括时间跟随设置、时间扩展设置、画面适配设置等，
 * apply为true时模板包的设置会在加载时覆盖效果对应的属性。当设计师设置
 * 这些属性为无时，不会修改效果对应的属性
 * @param apply true表示应用设置，默认值为true
 * @warning 需要在用资源初始化轨道或特效之前设置，后期修改无效
 */
- (void)setApplyResourceSettings:(BOOL)apply;
/**
 * 获取是否应用模板包设置
 * @return true表示应用模板包设置
 */
- (BOOL)applyResourceSettings;
/**
 * 设置是否允许自动插值
 * @warning 仅2.0版本包支持
 * @param enable 是否允许插值
 */
- (void)setInterpolatorEnable:(BOOL)enable;
/**
 * 是否开启2.0版本包的插值功能
 * @return 是否开启
 */
- (BOOL)isInterpolatorEnabled;

@end

NS_ASSUME_NONNULL_END
