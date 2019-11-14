#import <Cordova/CDVPlugin.h>
#import "SimilityRecon.h"
#import "DeviceRecon.h"

@implementation DeviceRecon

- (void)signal:(CDVInvokedUrlCommand*)command
{
    NSString *signal = [command.arguments objectAtIndex:0];
    CDVPluginResult* pluginResult = nil;
    
    NSString *customerId, *sessionId, *userId;

    customerId = [signal valueForKey:@"customer_id"];
    sessionId = [signal valueForKey:@"session_id"];
            
    if ([signal valueForKey:@"user_id"] != nil) {
        userId = [signal valueForKey:@"user_id"];
    }

    @try {
        SimilityContext *similityContext = [[SimilityContext alloc] init];
        [similityContext setCustomerId:customerId];
        [similityContext setSessionId:sessionId]; 
        [similityContext setUserId:userId]; 

        [[SimilityScript sharedInstance] execute:similityContext];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"success"];
    }
    @catch (NSException * e) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
