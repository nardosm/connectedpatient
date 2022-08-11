//
//  OMCCxAAnalytics.h
//  MIECS
//
//  Copyright © 2017 Oracle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OMCCore/OMCCxAAnalyticsAppServiceProxy.h"

#import "OMCCxAEvent.h"
#import "OMCCxARequestCallback.h"

#define  OMCCxAScreenViewEvent                 OMCCxAScreenView
#define  OMCCxAPageViewEvent                   OMCCxAPageView
#define  OMCCxAEcommerceTransactionEvent       OMCCxAEcommerce
#define  OMCCxAEcommerceTransactionBuilder     OMCCxAEcommTransactionBuilder
#define  OMCCxAEcommerceTransactionItemEvent   OMCCxAEcommerceItem
#define  OMCCxAEcommerceTransactionItemBuilder OMCCxAEcommTransactionItemBuilder
#define  OMCCxACustomEvent                     OMCCxAStructured
#define  OMCCxACustomEventBuilder              OMCCxAStructuredBuilder

NS_ASSUME_NONNULL_BEGIN

/**
  OMCCxAAnalytics The class to handle all event trackings.
 */

@interface OMCCxAAnalytics : OMCCxAAnalyticsAppServiceProxy

/**
  enabled: If set to true, all event handlings will be enabled.  Otherwise, event handlings are disabled.
 */

@property (readonly) BOOL enabled;

/**
  profileName : name of profile.
 */

@property (readonly) NSString* profileName;


/**
 * Log or send out an event to collector.
 * @param event The event to be sent from sdk to collector.
 *
 */

- (void) logEvent:(id) event;

/**
 * Resumes all event tracking and restarts the session checking.
 */

- (void) resumeEventTracking;

/**
 * Pauses all event tracking, storage and session checking.
 */

- (void) pauseEventTracking;

/**
 * Empties the buffer of events using the respective HTTP request method in httpMethod.
 */

- (void) flush;

/**
 * Set foreground timeout in seconds.
 @param foregroundTimeout foregroundTimeout to be set in seconds.
 */

- (void) setForegroundTimeout:(NSInteger)foregroundTimeout;


/**
 * Sets a new check interval and restarts the timer
 @param checkInterval checkInterval to be set in seconds.
 */
- (void) setCheckInterval:(NSInteger)checkInterval;


/**
 * Set background timeout in seconds.
 @param backgroundTimeout backgroundTimeout to be set in seconds.
 */

- (void) setBackgroundTimeout:(NSInteger)backgroundTimeout;

/**
 * Set emitter thread pool size.
 @param emitThreadPoolSize thread pool size to be set.
 */

- (void) setEmitThreadPoolSize:(NSInteger)emitThreadPoolSize;

/**
 * Set call back to keep track of events sent.
 @param callback callback to be set.
 */

- (void) setCallback:(id<OMCCxARequestCallback>)callback;

/**
 * Sets the User ID
 * @param uid as a String
 */
- (void) setUserId:(NSString *)uid;

@end


#pragma mark - Constants

/**
 The Analytics library's current version.
 */
extern NSString* const OMCCxAAnalyticsVersion;

/**
 The `analytics` service's properties name.
 */
extern NSString* const OMCCxAAnalyticsPropertyName;

/**
 The analytics service's `enabled` property name.
 */
extern NSString* const OMCCxAAnalyticsEnabledPropertyName;

/**
 The analytics service's `enabled` default value (`YES`).
 */
extern BOOL const OMCCxAAnalyticsEnabledDefault;

/**
 The analytics service's `notification` property name.
 */
extern NSString* const OMCCxAAnalyticsNotificationPropertyName;

/**
 The analytics service's notification `profileName` property name.
 */
extern NSString* const OMCCxAAnalyticsProfileNamePropertyName;

/**
 The analytics service's authentication scope.
 */
extern NSString* const OMCCxAAnalyticsAuthenticationScope;

NS_ASSUME_NONNULL_END
