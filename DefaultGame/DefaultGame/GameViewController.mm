//
//  GameViewController.m
//  DefaultGame
//
//  Created by Martin Linklater on 11/05/2024.
//

#import "GameViewController.h"
#import "RendererObjC.h"

#if USE_CPP_RENDERER
#include "Renderer.hpp"
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#endif // USE_CPP_RENDERER

@implementation GameViewController
{
    MTKView *_view;

#if USE_CPP_RENDERER
    Renderer*   renderer;
    
    MTL::Device* _pDevice;
#else
    RendererObjC *_renderer;
#endif // USE_CPP_RENDERER
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    _view = (MTKView *)self.view;

    _view.device = MTLCreateSystemDefaultDevice();

    if(!_view.device)
    {
        NSLog(@"Metal is not supported on this device");
        self.view = [[NSView alloc] initWithFrame:self.view.frame];
        return;
    }

#if USE_CPP_RENDERER
    renderer = new Renderer();
#else
    _renderer = [[RendererObjC alloc] initWithMetalKitView:_view];

    [_renderer mtkView:_view drawableSizeWillChange:_view.drawableSize];

    _view.delegate = _renderer;
#endif // USE_CPP_RENDERER
}

#if USE_CPP_RENDERER
- (void)drawInMTKView:(nonnull MTKView *)view {
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size { 
}

- (BOOL)commitEditingAndReturnError:(NSError *__autoreleasing  _Nullable * _Nullable)error { 
    return true;
}

- (void)encodeWithCoder:(nonnull NSCoder *)coder { 
}
#endif // USE_CPP_RENDERER

@end
