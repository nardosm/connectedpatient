//
//  OMCAnalytics.h
//  OMCAnalytics
//
//  Copyright (c) 2015, Oracle Corp. All rights reserved. 
//

#import <Foundation/Foundation.h>
#import "OMCMobileBackendServiceProxy.h"
@protocol OMCAnalyticsDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 Library interface to the Oracle Mobile Cloud Analytics service.
 
 **Device Location Support**
 
 By default, the Analytics library captures the device's location with each Analytics
 event and session start/end. As a result, the first time the Analytics library records
 a session start, the library will request authorization to access the device's location.
 If the library's client app has not already requested this authorization, the user will
 be prompted via a dialog.
 
 **[iOS 8 and later]** By default, the Analytics library will request "when in use" location authorization.
 If the client app will be starting or ending Analytics sessions or logging Analytics events
 in the background and would like the device location to be updated while the app is
 in the background, this library must be configured to request "always" authorization.
 (Alternatively, the client app itself can request "always" authorization.)
 This is configured via the appropriate `OMC.plist` property.
 
 **[iOS 8 and later]** The Analytics library requests location
 updates by calling the method `-[CLLocationManager startUpdatingLocation]`, which
 requires only "when in use" authorization, unless updates are required while the client app
 is in the background.
 
 @warning **[iOS 8 and later]** If the Analytics library is configured to capture location information,
 the client app's `Info.plist` file must include the appropriate entry for prompting the user
 for location authorization; either `NSLocationWhenInUseUsageDescription` or
 `NSLocationAlwaysUsageDescription`. See the documentation for `CLLocationManager`.
 */
@interface OMCAnalytics : OMCMobileBackendServiceProxy

/**
 The analytics service's current session ID. This is `nil` if there
 is currently no analytics session.
 */
@property (readonly, nullable) NSUUID* sessionID __deprecated_msg("see OMCCxAAnalytics");

/** The analytics service's delegate. */
@property (weak) id<OMCAnalyticsDelegate> delegate __deprecated_msg("see OMCCxAAnalytics");

/**
 Determines whether sessions and events are logged.
 If this flag is set to `YES`, the following methods will do nothing:
 
 - `startSession`
 - `endSession`
 - `logEvent:`
 - `logEvent:properties:`
 
 This allows the client application to simply set this flag if
 the user wants to "opt out" of being tracked via analytics events.
 The client application code then need not check the user's preference
 with every call to the Analytics library.
  
 NB: As the value of this flag is not persisted, its value must
 be set by the client application every time the application starts.
 The client must persist the user's preference as appropriate.
 
 NB: The `flush` method ignores this flag and will still upload any
 events generated while this flag was not set. As usual, if there are
 no events, the `flush` method does nothing.
 */
@property BOOL optOut __deprecated_msg("see OMCCxAAnalytics");


/**
 Starts an OMC Analytics session. If a session is already in progress, it simply proceeds
 and a new session is NOT started.
 
 Does nothing if the `optOut` flag is set.
 */
- (void)startSession __deprecated_msg("see OMCCxAAnalytics");

/**
 Stops the current OMC Analytics session. Does nothing if a session is not in progress.
 
 Does nothing if the `optOut` flag is set.
 */
- (void)endSession __deprecated_msg("see OMCCxAAnalytics");

/**
 Logs an OMC Analytics event with the specified name. If a session is not in progress,
 starts a session. Copies the specified name before returning.
 
 Does nothing if the `optOut` flag is set.
 @param name The event name.
 */
- (void)logEvent:(NSString*)name __deprecated_msg("see OMCCxAAnalytics");

/**
 Logs an OMC Analytics event with the specified name and properties.
 If a session is not in progress, starts a session.
 Copies the specified name and properties before returning.
 
 Does nothing if the `optOut` flag is set.
 @param name The event name.
 @param properties Optional dictionary of arbitrarily named properties for the event.
 @warning Raises an `NSInvalidArgumentException` if any of the keys in `properties`
    is reserved.
 @see reservedEventPropertyNames
 */
- (void)logEvent:(NSString*)name
      properties:(NSDictionary<NSString*, NSString*>* _Nullable)properties __deprecated_msg("see OMCCxAAnalytics");

/**
 Uploads all the logged events to the OMC Mobile Analytics REST service.
 */
- (void)flush __deprecated_msg("see OMCCxAAnalytics");

/**
 Returns a set of the reserved event property names.
 */
+ (NSSet*)reservedEventPropertyNames __deprecated_msg("see OMCCxAAnalytics");


#pragma mark - App-Supplied Context Location

/**
 The analytics service's context location country. This can be `nil`.
 @see -[OMCAnalytics setContextLocationCountry:region:locality:postalCode:]
 */
@property (readonly, nullable) NSString* contextLocationCountry __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's context location region. This can be `nil`.
 @see -[OMCAnalytics setContextLocationCountry:region:locality:postalCode:]
 */
@property (readonly, nullable) NSString* contextLocationRegion __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's context location locality. This can be `nil`.
 @see -[OMCAnalytics setContextLocationCountry:region:locality:postalCode:]
 */
@property (readonly, nullable) NSString* contextLocationLocality __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's context location postal code. This can be `nil`.
 @see -[OMCAnalytics setContextLocationCountry:region:locality:postalCode:]
 */
@property (readonly, nullable) NSString* contextLocationPostalCode __deprecated_msg("see OMCCxAAnalytics");

/**
 Set the analytics service's context location country, region, locality,
 and/or postal code. Any of these settings can be `nil`.
 @param country Optional country.
 @param region Optional region.
 @param locality Optional locality.
 @param postalCode Optional postal code.
 */
- (void)setContextLocationCountry:(nullable NSString*)country
                           region:(nullable NSString*)region
                         locality:(nullable NSString*)locality
                       postalCode:(nullable NSString*)postalCode __deprecated_msg("see OMCCxAAnalytics");

@end


#pragma mark - Constants

/**
 The Analytics library's current version.
 */
extern NSString* const OMCAnalyticsVersion __deprecated_msg("see OMCCxAAnalytics");

/**
 The relative path for the Analytics Events REST endpoint.
 This is appended to the Analytics's backend's base URL
 (`analytics/events`).
 */
extern NSString* const OMCAnalyticsEventsRelativePath __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics `Oracle-Mobile-Analytics-Session-ID` HTTP header field name.
 This header must accompany any REST calls to the Custom Code service when
 the Custom Code module's Analytics events are to be included in the client's
 Analytics Session.
 */
extern NSString* const OMCAnalyticsSessionIDHTTPHeaderFieldName __deprecated_msg("see OMCCxAAnalytics");

/**
 The type of an Analytics system event (`system`).
 */
extern NSString* const OMCAnalyticsSystemEventType __deprecated_msg("see OMCCxAAnalytics");

/**
 The name of the Analytics context event (`context`).
 */
extern NSString* const OMCAnalyticsContextEventName __deprecated_msg("see OMCCxAAnalytics");

/**
 The name of the Analytics session start event (`sessionStart`).
 */
extern NSString* const OMCAnalyticsSessionStartEventName __deprecated_msg("see OMCCxAAnalytics");

/**
 The name of the Analytics session end event (`sessionEnd`).
 */
extern NSString* const OMCAnalyticsSessionEndEventName __deprecated_msg("see OMCCxAAnalytics");

/**
 The `analytics` service's properties name.
 */
extern NSString* const OMCAnalyticsPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's `dryRun` property name.
 */
extern NSString* const OMCAnalyticsDryRunPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's `dryRun` default value (`NO`).
 */
extern BOOL const OMCAnalyticsDryRunDefault __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's `location` property name.
 */
extern NSString* const OMCAnalyticsLocationPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `enabled` property name.
 */
extern NSString* const OMCAnalyticsLocationEnabledPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `enabled` default value (`YES`).
 */
extern BOOL const OMCAnalyticsLocationEnabledDefault __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `logUpdates` property name.
 */
extern NSString* const OMCAnalyticsLocationLogUpdatesPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `logUpdates` default value (`NO`).
 */
extern BOOL const OMCAnalyticsLocationLogUpdatesDefault __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `accuracy` property name.
 Specified in meters. Default is -1 (best).
 */
extern NSString* const OMCAnalyticsLocationAccuracyPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `distanceFilter` property name.
 Specified in meters. Default is -1 (none).
 */
extern NSString* const OMCAnalyticsLocationDistanceFilterPropertyName __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `activityType` property name.
 
 Supported values:
 
 - `"Other"` (default) (`OMCAnalyticsLocationActivityTypeOther`)
 - `"AutomotiveNavigation"` (`OMCAnalyticsLocationActivityTypeAutomotiveNavigation`)
 - `"Fitness"` (`OMCAnalyticsLocationActivityTypeFitness`)
 - `"OtherNavigation"` (`OMCAnalyticsLocationActivityTypeOtherNavigation`)
 
 @see CLActivityType
 */
extern NSString* const OMCAnalyticsLocationActivityTypePropertyName __deprecated_msg("see OMCCxAAnalytics");
extern NSString* const OMCAnalyticsLocationActivityTypeOther __deprecated_msg("see OMCCxAAnalytics");
extern NSString* const OMCAnalyticsLocationActivityTypeAutomotiveNavigation __deprecated_msg("see OMCCxAAnalytics");
extern NSString* const OMCAnalyticsLocationActivityTypeFitness __deprecated_msg("see OMCCxAAnalytics");
extern NSString* const OMCAnalyticsLocationActivityTypeOtherNavigation __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `authorizationRequest` property name.
 [iOS 8 and later.]
 
 Supported values:
 
 - `"WhenInUse"` (default) (`OMCAnalyticsLocationAuthorizationRequestWhenInUse`)
 - `"Always"` (`OMCAnalyticsLocationAuthorizationRequestAlways`)
 
 @see -[CLLocationManager requestWhenInUseAuthorization]
 @see -[CLLocationManager requestAlwaysAuthorization]
 */
extern NSString* const OMCAnalyticsLocationAuthorizationRequestPropertyName __deprecated_msg("see OMCCxAAnalytics");
extern NSString* const OMCAnalyticsLocationAuthorizationRequestWhenInUse __deprecated_msg("see OMCCxAAnalytics");
extern NSString* const OMCAnalyticsLocationAuthorizationRequestAlways __deprecated_msg("see OMCCxAAnalytics");

/**
 The analytics service's location `authorizationRequest` default value
 (`"WhenInUse"`).
 [iOS 8 and later.]
 */
extern NSString* const OMCAnalyticsLocationAuthorizationRequestDefault __deprecated_msg("see OMCCxAAnalytics");

/**
 The value of the `code` of the `NSError` generated when
 an unexpected status code was returned by the Analytics server.
 See the values in the `userInfo` dictionary.
 */
extern NSInteger const OMCAnalyticsPostEventsError __deprecated_msg("see OMCCxAAnalytics");

/**
 A key to the `userInfo` dictionary in the `NSError` generated when an unexpected
 response occurs when posting events to the Analytics server.
 The corresponding value is the `NSURLRequest` that generated the error.
 */
extern NSString* const OMCAnalyticsEventsPostErrorRequest __deprecated_msg("see OMCCxAAnalytics");

/**
 A key to the `userInfo` dictionary in the `NSError` generated when an unexpected
 response occurs when posting events to the Analytics server.
 The corresponding value is the `NSURL` of the event file to be POSTed by the request
 that generated the error.
 */
extern NSString* const OMCAnalyticsEventsPostErrorFileURL __deprecated_msg("see OMCCxAAnalytics");

/**
 A key to the `userInfo` dictionary in the `NSError` generated when an unexpected
 response occurs when posting events to the Analytics server.
 The corresponding value is the `NSHTTPURLResponse` returned when events were
 posted to the Analytics server.
 */
extern NSString* const OMCAnalyticsEventsPostErrorResponse __deprecated_msg("see OMCCxAAnalytics");

/**
 A key to the `userInfo` dictionary in the `NSError` generated when an unexpected
 response occurs when posting events to the Analytics server.
 The corresponding value is the `NSData` returned when events were
 posted to the Analytics server.
 */
extern NSString* const OMCAnalyticsEventsPostErrorResponseData __deprecated_msg("see OMCCxAAnalytics");

/**
 The value of the `code` of the `NSError` generated when
 the Analytics directory is a file.
 */
extern NSInteger const OMCAnalyticsDirectoryError __deprecated_msg("see OMCCxAAnalytics");

/**
 The value of the `code` of the `NSError` generated when
 the Analytics events directory is a file.
 */
extern NSInteger const OMCAnalyticsEventsDirectoryError __deprecated_msg("see OMCCxAAnalytics");

/**
 The value of the `code` of the `NSError` generated when
 the Mobile Backend Analytics events directory is a file.
 */
extern NSInteger const OMCMobileBackendAnalyticsEventsDirectoryError __deprecated_msg("see OMCCxAAnalytics");

/**
 The value of the `code` of the `NSError` generated when
 the Analytics event file is a directory.
 */
extern NSInteger const OMCAnalyticsEventFileError __deprecated_msg("see OMCCxAAnalytics");

/**
 The value of the `code` of the `NSError` generated when
 the Analytics event file does not exist.
 */
extern NSInteger const OMCAnalyticsEventFileDoesNotExistError __deprecated_msg("see OMCCxAAnalytics");

NS_ASSUME_NONNULL_END
