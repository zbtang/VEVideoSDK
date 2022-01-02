//
//  SXEditManager.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/3/31.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXEditOptions.h"
#import "SXTrack.h"
#import "SXTrackGroup.h"
#import "SXComposite.h"
#import <OpenGLES/EAGL.h>
NS_ASSUME_NONNULL_BEGIN

//预览时音画同步方式
typedef enum : NSUInteger {
    SXEditPlayerSynchronizeNone,           //相互不影响
    SXEditPlayerSynchronizeLoopAudio,      //当画面无法跟上，音频播放完毕后循环
    SXEditPlayerSynchronizeDropFrame       //当画面无法跟上，丢弃部分帧追赶音频进度
} SXEditPlayerSynchronizeType;
/**
 * SXEditManager委托
 */
@protocol SXEditManagerDelegate <NSObject>

/**
 * 播放进度更新
 * @param frameIndex 当前播放的帧序列号
 */
- (void)playFrameIndex:(NSInteger)frameIndex;

/**
 * 渲染开始
 */
-(void)renderStarted;

/**
 * 渲染结束
 * @param tempUrl 结果文件路径
 */
-(void)renderFinished:(NSURL *)tempUrl;

/**
 * 渲染被取消
 */
-(void)renderCancelled;

/**
 渲染失败

 @param error 错误信息
 @warning 当erro中userinfo包含request， 且为"/render/charge/cpt/confirm", 请记录路径和订单流水号(必须对应)，以便稍后调用decodeFile重新尝试输出视频文件
          渲染回调的文件如果不是直接再次导出，请注意保存该文件，不然可能会被覆盖
 */
-(void)renderFailed:(NSError *)error;
/**
 * 渲染进度更新
 * @param progress 渲染进度，0~1
 */
-(void)renderProgress:(float) progress;

@end


@interface SXEditManager : NSObject<SXTrackDataDelegate, SXCompositeDelegate, SXEditAttributeDelegate>

/**
 * SXEditManager委托
 */
@property (nonatomic, weak) id<SXEditManagerDelegate> delegate;

/**
 * 获取和设置当前渲染输出的文件路径
 * @warning 完整的视频路径，需要包含文件名以及后缀，该路径若已有文件会被删除重写
 */
@property (nonatomic, copy) NSString *outputPath;

/**
 * 预览时音画同步方式，默认SXEditPlayerSynchronizeDropFrame
 */
@property (nonatomic, assign) SXEditPlayerSynchronizeType synchronizeType;

/**
 * 初始化编辑管理类
 * @param options 初始化参数，初始化时生效，后期修改无效
*/
- (instancetype)initWithOptions:(SXEditOptions *)options;

/**
 * 获取和设置当前编码器的比特率系数，默认值为0.25
 * @attention 编码器的比特率计算公式为 width * height * framerate * bpp
 * @warning 注意，设置只能在开始渲染之前调用
 */
@property (nonatomic, assign) float bpp;

/**
 * 获取和设置当前编码器的比特率，默认值为(width * height * framerate * 0.25)
 * @attention 编码器的比特率
 *  @warning 注意，设置只能在开始渲染之前调用
 */
@property (nonatomic, assign) int bitRate;
/**
 * 初始化编辑管理类
 * @param options 初始化参数，初始化时生效，后期修改无效
 * @param options 初始化参数，从 json 导入剪辑信息
*/
- (instancetype)initWithOptions:(SXEditOptions *)options jsonString:(NSString *)jsonString;

/**
 * SDK内部使用帧数计算，消除时间转化中的误差
 * @return 去掉误差后的时间
*/
- (double)removeTimeError:(double)time;

/**
 * 设置背景颜色, 默认黑色
 * @param red [0-1]
 * @param green [0-1]
 * @param blue [0-1]
 * */
- (void)setBackgroundColorRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue;

/**
 * 重设 edit 尺寸
 *
 * @param size 尺寸
 * @return 是否成功
 */
- (BOOL)resetEditSize:(CGSize)size;

/**
 * 创建一个合成
 * @param width 宽度
 * @param height 高度
 * @param frame 时长
 * @return 合成对象，失败返回空对象
 */
- (SXComposite *)createCompositeWidth:(int)width height:(int)height frame:(int64_t)frame;

/**
 * 创建大小与edit manager大小帧率一致的合成
 * @note 此合成大小保持与edit manager大小一致
 * @param frame 时长
 * @return 合成对象，失败返回空对象
 */
- (SXComposite *)createCompositeFrame:(int64_t)frame;

/**
 * 删除合成
 * @param compositeId 合成id
 */
- (void)deleteComposite:(NSString *)compositeId;

/**
 * 生成剪辑信息到 json
 *
 * @return json string
 */
- (NSString *)toJson;

#pragma mark - Play and Render
/**
 * 开始预览
 * @return 是否成功
 */
- (BOOL)start;

/**
 * 暂停预览
 * @return 是否成功
 */
- (BOOL)pause;

/**
 * 停止预览,释放资源
 * @warning 调用时需要确保其他方法已经调用结束，否则资源释放后其他方法继续执行可能导致闪退
 * @return 是否成功
 */
- (BOOL)stop;

/**
 * 获取播放状态
 * @return 是否正在播放
 */
- (BOOL)isPlay;

/**
 * 开始渲染
 * @return 是否开始成功
 */
- (BOOL)startRender;

/**
 * 取消渲染
 */
- (void)cancelRender;

/**
 * 设置时间进度
 * @param second 新的时间进度，秒为单位
 * @return 是否设置成功
 */
- (BOOL)seek:(float)second;

/**
 * 绘制当前帧
 * @param forceUpdate 是否强制刷新当前帧
 * @warning 时间不变时刷新当前帧一般会使用缓存数据来减少渲染量，强制刷新会
 * 使用所有资源重新渲染
 */
- (void)draw:(BOOL)forceUpdate;

/**
 * 获取播放器所使用的视图对象
 * @return UIView视图对象，获取到之后可以添加显示到界面上
 */
- (UIView *)getPlayerView;

/**
 * 获取GLContext
 * @return 当前渲染线程的GLContext
 */
- (EAGLContext *)getGLContext;

/**
 录制文件导出失败后重试接口,参数由录制回调的错误中获得
 
 @param filePath 加密文件路径, 对应key - filePath
 @param orderSN 订单流水号, 对应key - orderSN
 @param featureString 订单功能, 对应key - featureString
 @param outputPath 解密文件输出路径
 @param completeHandler 完成回调
 
 @warning 一个订单对应一个加密文件，参数不要修改，不要用来解密其他文件，可能造成文件错误且扣费成功
 解压完成后不会删除原文件
 */
+ (void)decodeFile:(NSString *)filePath
           orderSN:(NSString *)orderSN
     featureString:(NSString *)featureString
        outputPath:(NSString *)outputPath
   completeHandler:(void (^)(NSError *))completeHandler;

@end

NS_ASSUME_NONNULL_END
