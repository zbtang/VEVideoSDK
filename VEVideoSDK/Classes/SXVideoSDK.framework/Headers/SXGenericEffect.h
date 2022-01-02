//
//  SXGenericEffect.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2021/1/7.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#import "SXEffect.h"

NS_ASSUME_NONNULL_BEGIN
//名称, 字段, 类型, 范围, 默认值, 备注
extern NSString *const SXColorSettingsBrightness;   //亮度, brightness, float, [0, 1], 0
extern NSString *const SXColorSettingsContrast;     //对比度, contrast, float, [-1, 1], 0
extern NSString *const SXColorSettingsSaturation;   //饱和度, saturation, float, [-1, 1], 0
extern NSString *const SXColorSettingsSharpen;      //锐化, sharpen, float, [-1, 1], 0
extern NSString *const SXColorSettingsHighlight;    //高亮, highlight, float, [0, 1], 0
extern NSString *const SXColorSettingsShadow;       //阴影, shadow, float, [0, 1], 0
extern NSString *const SXColorSettingsExposure;     //曝光度, exposure, float, [-1, 1], 0
extern NSString *const SXColorSettingsHue;          //色相, hue, float, [0, 1], 0
extern NSString *const SXColorSettingsCCT;          //色温, cct, float, [-1,1], 0
extern NSString *const SXColorSettingsRed;          //红色通道, r, float, [-1,1], 0
extern NSString *const SXColorSettingsGreen;        //绿色通道, g, float, [-1,1], 0
extern NSString *const SXColorSettingsBlue;         //蓝色通道, b, float, [-1,1], 0

extern NSString *const SXChromaKeyColor;            //颜色, color, string, #000000 ~ #FFFFFF, #00FF00
extern NSString *const SXChromaKeySimilarity;       //相似度, similarity, float, [0, 1], 0.15
extern NSString *const SXChromaKeySmoothness;       //平滑度, smoothness, float, [0, 1], 0.07
extern NSString *const SXChromaKeySpillReduce;      //溢色消除, spill_reduce, float, [0, 1], 0.3
extern NSString *const SXChromaKeyEdgeThin;         //边缘缩进, edge_thin, int（像素）, [0, 100], 0
extern NSString *const SXChromaKeyEdgeFeather;      //边缘羽化, edge_feather, int （像素）, [0, 50], 0

extern NSString *const SXMultipleColorKeySimilarity;    //颜色, colors_str, string, #000000 ~ #FFFFFF, "#00FF00", 多个颜色用";"隔开 例："#00FF00; #FF00FF" 最多支持3个颜色
extern NSString *const SXMultipleColorKeySmoothness;    //相似度, similarity, float, [0, 1], 0.01
extern NSString *const SXMultipleColorKeySpillReduce;   //平滑度, smoothness, float, [0, 1], 0.00
extern NSString *const SXMultipleColorKeyEdgeThin;      //溢色消除, spill_reduce, float, [0, 1], 0
extern NSString *const SXMultipleColorKeyEdgeFeather;   //边缘缩进, edge_thin, int（像素）, [0, 100], 0
extern NSString *const SXMultipleColorKeySimilarity;    //边缘羽化, edge_feather, int （像素）, [0, 50], 0

extern NSString *const SXGaussianBlurRadius;        //模糊半径, radius, float, [0, 50], 0

extern NSString *const SXFaceBeautyBlur;            //磨皮强度, blur, float, [0, 30], 3
extern NSString *const SXFaceBeautySkinRange;       //磨皮范围, skin_range, float, [0, 100], 10
extern NSString *const SXFaceBeautyWhiten;          //皮肤美白, whiten, float, [0, 100], 30
extern NSString *const SXFaceBeautyRedden;          //皮肤红润, redden, float, [0,100], 0
extern NSString *const SXFaceBeautyPinking;         //皮肤粉嫩, pinking, float, [0,100], 0
extern NSString *const SXFaceBeautySkinHue;         //皮肤颜色, skin_hue, float, [0,1], 0.05

extern NSString *const SXTrackMattePath;            //遮罩文件, path, string, 无, 无, 绝对路径
extern NSString *const SXTrackMatteType;            //遮罩类型, type, int, [0, 3], 0, 0:亮度，1:反亮度，2:alpha，3:反alpha

typedef enum : NSUInteger {
    SXGenericEffectTypeColorAdjustment = 0,
    SXGenericEffectTypeChromaKey,
    SXGenericEffectTypeGaussianBlur,
    SXGenericEffectTypeFaceBeauty,
    SXGenericEffectTypeMultipleColorKey,
    SXGenericEffectTypeTrackMatte
}SXGenericEffectType;

@interface SXGenericEffect : SXEffect

/**
 * 获取内置特效的类型
 * @return 内置特效类型
 */
- (SXGenericEffectType)genericEffectType;
/**
 * 重置特效属性
 */
- (void)resetAttributes;
/**
 * 通过名称设置特效的属性
 * @param name 属性名称
 * @param value 属性值
 * @return 是否设置成功，名称错误会导致设置失败
 */
- (BOOL)setAttributeInt:(NSString *)name value:(int)value;
/**
 * 通过名称设置特效的属性
 * @param name 属性名称
 * @param value 属性值
 * @return 是否设置成功，名称错误会导致设置失败
 */
- (BOOL)setAttributeFloat:(NSString *)name value:(float)value;
/**
 * 通过名称设置特效的属性
 * @param name 属性名称
 * @param value 属性值(设置颜色为十六进制字符串)
 * @return 是否设置成功，名称错误会导致设置失败
 */
- (BOOL)setAttributeString:(NSString *)name value:(NSString *)value;
/**
 * 通过属性名称获取属性值
 * @param name 属性名称
 * @return 是否获取到属性值，名称错误会导致获取失败
 */
- (id)getAttributeValue:(NSString *)name;
/**
 * 获取所有属性及属性值
 * @return 属性名称与属性值的对应字典
 */
- (NSDictionary<NSString *, id> *)getAttributes;

@end

NS_ASSUME_NONNULL_END
