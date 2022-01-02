//
//  SXComposite.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2021/1/6.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXTrack.h"
#import "SXTrackGroup.h"
#import "SXResource.h"
NS_ASSUME_NONNULL_BEGIN

@class SXComposite;
@protocol SXTrackDataDelegate <NSObject>

/**
 * 通过id获取对应的组，id可通过类方法uuid获取
 * @param groupId 组的uuid
 * @return 组的实例对象，不存在对应的组时返回nullptr
 */
- (SXTrackGroup *)group:(NSString *)groupId;

/**
 * 在最后方追加一个新组
 * @return 新组的实例对象
 */
- (SXTrackGroup *)addNewGroup;

/**
 * 组是顺序存储的，因此可以在index所在的位置插入一个组
 * @param index 位置的索引，index超出组个数时等价于addNewGroup
 * @return 新组的实例对象
 */
- (SXTrackGroup *)insertNewGroupAt:(int)index;

/**
 * 通过id删除组，如果组内存在轨道则会移除所有轨道，但不会删除轨道
 * @param groupId 组的唯一id
 */
- (void)deleteGroup:(NSString *)groupId;

/**
 * 移动一个组到指定的位置
 * @param groupId 组的唯一id
 * @param index 组的顺序索引，从0开始（不包含主轨道和当前轨道）
 */
- (void)moveGroup:(NSString *)groupId toIndex:(int)index;

/**
 * 获取所有的组
 * @return 顺序存储的所有组
 */
- (NSArray *)groups;

/**
 * 创建媒体轨道，接受视频和图片素材
 * @param resource 资源对象
 * @return 媒体轨道
 */
- (SXMediaTrack *)createMediaTrack:(SXResource *)resource;

/**
 * 创建贴纸轨道
 * @param resource 资源对象
 * @param duration  持续时长
 * @return 贴纸轨道
 */
- (SXStickerTrack *)createStickerTrack:(SXResource *)resource duration:(double)duration;

/**
 * 创建文字轨道
 * @param duration 持续时长
 * @return 文字轨道
 * */
- (SXTextTrack *)createTextTrack:(double)duration;

/**
 * 创建音频轨道
 * @param resource 资源对象
 * @return 音频轨道
 * */
- (SXAudioTrack *)createAudioTrack:(SXResource *)resource;

/**
 * 创建模板轨道
 * @param resource 资源对象
 * @param applyTimeExtend 是否应用时间伸缩
 * @return 模板轨道
 * */
- (SXTemplateTrack *)createTemplateTrack:(SXResource *)resource applyTimeExtend:(BOOL)applyTimeExtend;

/**
 * 通过轨道id删除一个轨道， 该track将被释放，后续不能再使用
 * @param trackId 轨道id
 */
- (void)deleteTrack:(NSString *)trackId;

/**
 * 通过轨道id复制一个新的轨道
 * @param trackId 轨道id
 * @return    新的轨道，复制失败时返回空指针
 */
- (SXTrack *)cloneTrack:(NSString *)trackId;

/**
 * 根据point查找画布中的track
 *
 * @param point 相对于画布左上角点的坐标
 *
 * @return 如果有相应的track返回对象，否则返回nil
*/
- (SXTrack *)hitPoint:(CGPoint)point;

/**
 * 根据point查找画布中相应类型的track
 *
 * @param point 相对于画布左上角点的坐标
 * @param type 需要查找的track类型
 *
 * @return 如果有相应的track返回对象，否则返回nil
*/
- (SXTrack *)hitPoint:(CGPoint)point type:(SXTrackType)type;
@end

@protocol SXCompositeDelegate <NSObject>
/**
 * 合成宽度
 * @return 宽度
 */
- (int)width;
/**
 * 合成高度
 * @return 高度
 */
- (int)height;
/**
 * 合成帧率
 * @return 帧率
 */
- (int)fps;
/**
 * 合成帧数
 * @return 帧数
 */
- (int64_t)frames;
/**
 * 合成时长
 * @return 时长单位为秒
 */
- (double)duration;

/**
 * 获取合成中轨道的最大结束时间
 * @param excludeAudio 是否排除音频时长
 * @return 轨道的最大结束时间
 */
- (double)contentMaxTime:(bool)excludeAudio;

/**
 * 设置合成时长
 * @param frame 帧数
 */
- (void)setDurationInFrame:(int64_t)frame;

/**
 * 设置合成时长，时长会转换为对应的帧数保存
 * @param seconds 时长，单位为秒
 */
- (void)setDuration:(double)seconds;

@end

@interface SXComposite : NSObject <SXCompositeDelegate, SXTrackDataDelegate, SXEditAttributeDelegate>

/**
 * 获取当前composite的ID
 * @return ID
*/
- (NSString *)getCompositeId;

@end

NS_ASSUME_NONNULL_END
