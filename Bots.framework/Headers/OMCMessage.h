//
//  OMCMessage.h
//  Bots
//

#import <UIKit/UIKit.h>
#import "OMCCoordinates.h"
#import "OMCDisplaySettings.h"

/**
 *  @abstract Notification that is fired when a message fails to upload.
 */
extern NSString* _Nonnull const OMCMessageUploadFailedNotification;

/**
 *  @abstract Notification that is fired when a message uploads successfully.
 */
extern NSString* _Nonnull const OMCMessageUploadCompletedNotification;

/**
 *  @abstract A type of message that contains an image, text, and/or action buttons
 */
extern NSString* _Nonnull const OMCMessageTypeImage;

/**
 *  @abstract A type of message that contains text and/or action buttons
 */
extern NSString* _Nonnull const OMCMessageTypeText;

/**
 *  @abstract A type of message that contains a location
 */
extern NSString* _Nonnull const OMCMessageTypeLocation;

/**
 *  @abstract A type of message that contains a file and/or text
 */
extern NSString* _Nonnull const OMCMessageTypeFile;

/**
 *  @abstract A type of message that contains a horizontally scrollable set of items
 */
extern NSString* _Nonnull const OMCMessageTypeCarousel;

/**
 *  @abstract A type of message that contains a vertically scrollable set of items
 */
extern NSString* _Nonnull const OMCMessageTypeList;

/**
 *  @discussion Upload status of an OMCMessage.
 *
 *  @see OMCMessage
 */
typedef NS_ENUM(NSInteger, OMCMessageUploadStatus) {
    /**
     *  A user message that has not yet finished uploading.
     */
    OMCMessageUploadStatusUnsent,
    /**
     *  A user message that failed to upload.
     */
    OMCMessageUploadStatusFailed,
    /**
     *  A user message that was successfully uploaded.
     */
    OMCMessageUploadStatusSent,
    /**
     *  A message that did not originate from the current user.
     */
    OMCMessageUploadStatusNotUserMessage
};

@interface OMCMessage : NSObject

/**
 *  @abstract Create a message with the given text. The message will be owned by the current user.
 */
-(nonnull instancetype)initWithText:(nonnull NSString*)text;

/**
 *  @abstract Create a message with the given text, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithText:(nonnull NSString *)text payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract Create a message with the given coordinates, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithCoordinates:(nonnull OMCCoordinates *)coordinates payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract The unique identifier of the message. May be nil if a unique identifier has not been generated for this message
 */
@property(readonly, nullable) NSString* messageId;

/**
 *  @abstract The text content of the message. May be nil if mediaUrl or actions are provided
 */
@property(nullable) NSString* text;

/**
 *  @abstract The text fallback to display for message types not supported by the SDK. May be nil
 */
@property(nullable) NSString* textFallback;

/**
 *  @abstract The name of the author. This property may be nil if no name could be determined.
 */
@property(nullable) NSString* name;

/**
 *  @abstract The url for the author's avatar image. May be nil
 */
@property(nullable) NSString* avatarUrl;

/**
 *  @abstract The date and time the message was sent
 */
@property(nullable) NSDate *date;

/**
 *  @abstract Returns YES if the message originated from the user, or NO if the message comes from the app team.
 */
@property(readonly) BOOL isFromCurrentUser;

/**
 *  @abstract The upload status of the message.
 *
 *  @see OMCMessageStatus
 */
@property(readonly) OMCMessageUploadStatus uploadStatus;

/**
 *  @abstract An array of OMCMessageAction objects representing the actions associated with this message (if any)
 *
 *  @discussion This array may be nil or empty, so check the length of the array to know if a message has actions or not.
 *
 *  @see OMCMessageAction
 */
@property(readonly, nullable) NSArray* actions;

/**
 *  @abstract An array of OMCMessageItem objects representing the items associated with this message
 *
 *  @discussion Only messages of type `OMCMessageTypeCarousel` and `OMCMessageTypeList` contain items.
 *
 *  @see OMCMessageItem
 */
@property(readonly, nullable) NSArray* items;

/**
 *  @abstract The url to the media asset, if applicable. Returns nil if the message is not an image or file message.
 */
@property(nullable) NSString* mediaUrl;

/**
 *  @abstract The size of the media asset in bytes. May be nil.
 */
@property(nullable) NSNumber* mediaSize;

/**
 *  @abstract The type the message.
 *
 *  @discussion Valid types include OMCMessageTypeText, OMCMessageTypeImage, and OMCMessageTypeLocation
 */
@property(nullable) NSString* type;

/**
 *  @abstract Coordinates for a location for a message of type OMCMessageTypeLocation
 */
@property(readonly, nullable) OMCCoordinates *coordinates;

/**
 *  @abstract Settings to adjust the layout of a message of type OMCMessageTypeCarousel
 *
 *  @see OMCDisplaySettings
 */
@property(readonly, nullable) OMCDisplaySettings *displaySettings;

/**
 *  @abstract The role of the message.
 *
 *  @discussion Valid roles include `appUser`, `appMaker`, and `whisper`. Messages created with -initWithText: have role of `appUser`.
 */
@property(readonly, nullable) NSString* role;

/**
 *  @abstract Metadata associated with the message.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

/**
 *  @abstract The payload of an action with type OMCMessageActionTypeReply
 *
 *  @discussion The payload of a OMCMessageActionTypeReply, if applicable. May be nil
 */
@property(nullable) NSString* payload;

@end
