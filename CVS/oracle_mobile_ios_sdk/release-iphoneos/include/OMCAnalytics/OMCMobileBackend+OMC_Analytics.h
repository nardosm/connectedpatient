//
//  OMCMobileBackend+OMC_Analytics.h
//  OMCAnalytics
//
//  Copyright (c) 2015, Oracle Corp. All rights reserved. 
//

#import "OMCMobileBackend.h"
@class OMCAnalytics;

NS_ASSUME_NONNULL_BEGIN

/**
 Extends `OMCMobileBackend` with Analytics-specific methods.
 */
@interface OMCMobileBackend (OMC_Analytics)

/**
 Returns the receiver's analytics service.
 */
- (OMCAnalytics*)analytics __deprecated_msg("see OMCCxAAnalytics");

/**
 Removes the receiver's analytics service.
 */
- (void)removeAnalytics __deprecated_msg("see OMCCxAAnalytics");

@end

NS_ASSUME_NONNULL_END
