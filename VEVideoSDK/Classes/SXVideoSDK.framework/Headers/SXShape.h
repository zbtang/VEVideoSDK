//
//  SXShape.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2020/4/28.
//  Copyright © 2020 Zhiqiang Li. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface SXShape : NSObject

/// 清空所有path
- (void)clear;

/// 移动到点
/// @param point 点的坐标
- (void)moveTo:(CGPoint)point;

/// 绘制直线
/// @param point 终点坐标
- (void)lineTo:(CGPoint)point;

/// 绘制贝塞尔曲线
/// @param point 终点坐标
/// @param cp1 control point1
/// @param cp2 control point2
- (void)bezierTo:(CGPoint)point cp1:(CGPoint)cp1 cp2:(CGPoint)cp2;

/// 绘制贝塞尔曲线
/// @param point 终点坐标
/// @param cp control point
- (void)quadTo:(CGPoint)point cp:(CGPoint)cp;

/// 封闭路径
- (void)closePath;

/// 绘制矩形
/// @param rect 矩形frame
- (void)rect:(CGRect)rect;

/// 绘制圆角矩形
/// @param rect 矩形frame
/// @param corner 圆角大小
- (void)roundRect:(CGRect)rect corner:(CGFloat)corner;

/// 绘制椭圆形
/// @param center 中心坐标
/// @param radiusX 宽度半径
/// @param radiusY 高度半径
- (void)ellipse:(CGPoint)center radiusX:(CGFloat)radiusX radiusY:(CGFloat)radiusY;

/// 绘制原型
/// @param center 中心坐标
/// @param radius 半径
- (void)circle:(CGPoint)center radius:(CGFloat)radius;

/// 旋转，会应用到已经绘制的所有路径上
/// @param angle 旋转角度
- (void)rotate:(CGFloat)angle;

/// 位移，会应用到已经绘制的所有路径上
/// @param translate 横纵位移
- (void)translate:(CGPoint)translate;

/// 缩放，会应用到已经绘制的所有路径上
/// @param scale 宽高缩放比例
- (void)scale:(CGSize)scale;

/// 综合变化，会应用到已经绘制的所有路径上
/// @param transform 变化
- (void)transform:(CGAffineTransform)transform;

/// 获取shape中所包含所有路径
/// 每个元素包含一段路径
/// @return 路径数组
- (NSArray<UIBezierPath *> *)getPaths;

/// 获取蒙版位置宽高
/// @return 蒙版的位置宽高
- (CGRect)getBbox;

@end

NS_ASSUME_NONNULL_END
