//
//  SXPlayerView.h
//  SXVideoEnging
//
//  Created by Yin Xie on 2019/1/7.
//  Copyright © 2019 Zhiqiang Li. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SXPlayerViewDelegate <NSObject>

- (void)updateContentScale;

@end

@interface SXPlayerView : UIView

@property (nonatomic, weak) id<SXPlayerViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
