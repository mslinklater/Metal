//
//  AppDelegate.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#pragma once

#include "Common.h"

class MTKViewDelegate;

class AppDelegate : public NS::ApplicationDelegate
{
public:
    virtual ~AppDelegate();

    NS::Menu* createMenuBar();

    virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
    virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

private:
    NS::Window* _pWindow;
    MTK::View* _pMtkView;
    MTL::Device* _pDevice;
    MTKViewDelegate* _pViewDelegate = nullptr;
};
