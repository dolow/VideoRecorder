# VideoRecorder

is the module to record screen usng OpenGLES.

This is written in Objective-C and for iOS.


## Usage

1. incude required frameworks
    * AssetsLibrary.framework
    * CoreMedia.framework
    * CoreVideo.framework

2. run "prepare" to initialize.
    * 1st arg : current view controller
    * 2nd arg : opengl drawing process

    notice : 2nd arg is exuted only for video recording not for your screen.

```Objective-C
[VideoRecorder prepare:viewController
           drawProcess:(DrawProcess)^{ [self drawMethod]; }];
```

3. run "start" and stop anywhere you ike.

```
[[VideoRecorder getInstance] start];
```

```
[[VideoRecorder getInstance] stop];
```


For more detail information, please refere to the sample projects included in this repository.
Both OpenGLKit project and cocos2d-x (3.4) project are available.


## Notice

No test codes sorry.

