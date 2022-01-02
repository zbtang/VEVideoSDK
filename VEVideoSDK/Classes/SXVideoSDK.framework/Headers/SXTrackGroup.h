//
//  SXTrackGroup.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/3/31.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXTrack.h"
NS_ASSUME_NONNULL_BEGIN

/**
 * 轨道组，可以包含多个轨道
 * @warning 注意所有的对象对比是否相等时请使用id对比，引用可能会不同
*/
@interface SXTrackGroup : NSObject<SXEditAttributeDelegate>

/**
 * 在组的某个时间添加一个轨道，如无法容纳此轨道返回false
 * @param track 轨道
 * @param time 轨道的开始显示时间，等价于修改轨道displayTime
 * @return 添加成功返回true，失败返回false
 */
- (BOOL)addTrack:(SXTrack *)track displayTime:(double)time;


/**
 * 从组中移除一个轨道
 * @param trackId 轨道唯一id
 * @return 如组内有此轨道返回true，无此轨道返回false
 */
- (BOOL)removeTrack:(NSString *)trackId;


/**
 * 清空组内所有轨道
 */
- (void)clearTracks;

/**
 * 通过id查找组中此轨道所在的下一个轨道
 * @param trackId 轨道唯一id
 * @return 查找成功返回轨道实例对象，否则返回nullptr
 */
- (SXTrack *)findNextTrack:(NSString *)trackId;


/**
 * 通过id查找组中此轨道所在的上一轨道
 * @param trackId 轨道唯一id
 * @return 查找成功返回轨道实例对象，否则返回nullptr
 */
- (SXTrack *)findPreviousTrack:(NSString *)trackId;


/**
 * 通过id查找组内的轨道
 * @param trackId 轨道唯一id
 * @return 查找成功返回轨道实例对象，否则返回nullptr
 */
- (SXTrack *)track:(NSString *)trackId;


/**
 * displayTime   track     split time     new track    out point
 *   |-----------------------|--------------------------|
 * ----------------------------------------------------------------------
 * 拆分轨道，拆分后的轨道附加效果会被移除或者缩短时间，请重新获取相关数据
 * @note 拆分后的新轨道会自动加入此组中
 * @param trackId 轨道唯一id
 * @param time 相对于轨道自身displayTime拆分时间点
 * @return 查找轨道失败或拆分时间不在轨道显示范围内返回nullptr，否则返回轨道实例对象
 */
- (SXTrack *)splitTrack:(NSString *)trackId time:(double)time;

/**
 * 按开始显示时间首尾相接顺序排列轨道，音频轨道除外
 * @note 重排轨道会引起轨道显示时间区间及轨道顺序的变化，轨道顺序会按显示时间重新排序， 若时间相同按照添加的先后顺序排序
 * @note process_transition为true时前一个轨道有转场时，轨道将自动交叉到转场开始处，
 * 后一个轨道时长不足转场时长时，交叉时长为后一个轨道时长
 * @param processTransition 是否处理转场交叉
 */
- (void)arrangeTracks:(BOOL)processTransition;

/**
 * 获取组中轨道的最大结束时间
 * @return 轨道的最大结束时间
 */
- (double)duration;

/**
 * 获取所有轨道
 * @return 轨道链表
 */
- (NSArray *)tracks;

/**
 * 轨道唯一id
 * @return id
 */
- (NSString *)getGroupId;

@end

NS_ASSUME_NONNULL_END
