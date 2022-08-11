//
//  OMCConversation.h
//  Bots
//

#import <Foundation/Foundation.h>
#import "OMCMessage.h"
#import "OMCMessageAction.h"
#import "OMCMessageItem.h"
#import "OMCConversationActivity.h"

NS_ASSUME_NONNULL_BEGIN
@protocol OMCConversationDelegate;

typedef void (^OMCImageUploadProgressBlock)(double progress);
typedef void (^OMCImageUploadCompletionBlock)(NSError* _Nullable error, OMCMessage* _Nullable message);
typedef void (^OMCFileUploadProgressBlock)(double progress);
typedef void (^OMCFileUploadCompletionBlock)(NSError* _Nullable error, OMCMessage* _Nullable message);

/**
 *  @discussion Represents various actions the user takes when interacting with Bots UI components.
 */
typedef NS_ENUM(NSInteger, OMCAction) {
    /**
     *  The user has tapped on a Bots in-app notification.
     */
    OMCActionInAppNotificationTapped,
    /**
     *  The user has tapped on a Bots push notification.
     */
    OMCActionPushNotificationTapped
};

/**
 *  @abstract Posted when the count of unread messages changes. The notification object will be an instance of OMCConversation, of which you can then inspect the messageCount property.
 *
 *  @see OMCConversation
 */
extern NSString* const OMCConversationUnreadCountDidChangeNotification;

/**
 *  @abstract Posted when an image upload begins.
 *
 *  @discussion The userInfo dictionary contains the UIImage to upload. Use OMCConversationImageKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see OMCConversationImageKey
 */
extern NSString* const OMCConversationImageUploadDidStartNotification;

/**
 *  @abstract Posted when an image upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the UIImage being uploaded, as well as an NSNumber reflecting the current progress. Use OMCConversationImageKey and OMCConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see OMCConversationImageKey
 *  @see OMCConversationProgressKey
 */
extern NSString* const OMCConversationImageUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when an image upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the UIImage that was uploaded. Use OMCConversationImageKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the OMCMessage instance of the new message. Use OMCConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use OMCConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see OMCMessage
 *  @see OMCConversationImageKey
 *  @see OMCConversationMessageKey
 *  @see OMCConversationErrorKey
 */
extern NSString* const OMCConversationImageUploadCompletedNotification;

/**
 *  @abstract Posted when a file upload begins.
 *
 *  @discussion The userInfo dictionary contains the url of the file to upload. Use OMCConversationFileKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see OMCConversationFileKey
 */
extern NSString* const OMCConversationFileUploadDidStartNotification;

/**
 *  @abstract Posted when a file upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the url of the file being uploaded, as well as an NSNumber reflecting the current progress. Use OMCConversationFileKey and OMCConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see OMCConversationFileKey
 *  @see OMCConversationProgressKey
 */
extern NSString* const OMCConversationFileUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when a file upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the url of the file that was uploaded. Use OMCConversationFileKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the OMCMessage instance of the new message. Use OMCConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use OMCConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see OMCMessage
 *  @see OMCConversationFileKey
 *  @see OMCConversationMessageKey
 *  @see OMCConversationErrorKey
 */
extern NSString* const OMCConversationFileUploadCompletedNotification;

/**
 *  @abstract Posted when new messages are received from the server.
 *
 *  @discussion The userInfo dictionary contains an NSArray of OMCMessage objects. Use OMCConversationNewMessagesKey to access this value.
 *
 *  @see OMCMessage
 *  @see OMCConversationNewMessagesKey
 */
extern NSString* const OMCConversationDidReceiveMessagesNotification;

/**
 *  @abstract Posted when an operation to load previous messages in a conversation has been completed
 *
 *  @discussion This notification is posted as the result of [OMCConversation loadPreviousMessages]
 *
 *  If the operation succeeded, the object returned by this notification will include the updated array of messages
 *  If the operation failed, the userInfo dictionary will contain an "error" object with the response error
 *
 *  @see OMCMessage
 *  @see OMCConversationPreviousMessagesKey
 */
extern NSString* const OMCConversationDidReceivePreviousMessagesNotification;

/**
 *  @abstract Posted when a conversation activity has been created, such as typing start/stop
 *
 *  @see OMCConversationActivity
 *  @see OMCConversationActivityKey
 */
extern NSString* const OMCConversationDidReceiveActivityNotification;

/**
 *  @abstract A key whose value is an NSArray of OMCMessage objects.
 *
 *  @discussion This key is used with OMCConversationDidReceiveMessagesNotification notification.
 *
 *  @see OMCConversationDidReceiveMessagesNotification
 */
extern NSString* const OMCConversationNewMessagesKey;

/**
 *  @abstract A key whose value is an NSArray of OMCMessage objects
 *
 *  @discussion This key is used with OMCConversationDidReceivePreviousMessagesNotification notification
 *
 *  @see OMCConversationDidReceivePreviousMessagesNotification
 */
extern NSString* const OMCConversationPreviousMessagesKey;

/**
 *  @abstract A key whose value is a UIImage which represents an image being uploaded.
 *
 *  @discussion This key is used with OMCConversationImageUploadDidStartNotification, OMCConversationImageUploadProgressDidChangeNotification, and OMCConversationImageUploadCompletedNotification notifications.
 *
 *  @see OMCConversationImageUploadDidStartNotification
 *  @see OMCConversationImageUploadProgressDidChangeNotification
 *  @see OMCConversationImageUploadCompletedNotification
 */
extern NSString* const OMCConversationImageKey;

/**
 *  @abstract A key whose value is an NSURL which represents a file being uploaded.
 *
 *  @discussion This key is used with OMCConversationFileUploadDidStartNotification, OMCConversationFileUploadProgressDidChangeNotification, and OMCConversationFileUploadCompletedNotification notifications.
 *
 *  @see OMCConversationFileUploadDidStartNotification
 *  @see OMCConversationFileUploadProgressDidChangeNotification
 *  @see OMCConversationFileUploadCompletedNotification
 */
extern NSString* const OMCConversationFileKey;

/**
 *  @abstract A key whose value is an NSError.
 *
 *  @discussion This key is used with OMCConversationImageUploadCompletedNotification notification.
 *
 *  @see OMCConversationImageUploadCompletedNotification
 */
extern NSString* const OMCConversationErrorKey;

/**
 *  @abstract A key whose value is an OMCMessage object representing the newly created message.
 *
 *  @discussion This key is used with OMCConversationImageUploadCompletedNotification notification.
 *
 *  @see OMCConversationImageUploadCompletedNotification
 */
extern NSString* const OMCConversationMessageKey;

/**
 *  @abstract A key whose value is an NSNumber reflecting the current progress of an image upload.
 *
 *  @discussion This key is used with OMCConversationImageUploadProgressDidChangeNotification notification.
 *
 *  @see OMCConversationImageUploadProgressDidChangeNotification
 */
extern NSString* const OMCConversationProgressKey;

/**
 *  @abstract A key whose value is a OMCConversationActivity object representing the newly created activity
 *
 *  @discussion This key is used with OMCConversationDidReceiveActivityNotification notification.
 *
 *  @see OMCConversationDidReceiveActivityNotification
 */
extern NSString* const OMCConversationActivityKey;

/**
 *  @discussion The OMCConversation class provides an interface to interact with the current user's conversation.
 *
 *  To obtain an instance, use `[Bots conversation]`. +initWithSettings:completionHandler: must have been called prior to retrieving the shared conversation object.
 *
 *  To send a message, use -sendMessage: with an OMCMessage object
 *
 *  Example:
 *
 *  `[[Bots conversation] sendMessage:[[OMCMessage alloc] initWithText:@"Hello World!"]];`
 *
 *  A notification will be fired indicating the success or failure of the message. To subscribe to these notifications, use NSNotificationCenter.
 *
 *  Example:
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageUploaded:) name:OMCMessageUploadCompletedNotification object:nil];`
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageFailed:) name:OMCMessageUploadFailedNotification object:nil];`
 *
 *  @see OMCMessage
 *  @see Bots
 */
@interface OMCConversation : NSObject

/**
 *  @abstract The array of OMCMessage objects representing the conversation.
 *
 *  @see OMCMessage
 */
@property(readonly, nullable) NSArray* messages;

/**
 *  @abstract The total number of messages in the conversation, including user-generated messages.
 */
@property(readonly) NSUInteger messageCount;

/**
 *  @abstract Count of unread messages in the conversation.
 *
 *  @discussion The primary use of this property is to be able to display an indicator / badge when the conversation has unread messages.
 */
@property(readonly) NSUInteger unreadCount;

/**
 *  @abstract Date when the business last read the user messages
 */
@property(readonly) NSDate *appMakerLastRead;

/**
 *  @abstract A delegate object for receiving notifications related to the conversation.
 *
 *  @see OMCConversationDelegate
 */
@property(weak, nullable) id<OMCConversationDelegate> delegate;


/**
 *  @abstract Boolean representing whether there are previous messages in the conversation that can be fetched or not
 *
 *  @discussion Returns YES if there are previous messages in the conversation, NO otherwise. For fetching previous messages, use [OMCConversation loadPreviousMessages]
 */
@property(readonly) BOOL hasPreviousMessages;

/**
 *  @abstract Marks all unread messages as read.
 *
 *  @discussion Marks all unread messages as read, and notifies that the unread count changed.
 *
 *  @see OMCMessage
 */
-(void)markAllAsRead;

/**
 *  @abstract Loads previous messages for this conversation, if any
 *
 *  @dicussion Will get previous messages for this conversation based on the timestamp of the current oldest message and will notify the delegate of new incoming messages through [OMCConversationDelegate conversation:didReceivePreviousMessages:]
 */
-(void)loadPreviousMessages;

/**
 *  @abstract Adds a new message to the conversation.
 *
 *  @discussion For each message added using `sendMessage`, a notification will be fired indicating the success or failure status of the upload.
 *
 *  @see OMCMessageUploadFailedNotification
 *  @see OMCMessageUploadCompletedNotification
 */
-(void)sendMessage:(OMCMessage*)message;

/**
 *  @abstract Adds an image message to the conversation.
 *
 *  @discussion Use the progress block to track the progress of the upload. Progress is reported as a number between 0 and 1.
 *
 *  The completion block is called when the operation completes, either in success or failure. Both blocks are guaranteed to be called on the main thread.
 *
 *  In case of success, the error parameter will be nil, and the message parameter will contain the newly created message. The message will already be part of the messages array when this block is called.
 *
 *  In case of failure, the message parameter will be nil, and the error parameter will contain the error that occurred.
 *
 *  @param image The image to upload. Must not be nil.
 *  @param progressBlock Called to report progress updates. May be nil.
 *  @param completionBlock Called when the upload completes or fails. May be nil.
 */
-(void)sendImage:(UIImage *)image withProgress:(nullable OMCImageUploadProgressBlock)progressBlock completion:(nullable OMCImageUploadCompletionBlock)completionBlock;

-(void)sendFile:(NSURL *)fileLocation withProgress:(nullable OMCFileUploadProgressBlock)progressBlock completion:(nullable OMCFileUploadCompletionBlock)completionBlock;

/**
 *  @abstract Sends a postback to the server.
 *
 *  @discussion The completion block is called when the operation completes, either in success or failure.
 *
 *  In case of success, the error parameter will be nil.
 *
 *  In case of failure, the error parameter will contain the error that occurred.
 *
 *  @param messageAction The messageAction for which to send the postback. Must not be nil.
 *  @param completionBlock Called when the postback completes or fails. May be nil.
 */
-(void)postback:(OMCMessageAction*)messageAction completion:(nullable void (^)(NSError* _Nullable error))completionBlock;

/**
 *  @abstract Retries a message that failed to send.
 *
 *  @discussion The failed message will be removed from the messages array, and a new message will be constructed with the same text as the failed message. A notification will be fired indicating the success or failure status of the upload.
 *
 *  @see OMCMessageUploadFailedNotification
 *  @see OMCMessageUploadCompletedNotification
 */
-(void)retryMessage:(OMCMessage*)failedMessage;

/**
 *  @abstract Notify the server that the user is typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  Typing updates are automatically throttled, so you may call this method as often as necessary. The typing stop event will automatically fire 10 seconds after the most recent call to this method.
 */
-(void)startTyping;

/**
 *  @abstract Notify the server that the user has finished typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  If the user was not flagged as typing recently, this method will result in a no-op.
 */
-(void)stopTyping;

@end

/**
 *  @discussion Delegate protocol for events related to the conversation.
 *
 *  Creating a delegate is optional, and may be used to receive callbacks when important changes happen in the conversation.
 *
 *  Delegate methods are guaranteed to be called from the main thread.
 */
@protocol OMCConversationDelegate <NSObject>

@optional
/**
 *  @abstract Notifies the delegate of a change in unread message count.
 *
 *  @discussion Called when conversation data is fetched from the server, or when the user enters the conversation screen.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param unreadCount The new number of unread messages.
 */
-(void)conversation:(OMCConversation*)conversation unreadCountDidChange:(NSUInteger)unreadCount;

/**
 *  @abstract Asks the delegate if an in-app notification should be shown for a message.
 *
 *  @discussion Called when a new message is received, right before the in-app notification is to be shown for that message. To show your own in-app notification, return NO from this method, and use the OMCMessage object to construct your view.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param message The message that will be displayed in the notification.
 *
 *  @return YES to allow Bots to present the notification. NO to suppress the notification, and perform custom handling.
 *
 *  @see OMCMessage
 */
-(BOOL)conversation:(OMCConversation*)conversation shouldShowInAppNotificationForMessage:(OMCMessage*)message;

/**
 *  @abstract Asks the delegate if the conversation should show for the given action.
 *
 *  @discussion Called when the user performs an action that causes the conversation screen to show. Return NO to cancel the display of the conversation screen and perform your own handling of the action.
 *
 *  @param conversation The conversation object.
 *  @param action The action the user has taken.
 *  @param info An instance of NSDictionary with a `message` object with the latest OMCMessage represented as an NSDictionary
 *
 *  @return YES to allow default handling. NO to suppress the conversation screen, and perform custom handling.
 *
 *  @see OMCAction
 */
-(BOOL)conversation:(OMCConversation*)conversation shouldShowForAction:(OMCAction)action withInfo:(nullable NSDictionary *) info;

/**
 *  @abstract Gives the delegate the option to modify a message before it is sent
 *
 *  @discussion Called when a message is about to be sent to give the delegate the option of modify or decorate its content (i.e. add metadata) before sending to Bots
 *
 *  @return the message to be sent
 */
-(OMCMessage *)conversation:(OMCConversation*)conversation willSendMessage:(OMCMessage *)message;

/**
 *  @abstract Gives the delegate the option to modify a message before it is displayed. If nil is returned the message will be hidden
 *
 *  @discussion Called when a message is about to be displayed to the user to give the delegate the option of modifying its content before display or hide it
 *
 *  @return the message to be displayed. If nil, the message won't get displayed
 */
-(nullable OMCMessage *)conversation:(OMCConversation*)conversation willDisplayMessage:(OMCMessage *)message;

/**
 *  @abstract Notifies the delegate of new incoming messages.
 *
 *  @discussion Called when new messages are received from the server.
 *
 *  @param conversation The conversation object.
 *  @param messages An array of OMCMessage objects representing the new messages.
 *
 *  @see OMCMessage
 */
-(void)conversation:(OMCConversation*)conversation didReceiveMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate when older messages in the conversation history have been received
 *
 *  @dicussion Called when older messages in the conversation history are received from the server
 *
 *  @param conversation The conversation object
 *  @param messages The messages that have been fetched
 */
-(void)conversation:(OMCConversation*)conversation didReceivePreviousMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate of new conversation activity
 *
 *  @dicussion Called when a new activity is received from the server
 *
 *  @param conversation The conversation object
 *  @param activity The activity that was received
 */
-(void)conversation:(OMCConversation *)conversation didReceiveActivity:(OMCConversationActivity *)activity;

/**
 *  @abstract Asks the delegate if default handling should be performed for a message action.
 *
 *  @discussion Called when the user taps a message action.
 *
 *  @return YES to allow default handling. NO to perform custom handling.
 */
-(BOOL)conversation:(OMCConversation *)conversation shouldHandleMessageAction:(OMCMessageAction*)action;

/**
 *  @abstract Notifies the delegate when the conversation is about to be presented.
 *
 *  @discussion Called in the viewWillAppear: method of the conversation view controller.
 */
-(void)conversation:(OMCConversation *)conversation willShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when presentation of the conversation completes.
 *
 *  @discussion Called in the viewDidAppear: method of the conversation view controller.
 */
-(void)conversation:(OMCConversation *)conversation didShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when the conversation is about to be dismissed.
 *
 *  @discussion Called in the viewWillDisappear: method of the conversation view controller.
 */
-(void)conversation:(OMCConversation *)conversation willDismissViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when dismissal of the conversation completes.
 *
 *  @discussion Called in the viewDidDisappear: method of the conversation view controller.
 */
-(void)conversation:(OMCConversation *)conversation didDismissViewController:(UIViewController*)viewController;

@end
NS_ASSUME_NONNULL_END
