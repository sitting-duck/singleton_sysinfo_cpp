#import <objc/NSObject.h>

float mac_version() {
    @autoreleasepool {
        float version = -1;
        NSString *versionString = [[NSProcessInfo processInfo] operatingSystemVersionString];
        NSLog(@"MAC Version String: %@", versionString);
        if([versionString containsString:@"10."]) {
            NSArray *parts = [versionString componentsSeparatedByString:@"10."];
            version = 10.0f + [parts[1] floatValue]/100.0f;
            NSLog(@"OSX Version: %@ float: %f", parts[1], version);
        } else {
            NSArray *parts = [versionString componentsSeparatedByString:@"11."];
            version = 11.0f + [parts[1] floatValue]/100.0f;
            NSLog(@"OSX Version: %@ float: %f", parts[1], version);
        }
        return version;
    }
}

NSString osx_version_as_string() {
    NSProcessInfo *pInfo = [NSProcessInfo processInfo];
    NSString *version = [pInfo operatingSystemVersionString];
    return version;
}
