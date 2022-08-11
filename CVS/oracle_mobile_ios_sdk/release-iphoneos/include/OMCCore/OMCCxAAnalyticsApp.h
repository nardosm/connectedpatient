//
//  OMCCxAAnalyticsApp.h
//  OMCCore
//
//  Copyright © 2017 Oracle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OMCMobileComponent.h"

NS_ASSUME_NONNULL_BEGIN

/**
 AnalyticsApp holds the settings that allow a cxa analytics app service proxy
 to communicate with server.
 */
@interface OMCCxAAnalyticsApp : OMCMobileComponent

/**
 The analytic app's application key, as specified by the OMC property list file
 (`OMC.plist`).
 */
@property (readonly) NSString* appKey;

@end


#pragma mark - constants

/**
 The analytics app base path (`cxacol`).
 */
extern NSString* const OMCCxAAnalyticsAppPath;

/**
 The analytics app `appKey` property name.
 */
extern NSString* const OMCCxAAnalyticsAppAppKeyPropertyName;

/**
 The analytics app `authentication` property name.
 */
extern NSString* const OMCCxAAnalyticsAppAuthenticationPropertyName;

/**
 The analytics app `oauth` property name.
 */
extern NSString* const OMCCxAAnalyticsAppOAuthPropertyName;

/**
 The Application ID header field name
 (`"Oracle-Mobile-Analytics-Application-ID"`).
 */
extern NSString* const OMCCxAAnalyticsApplicationIDHTTPHeaderName;

NS_ASSUME_NONNULL_END
