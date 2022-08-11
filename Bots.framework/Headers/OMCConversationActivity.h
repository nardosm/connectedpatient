//
//  OMCConversationActivity.h
//  Bots
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @abstract An activity type indicating that the appMaker started typing a response
 */
extern NSString const *OMCConversationActivityTypeTypingStart;

/**
 *  @abstract An activity type indicating that the appMaker stopped typing a response
 */
extern NSString const *OMCConversationActivityTypeTypingStop;

/**
 *  @abstract An activity type indicating that the appMaker recently read the user message
 */
extern NSString const *OMCConversationActivityTypeConversationRead;

/**
 *  @abstract A key whose value is an NSString representing the appMaker name.
 *
 *  @discussion This key is used in the OMCConversationActivity data object.
 */
extern NSString const *OMCConversationActivityDataNameKey;

/**
 *  @abstract A key whose value is an NSString representing the URL of the appMaker avatar.
 *
 *  @discussion This key is used in the OMCConversationActivity data object.
 */
extern NSString const *OMCConversationActivityDataAvatarUrlKey;

@interface OMCConversationActivity : NSObject

/**
 *  @abstract the role of who is performing the typing activity
 */
@property(readonly) NSString *role;

/**
 *  @abstract the type of activity that is being triggered. Could be either OMCConversationActivityTypeTypingStart, OMCConversationActivityTypeTypingStop or OMCConversationActivityTypeConversationRead
 */
@property(readonly) NSString *type;

/**
 *  @abstract additional data for this activity. Posible values are the appMaker's 'name' and/or 'avatarUrl'
 */
@property(readonly, nullable) NSDictionary *data;

/**
 *  @abstract date when the appMaker last read user messages for activities of type OMCConversationActivityTypeConversationRead
 */
@property(readonly, nullable) NSDate *appMakerLastRead;

@end
NS_ASSUME_NONNULL_END
