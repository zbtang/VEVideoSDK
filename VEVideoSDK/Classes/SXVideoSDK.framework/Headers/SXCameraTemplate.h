//
//  SXCameraTemplate.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2019/11/8.
//  Copyright © 2019 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SXCameraTemplate : NSObject
//相机模板名称
@property (nonatomic, copy, readonly) NSString *name;
//相机模板版本号
@property (nonatomic, strong, readonly) NSString *version;

//是否打开美颜
@property (nonatomic, assign) BOOL enableBeauty;
//美白 defalut:50 range(0 - 100)
@property (nonatomic, assign) int complexion;
//磨皮defalut:50 range(0-100)
@property (nonatomic, assign) int adjust;

//是否打开五官调节
@property (nonatomic, assign) BOOL enableFaceReshape;
//瘦下巴 defalut:0 range(-50 -- 100)
@property (nonatomic, assign) int smallChin;
//大眼  defalut:0 range(-50 -- 50)
@property (nonatomic, assign) int bigEye;
//下巴长度  defalut:0 range(-50 -- 50)
@property (nonatomic, assign) int chinStrength;
//瘦脸 defalut:0 range(-50 -- 100)
@property (nonatomic, assign) int smallFace;
//嘴型  defalut:0 range(-50 -- 50)
@property (nonatomic, assign) int smallMouth;
//鼻子长度  defalut:0 range(-50 -- 50)
@property (nonatomic, assign) int noseStrength;
//鼻翼宽度  defalut:0 range(-50 -- 50)
@property (nonatomic, assign) int noseWidth;
//额头宽度  defalut:0 range(-50 -- 50)
@property (nonatomic, assign) int foreHeadStrength;

//是否打开抠图
@property (nonatomic, assign) BOOL enableChromaKey;
//defalut:70 range(0-1000)
@property (nonatomic, assign) float chromaSimilarity;
//defalut:50 range(0-1000)
@property (nonatomic, assign) float chromaSmoothness;
//defalut:50 range(0-1000)
@property (nonatomic, assign) float chromaSpillReduce;
//defalut:RGB(0,1,0)
@property (nonatomic, strong) UIColor *chromaColor;


/**
 * 初始化一个相机模板实例
 * @param filePath 相机模板文件夹路径
 * @return 相机模板实例
 */
- (instancetype)initWithFilePath:(NSString *)filePath;

/**
 检测相机模板的 version 是否被当前引擎全部支持
 
 @return  1 表示相机模板版本高于引擎版本，不是完整支持， 返回 0， -1 表示可以完整支持
 */
- (int)compareWithCurrentVersion;

@end

NS_ASSUME_NONNULL_END
