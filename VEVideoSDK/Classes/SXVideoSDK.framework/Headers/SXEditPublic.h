//
//  SXEditPublic.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2021/4/13.
//  Copyright © 2021 Zhiqiang Li. All rights reserved.
//

#ifndef SXEditPublic_h
#define SXEditPublic_h

@protocol SXEditAttributeDelegate <NSObject>

//数据存储相关，可在存储一些数据
/**
 * 设置键值对
 * @param key 唯一键
 * @param value 值
 */
- (void)setField:(NSString *)key value:(NSString *)value;
/**
 * 获取键值
 * @param key 唯一键
 * @return 值
 */
- (NSString *)getField:(NSString *)key;
/**
 * 移除数据
 * @param key 唯一键
 */
- (void)removeField:(NSString *)key;
/**
 * 清除所有数据
 */
- (void)clearFields;

/**
 * 获取数据对象
 * @return 数据map
 */
- (NSDictionary<NSString *, NSString *> *)fields;

@end

#endif /* SXEditPublic_h */
