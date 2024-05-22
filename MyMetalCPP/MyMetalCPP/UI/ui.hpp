//
//  ui.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 22/05/2024.
//

#pragma once

#include <stdio.h>
#include "../Common.h"

// Yes - it's a singleton - sue me

class UI {
public:
    static UI* Instance();
    
    void Init(class MTL::Device* pDevice, class MTK::View* pView);
    void NewFrame(class MTL::RenderPassDescriptor* pRpd, MTL::RenderCommandEncoder* pEnc);
    void Draw(class MTL::CommandBuffer* pCmd);
private:
    static UI* pInstance;
    class MTK::View* _pView;
    class MTL::RenderCommandEncoder* _pEnc;
};
