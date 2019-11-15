//
//  SimilityRecon.h
//  SimilityRecon
//
//  Created by Anupam on 20/01/17.
//  Copyright © 2017 Simility. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^WorkerScriptDebugHandler)(NSString *, BOOL, NSError *);
typedef void (^ScriptStatusCallbackHandler)(NSDictionary *);
typedef void (^ScriptCompletionHandler)(NSDictionary *);

@interface SimilityTouchEvent : NSObject

@property (readonly) NSTimeInterval timestamp;
@property (readonly) UITouchPhase phase;
@property (readonly) CGPoint location;
@property (readonly) CGFloat force;
@property (readonly) NSString *json;

- (id) initWithTouchData:(NSTimeInterval) timestamp phase:(UITouchPhase) phase location:(CGPoint) location force:(CGFloat) force;

@end

@interface SimilityContext : NSObject

@property NSString *customerId;
@property NSString *sessionId;
@property NSString *userId;
@property NSDictionary *metadata;
@property NSString *zone;
@property NSString *requestEndpoint;
@property NSString *eventTypes;
@property NSString *transactionSubCustomerId;
@property NSString *transactionInfo;
@property NSMutableArray *transactionEntries;
@property NSString *collectOptions;
@property NSString *cmid;
@property NSDictionary *magnesDeviceInfo;
@property NSMutableArray *touchEvents;
@property BOOL similityLite;
@property BOOL hashConfidentialData;
@property NSTimeInterval startTimestamp;
@property (readonly) long statusCallbackTimeoutInMS;
@property (readonly) BOOL statusCallbackDone;
@property ScriptStatusCallbackHandler scriptStatusCallbackHandler;

- (void) addTransactionEntry:(NSString *) entity id:(NSString *) id fields:(NSDictionary *) fields;
- (void) setScriptStatusCallbackHandlerWithTimeout:(ScriptStatusCallbackHandler)scriptStatusCallbackHandler statusCallbackTimeoutInMS:(long) statusCallbackTimeoutInMS;
@end

@interface SimilityScript : NSObject

+ (SimilityScript *) sharedInstance;
- (void) getDeviceId:(SimilityContext *) similityContext scriptCompletionHandler:(ScriptCompletionHandler) scriptCompletionHandler;
- (void) execute:(SimilityContext *) similityContext;
- (void) execute:(SimilityContext *) similityContext scriptCompletionHandler:(ScriptCompletionHandler) scriptCompletionHandler;

+ (NSString *) getSessionId;
+ (NSString *) resetSessionId;

@end
