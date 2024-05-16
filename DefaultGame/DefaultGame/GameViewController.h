//
//  GameViewController.h
//  DefaultGame
//
//  Created by Martin Linklater on 11/05/2024.
//

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "RendererObjC.h"

#define USE_CPP_RENDERER 1

// Our macOS view controller.
#if USE_CPP_RENDERER
@interface GameViewController : NSViewController <MTKViewDelegate>
#else
@interface GameViewController : NSViewController
#endif

@end
