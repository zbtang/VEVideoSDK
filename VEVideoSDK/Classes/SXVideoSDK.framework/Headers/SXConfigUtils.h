//
//  SXConfigUtils.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2021/3/30.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    SXTemplateUndefined = 0,    
    SXTemplateTypeNormal = 1,           // 标准模板
    SXTemplateTypeDynamic = 1 << 1,     // 动态模板
    SXTemplateTypeFilter = 1 << 2,      // 滤镜功能
    SXTemplateTypeCustom = 1 << 3,      // 自定义模板
    SXTemplateTypeImage = 1 << 4,       // 图片滤镜功能
    SXTemplateTypeVideoClip = 1 << 5,   // 视频剪辑功能
    SXTemplateTypeSourceCut = 1 << 6,   // 裁剪功能
    SXTemplateTypeSticker = 1 << 7,     // 贴纸模板
    SXTemplateTypeCamera = 1 << 8,      // 摄像机模板
    SXTemplateTypePowerText = 1 << 9,   // 高级字符动画功能
    SXTemplateTypeModule = 1 << 10,     // 扩展模块类型
} SXTemplateType;

typedef enum : NSUInteger {
    SXSourceTypeUnknown,              //未知类型
    SXSourceTypeAVFile,               //图片或视频
    SXSourceTypeGLTexture,            //GL纹理
    SXSourceTypeRenderComp,           //合成
    SXSourceTypeSolidColor,           //纯色
    SXSourceTypeCustomVideoProvider,  //自定义流
    SXSourceTypePowerText             //高级文字
}SXSourceType;

typedef enum : NSUInteger {
    SXReplaceTypeNone,          //不可编辑
    SXReplaceTypeMediaFile,     //图片或视频
    SXReplaceTypeText,          //旧版以图片形式展示的文字
    SXReplaceTypePowerText      //高级文字
}SXReplaceType;

//只作为模板数据的获取，修改无效
@interface SXTemplateAsset : NSObject
//检测素材是否有效
@property(nonatomic, assign) BOOL isValid;
//素材id
@property(nonatomic, copy) NSString *key;
//素材的uikey,uikey由设计师导出模板时指定,无uikey返回空字符串
@property(nonatomic, copy) NSString *uiKey;
//素材名称
@property(nonatomic, copy) NSString *name;
//素材原始json字符串
@property(nonatomic, copy) NSString *assetJson;
//素材的宽度
@property(nonatomic, assign) NSInteger width;
//素材的高度
@property(nonatomic, assign) NSInteger height;
//可编辑素材的类型
@property(nonatomic, assign) BOOL isReplaceable;
@property(nonatomic, assign) SXReplaceType replaceType;
//素材类型
@property(nonatomic, assign) SXSourceType sourceType;
@end

@interface SXTemplateAssetTimeRange : NSObject
@property(nonatomic, strong) SXTemplateAsset *asset;
//数组中每一个元素代表出现的一个时间段，每个时间段包含两个元素
//每个时间段中第一个元素表示在主合成中的开始显示时间 单位为秒
//每个时间段中第二个元素表示在主合成中的结束显示时间 单位为秒
@property(nonatomic, strong) NSMutableArray<NSArray<NSNumber *> *> *timeRanges;
@end

@interface SXConfigUtils : NSObject

/**
 * 仅通过替换文件数量来计算时长
 * @param path 模板json数据的路径
 * @param fileCount 动态模板需要文件数量以计算时长。标准模板不需要，传入0即可。
 */
- (instancetype)initWithPath:(NSString *)path fileCount:(NSInteger)fileCount;

/**
 * 支持视频裁剪和动态适配的构造方式
 * @param path 模板json数据的路径
 * @param replaceJson 用户可替换素材,根据规范结构组成
 * [规范参考http://www.seeshiontech.com/docs/page_103.html]
 * @param adaptVideo 是否适配视频长度，仅对动态模版有效
 */
- (instancetype)initWithPath:(NSString *)path replaceJson:(NSString *)replaceJson adaptVideo:(BOOL)adaptVideo;

/**
 获取此模版可生成视频的时长
 @return 单位为秒
 */
- (float)getDuration;
/**
 模版是否可用，创建ConfigUtils时会检查模版的可用性

 @return 是否可用
 */
- (bool)isValid;

/**
 获取主合成的FPS

 @return 返回主合成的FPS
 */
- (float)getFps;

/**
 获取此模版可生成视频的时长，单位为帧

 @return 视频的时长
 */
- (NSInteger)getFrameCount;

/**
 获取主合成的宽，单位为像素

 @return 主合成的宽
 */
- (NSInteger)getWidth;
/**
 获取主合成的宽，单位为像素
 
 @return 主合成的宽
 */
- (NSInteger)getHeight;
/**
 获取模版类型
 
 @return 模版类型 SXTemplateType
 */
- (SXTemplateType)getTemplateType;

/**
 获取模版对应底层渲染引擎的版本号
 
 @return 版本号
 */
- (NSString *)getVersion;

- (NSString *)getUIVersion;

- (NSString *)getDescription;

- (NSString *)getUUid;
/**
 * 获取所有可编辑的素材信息，顺序与json中替换顺序一致
 * @return 可编辑的素材信息
 */
- (NSArray<SXTemplateAsset *> *)getReplaceableAsset;
/**
 * 通过UIKey查找素材信息
 * @note 普通模板通过素材的UIKey查找，动态模板通过图层的UIKey查找
 * @param key UIKey
 * @return 素材信息，未查找到则返回空对象，使用时请检查对象是否有效
 */
- (SXTemplateAsset *)getAssetByUIKey:(NSString *)key;
/**
 * 根据前缀替换规则获取动态模板中一个文件（main_file）所关联的素材信息
 * @note 仅动态模板有效，仅支持新版标记方式
 * @param index 动态模板的主替换文件索引
 * @return 主替换文件相关联的的素材信息
 */
- (NSArray<SXTemplateAsset *> *)getRelatedAssetForFile:(int)index;
/**
 * 获取可替换资源的在主合成中的显示时间区间，顺序与可替换素材顺序一致
 * @warning 仅标准模板有效，显示时间区间仅表示模板设计中的显示时间，
 * 不保证与实际视频画面的显示时间一致（可能被其他画面遮挡、超出画面范围等原因）
 * 不代表素材时长
 * 不支持对合成使用时间重映射，支持时间伸缩
 * @return 可替换资源的显示时间区间
 */
- (NSArray<SXTemplateAssetTimeRange *> *)getReplaceableAssetTimeRange;
@end

NS_ASSUME_NONNULL_END
