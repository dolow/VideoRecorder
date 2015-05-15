#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface VideoRecorderGLKitTestViewController : GLKViewController
{
    GLuint testBufferID;
    bool testFrameReversed;
    
    GLuint outputTexture;
    
    GLint dataInputTextureUniform;
    GLint dataPositionAttribute;
    GLint dataTextureCoordinateAttribute;
    
    UILabel* label;
}

@property (strong, nonatomic) GLKBaseEffect *baseEffect;

@end
