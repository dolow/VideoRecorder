#import <UIKit/UIKit.h>
@class SimpleVideoFileFilterViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    SimpleVideoFileFilterViewController *rootViewController;
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UIViewController *viewController;

@end
