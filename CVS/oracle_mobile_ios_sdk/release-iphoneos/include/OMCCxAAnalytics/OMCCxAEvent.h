//
//  OMCCxAEvent.h
//  Snowplow
//
//  Copyright (c) 2015 Snowplow Analytics Ltd. All rights reserved.
//
//  This program is licensed to you under the Apache License Version 2.0,
//  and you may not use this file except in compliance with the Apache License
//  Version 2.0. You may obtain a copy of the Apache License Version 2.0 at
//  http://www.apache.org/licenses/LICENSE-2.0.
//
//  Unless required by applicable law or agreed to in writing,
//  software distributed under the Apache License Version 2.0 is distributed on
//  an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
//  express or implied. See the Apache License Version 2.0 for the specific
//  language governing permissions and limitations there under.
//
//  Authors: Joshua Beemster
//  Copyright: Copyright (c) 2015 Snowplow Analytics Ltd
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>



@class OMCCxAPayload;


// Builder Protocols : Defines all setter functions

/**
 Basic event builder.
 */

@protocol OMCCxAEventBuilder <NSObject>
/**
 Set timestamp for the event.
 @param timestamp to be set.
 */
- (void) setTimestamp:(long long)timestamp;
@end

/**
 Pageview event builder, for view of web pages.
 */

@protocol OMCCxAPageViewBuilder <OMCCxAEventBuilder>
/**
 Set PageUrl for the web page.
 @param pageUrl page url to be set.
 */
- (void) setPageUrl:(NSString *)pageUrl;
/**
 Set PageTitle for the web page.
 @param pageTitle page title to be set.
 */
- (void) setPageTitle:(NSString *)pageTitle;

/**
 Set Referrer for the page.
 @param referrer to be set.
 */
- (void) setReferrer:(NSString *)referrer;
@end

/**
 Structured event builder.
 */

@protocol OMCCxAStructuredBuilder <OMCCxAEventBuilder>
/**
Set the grouping of structured events which this action belongs to.
@param category which this action belongs to.
*/
- (void) setCategory:(NSString *)category;
/**
 Set the type of user interaction which this event involves.
 @param action Defines the type of user interaction which this event involves.
 */
- (void) setAction:(NSString *)action;
/**
 Set a string to provide additional dimensions to the event data.
 @param label a string to provide additional dimensions to the event data.
 */
- (void) setLabel:(NSString *)label;
/**
 Set a string describing the object or the action performed on it.
 @param property a string describing the object or the action performed on it.
 */
- (void) setProperty:(NSString *)property;
/**
 Set a value to provide numerical data about the event.
 @param value a value to provide numerical data about the event.
 */
- (void) setValue:(double)value;
/**
 Set a custom key value pair to the event.
 @param key key of the pair to be set.
 @param value value of the pair to be set.
 */
- (void) setCustomField:(NSString *)key andValue:(NSString *)value;
/**
 Set a map of custom key value pairs to the event.
 @param map map of the key value pairs to be set.
 */
- (void) setCustomFieldMap:(NSMutableDictionary *)map;
/**
 Set a custom key value pair attribute to the event.
 @param key key of the  attribute pair to be set.
 @param value value of the  attribute pair to be set.
 */
- (void) setCustomAttribute:(NSString *)key andValue:(NSString *)value;
/**
 Set a custom key value pair Metric to the event.
 @param key key of the metric pair to be set.
 @param value value of the metric pair to be set.
 */
- (void) setCustomMetric:(NSString *)key andValue:(NSString *)value;
@end


/**
 Screen view  event builder.
 */

@protocol OMCCxAScreenViewBuilder <OMCCxAEventBuilder>
/**
 Set Human-readable name for this screen
 @param name to be set for this screen.
 */
- (void) setName:(NSString *)name;
/**
Set unique identifier for this screen
@param sId unique identifier to be set for this screen.
*/
- (void) setId:(NSString *)sId;
@end

/**
 crash report  event builder.
 */
@protocol OMCCxACrashReportBuilder <OMCCxAEventBuilder>
/**
 Set crash data report for this screen
 @param crData crash data report to be set.
 */
- (void) setCrashData:(NSString *)crData;
@end

/**
Campaign view event builder.
*/

@protocol OMCCxACampaignViewBuilder <OMCCxAEventBuilder>
/**
 Set unique identifier for this event
 @param sId unique identifier to be set for this event.
 */
- (void) setId:(NSString *)sId;
/**
 Set unique device identifier for this event
 @param dvceId unique device identifier to be set for this event.
 */
- (void) setDvceId: (NSString *)dvceId;
@end

/**
 Campaign receive event builder.
 */

@protocol OMCCxACampaignReceiveBuilder <OMCCxAEventBuilder>
/**
 Set unique identifier for this event
 @param sId unique identifier to be set for this event.
 */
- (void) setId:(NSString *)sId;

/**
 Set unique device identifier for this event
 @param dvceId unique device identifier to be set for this event.
 */
- (void) setDvceId: (NSString *)dvceId;
@end

/**
 Ecommerce transaction event builder.
 */

@protocol OMCCxAEcommTransactionBuilder <OMCCxAEventBuilder>
/**
 Set ID of the eCommerce transaction.
 @param orderId ID of the eCommerce transaction.
 */
- (void) setOrderId:(NSString *)orderId;
/**
 Set total transaction value.
 @param  totalValue total transaction value.
 */
- (void) setTotalValue:(double)totalValue;
/**
 Set  transaction affiliation.
 @param  affiliation  transaction affiliation.
 */
- (void) setAffiliation:(NSString *)affiliation;
/**
Set  transaction tax value
@param  taxValue  transaction tax value
*/
- (void) setTaxValue:(double)taxValue;
/**
 Set  delivery cost charged.
 @param  shipping delivery cost charged.
 */
- (void) setShipping:(double)shipping;
/**
 Set  delivery city.
 @param  city   delivery city
 */
- (void) setCity:(NSString *)city;
/**
 Set  delivery state.
 @param  state  delivery state.
 */
- (void) setState:(NSString *)state;
/**
 Set  delivery country.
 @param   country delivery  country.
 */
- (void) setCountry:(NSString *)country;
/**
 Set  transaction currency.
 @param  currency set transaction currency.
 */
- (void) setCurrency:(NSString *)currency;
/**
Set  items in the transaction.
@param  items in the transaction.
*/
- (void) setItems:(NSArray *)items;
@end


/**
 Ecommerce transaction item event builder.
 */
@protocol OMCCxAEcommTransactionItemBuilder <OMCCxAEventBuilder>
/**
 Set ID of the eCommerce transaction.
 @param itemId ID of the eCommerce transaction, it will be automatically set via connect/add this item to the transaction.
 */
- (void) setItemId:(NSString *)itemId;
/**
 Set Item SKU.
 @param sku item SKU.
 */
- (void) setSku:(NSString *)sku;
/**
 Set Item price.
 @param price item price.
 */
- (void) setPrice:(double)price;
/**
 Set Item quantity.
 @param quantity item quantity.
 */
- (void) setQuantity:(NSInteger)quantity;
/**
 Set Item name.
 @param name item name.
 */
- (void) setName:(NSString *)name;
/**
 Set Item category.
 @param category item category.
 */
- (void) setCategory:(NSString *)category;
/**
 Set transaction currency.
 @param currency transaction currency.
 */
- (void) setCurrency:(NSString *)currency;
@end

/**
 Basic event builder.
 */

@interface OMCCxAEvent : NSObject <OMCCxAEventBuilder>

/**
 time stamp of the event
 */
@property (nonatomic, readwrite) long long timestamp;
/**
 context of the event
 */
@property (nonatomic, readwrite, retain) NSMutableArray* contexts;
/**
 Id of the event
 */
@property (nonatomic, readwrite, retain) NSString * eventId;
/**
 Get context of the event
 @return context of the event.
 */
- (NSMutableArray *) getContexts;
/**
 Get time stamp of the event
 @return time stamp of the event.
 */
- (long long) getTimestamp;
/**
Get id of the event
@return id of the event.
*/
- (NSString *) getEventId;
/**
 add the default params to the event payload.
 @param pb payload to be added
 @return payload of the event.
 */
- (OMCCxAPayload *) addDefaultParamsToPayload:(OMCCxAPayload *)pb;
@end

/**
PageView event.
 */

@interface OMCCxAPageView : OMCCxAEvent <OMCCxAPageViewBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxAPageViewBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
@end
/**
 Structured Event
*/
@interface OMCCxAStructured : OMCCxAEvent <OMCCxAStructuredBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxAStructuredBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
/**
 Get custom field of the event.
 @return custom field of the event.
 */
- (NSDictionary *) getCustomFields;
@end


/** 
 ScreenView Event
 */

@interface OMCCxAScreenView : OMCCxAEvent <OMCCxAScreenViewBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxAScreenViewBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
@end

/**
 Crash Report Event
*/
@interface OMCCxACrashReport : OMCCxAEvent <OMCCxACrashReportBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxACrashReportBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
@end

/**
 CampaignView Event
 */

@interface OMCCxACampaignView : OMCCxAEvent <OMCCxACampaignViewBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxACampaignViewBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
@end
/**
 CampaignReceive Event
 */

@interface OMCCxACampaignReceive : OMCCxAEvent <OMCCxACampaignReceiveBuilder>
/**
 event builder
 
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxACampaignReceiveBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
@end



/**
 Ecommerce Event
 */

@interface OMCCxAEcommerce : OMCCxAEvent <OMCCxAEcommTransactionBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxAEcommTransactionBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
/**
 Get items of the  Ecommerce Event.
 @return an array of Ecommerce transaction items.
 */
- (NSArray *) getItems;
@end


/**
 Ecommerce Item Event
 */

@interface OMCCxAEcommerceItem : OMCCxAEvent <OMCCxAEcommTransactionItemBuilder>
/**
 event builder
 @param buildBlock buildBlock of the event
 @return instancetype of the event.
 */
+ (instancetype) build:(void(^)(id<OMCCxAEcommTransactionItemBuilder>builder))buildBlock;
/**
 Get payload of the event.
 @return payload of the event.
 */
- (OMCCxAPayload *) getPayload;
@end
