//
//  OMCCxAAnalyticsApp+OMC_CxAAnalytics.h
//  OMCCxAAnalytics
//
//  Copyright (c) 2017 Oracle. All rights reserved.
//

#import "OMCCore/OMCCxAAnalyticsApp.h"
@class OMCCxAAnalytics;

NS_ASSUME_NONNULL_BEGIN

/**
 Extends `OMCCxAAnalyticsApp` with Analytics-specific methods.
 */
@interface OMCCxAAnalyticsApp (OMC_CxAAnalytics)

/**
 Returns the receiver's CxA analytics service.
 */
- (OMCCxAAnalytics*)analytics;

/**
 Removes the receiver's CxA analytics service.
 */
- (void)removeAnalytics;

@end

NS_ASSUME_NONNULL_END
