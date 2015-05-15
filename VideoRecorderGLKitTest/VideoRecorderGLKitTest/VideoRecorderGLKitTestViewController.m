#import "VideoRecorderGLKitTestViewController.h"
#import <AssetsLibrary/AssetsLibrary.h>

#import "VideoRecorder.h"

@implementation VideoRecorderGLKitTestViewController

@synthesize baseEffect;

static GLKVector3 vertices[] =
{
    {-0.5f, -0.5f, 0.0},
    { 0.5f, -0.5f, 0.0},
    {-0.5f,  0.5f, 0.0}
};

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    testFrameReversed = false;
    
    GLKView *view = (GLKView*)self.view;
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:view.context];
    
    baseEffect = [[GLKBaseEffect alloc] init];
    baseEffect.useConstantColor = GL_TRUE;
    baseEffect.constantColor    = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    glGenBuffers(1, &testBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, testBufferID);
    
    label = [[UILabel alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height - 20, 40, 100)];
    label.text  = @"RECORD";
    [label sizeToFit];
    label.textColor = [UIColor whiteColor];
    [self.view addSubview:label];
    
    [VideoRecorder prepare:self drawProcess:Block_copy(^{ [self _draw]; })];
}

#pragma mark - GLKView delegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    [self _setVertices];
    
    [self _draw];
}

- (void)_draw
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    [self.baseEffect prepareToDraw];
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLKVector3), ((char *)NULL + (0)));
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
    GLKView *view = (GLKView *)self.view;
    [EAGLContext setCurrentContext:view.context];
    
    if (0 != testBufferID)
        glDeleteBuffers(1, &testBufferID);
    
    view.context = nil;
    [EAGLContext setCurrentContext:nil];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return false;
}

# pragma mark - private

# pragma mark touches

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ([touches count] < 1) return;
    
    if (CGRectContainsPoint(label.frame, [[touches anyObject] locationInView:[self view]])) {
        if ([label.text isEqualToString:@"RECORD"]) {
            label.text = @"STOP";
            [[VideoRecorder getInstance] start];
        }
        else {
            label.text = @"RECORD";
            [[VideoRecorder getInstance] stop];
        }
    }
}

- (void)_setVertices
{
    if (testFrameReversed) {
        vertices[2].x += -0.01f;
        if (vertices[2].x <= -0.5f)
            testFrameReversed = !testFrameReversed;
    }
    else {
        vertices[2].x += 0.01f;
        if (vertices[2].x >= 0.5f)
            testFrameReversed = !testFrameReversed;
    }
}

@end
