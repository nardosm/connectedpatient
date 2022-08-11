//
//  Engagement.h
//  Engagement
//
//  Copyright © 2016 Oracle. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Engagement SDK for CxA is use for registerting device for notifications and handling campaigns.
 */
@interface OMCCxAEngagement : NSObject

/**
 Auto register for APNS and if successfully retrieved the device token from APNS, this method will also auto register the token to MIECS server.
 This method must be called from appDelegate's didFinishLaunchingWithOptions: method.
 @param launchOptions required to get push notification information
 */
+ (void) startEngagement:(NSDictionary *) launchOptions;


/**
 Returns current status of device token registration with CxA server for Push Notifications.
 @return boolean registration status
 */
+ (BOOL) isRegistered;


@end
