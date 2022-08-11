//
//  OMCMessageAction.h
//  Bots
//

#import <Foundation/Foundation.h>

/**
 *  @abstract Type for a link action.
 */
extern NSString* _Nonnull const OMCMessageActionTypeLink;

/**
 *  @abstract Type for a webview action.
 */
extern NSString* _Nonnull const OMCMessageActionTypeWebview;

/**
 *  @abstract Type for a buy action.
 */
extern NSString* _Nonnull const OMCMessageActionTypeBuy;

/**
 *  @abstract Type for a postback action.
 */
extern NSString* _Nonnull const OMCMessageActionTypePostback;

/**
 *  @abstract Type for a reply action
 */
extern NSString* _Nonnull const OMCMessageActionTypeReply;

/**
 *  @abstract Type for a location request
 */
extern NSString* _Nonnull const OMCMessageActionTypeLocationRequest;

/**
 *  @abstract Offered state for a buy message. The user has not yet completed the transaction.
 */
extern NSString* _Nonnull const OMCMessageActionStateOffered;

/**
 *  @abstract Paid state for a buy message. The user has completed the transaction and payment was successful.
 */
extern NSString* _Nonnull const OMCMessageActionStatePaid;

/**
 *  @abstract A full-sized webview
 */
extern NSString* _Nonnull const OMCMessageActionWebviewSizeFull;

/**
 *  @abstract A tall-sized webview
 */
extern NSString* _Nonnull const OMCMessageActionWebviewSizeTall;

/**
 *  @abstract A compact-sized webview
 */
extern NSString* _Nonnull const OMCMessageActionWebviewSizeCompact;

/**
 *  @abstract An action associated to a particular OMCMessage.
 *
 *  Actions are rendered as buttons in the Bots conversation screen, and may be of type `OMCMessageActionTypeLink`, `OMCMessageActionTypeBuy` or `OMCMessageActionTypePostback`.
 *
 *  @see OMCMessage
 */
@interface OMCMessageAction : NSObject

/**
 *  @abstract The unique identifier representing the action.
 */
@property(readonly, nullable) NSString* actionId;

/**
 *  @abstract The type of action.
 *
 *  @discussion Valid types include `OMCMessageActionTypeLink` for regular actions, and `OMCMessageActionTypeBuy` for buy actions.
 */
@property(nullable) NSString* type;

/**
 *  @abstract The text to display as a descriptor for the action.
 *
 *  @discussion May not be nil.
 */
@property(nullable) NSString* text;

/**
 *  @abstract The URI to navigate to if the user interacts with the action.
 *
 *  @discussion May not be nil if message is of type `OMCMessageActionTypeLink` or `OMCMessageActionTypeWebview`
 */
@property(nullable) NSURL* uri;

/**
 *  @abstract Fallback URI to use for action types not supported by the SDK. May be nil.
 */
@property(nullable) NSURL* fallback;

/**
 *  @abstract The size of a webview
 *
 *  @discussion May not be nil if message is of type `OMCMessageActionTypeWebview`
 */
@property(nullable, copy) NSString* size;

/**
 *  @abstract Boolean value indicating whether this action is the default action for an OMCMessageItem
 *
 *  @discussion Default value is `NO`
 *
 *  @see OMCMessageItem
 */
@property(readonly) BOOL isDefault;

/**
 *  @abstract Metadata associated with the action.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

/**
 *  @abstract Icon to display with a reply
 *
 *  @discussion An icon to render next to the reply option
 */
@property(nullable) NSString* iconUrl;

/**
 *  @abstract The payload of actions with type OMCMessageActionTypeReply or OMCMessageActionTypePostback
 *
 *  @discussion The payload of actions with type OMCMessageActionTypeReply or OMCMessageActionTypePostback, if applicable. May be nil
 */
@property(nullable) NSString* payload;

#pragma mark - Buy actions

/**
 *  @abstract The purchase state of the action
 *
 *  @discussion This property is only non-nil for actions of type `OMCMessageActionTypeBuy`. Valid states include `OMCMessageActionStateOffered` and `OMCMessageActionStatePaid`.
 */
@property(nullable) NSString* state;

/**
 *  @abstract The amount of money to charge for the action.
 *
 *  @discussion This property is only valid for actions of type `OMCMessageActionTypeBuy`. For USD, this value is in cents.
 */
@property long amount;

/**
 *  @abstract The currency in which the `amount` is expressed.
 *
 *  @discussion This property is only valid for actions of type `OMCMessageActionTypeBuy`.
 */
@property(nullable) NSString* currency;

@end
