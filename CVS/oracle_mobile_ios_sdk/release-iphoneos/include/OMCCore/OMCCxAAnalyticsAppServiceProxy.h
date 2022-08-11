//
//  OMCCxAAnalyticsAppServiceProxy.h
//  OMCCore
//
//  Copyright © 2017 Oracle. All rights reserved.
//

#import "OMCServiceProxy.h"
@class OMCCxAAnalyticsApp;

NS_ASSUME_NONNULL_BEGIN

/**
 Interface to an Oracle Mobile CxA Analytics App service proxy.
 */
@interface OMCCxAAnalyticsAppServiceProxy : OMCServiceProxy

/**
 The service proxy's analytics app.
 */
@property (readonly) OMCCxAAnalyticsApp* analyticsApp;

@end

NS_ASSUME_NONNULL_END
