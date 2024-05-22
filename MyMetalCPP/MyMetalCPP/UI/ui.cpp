//
//  ui.cpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 22/05/2024.
//

#include "ui.hpp"

#include "imgui.h"
#include "imgui_impl_metal.h"
#include "imgui_impl_osx.h"

UI* UI::pInstance = nullptr;

UI* UI::Instance()
{
    if( !pInstance )
    {
        pInstance = new UI();
    }
    return pInstance;
}

void UI::Init(MTL::Device* pDevice, MTK::View* pView)
{
    IMGUI_CHECKVERSION();
    _pView = pView;
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Renderer backend
    ImGui_ImplMetal_Init(pDevice);
    
    ImGui_ImplOSX_Init(pView);
}

void UI::NewFrame(class MTL::RenderPassDescriptor* pRpd, MTL::RenderCommandEncoder* pEnc)
{
    _pEnc = pEnc;
    pEnc->pushDebugGroup( AAPLSTR( "Dear ImGui" ) );
    ImGui_ImplMetal_NewFrame(pRpd);
    ImGui_ImplOSX_NewFrame(_pView);
    ImGui::NewFrame();
}

void UI::Draw(class MTL::CommandBuffer* pCmd)
{
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
    ImGui_ImplMetal_RenderDrawData(draw_data, pCmd, _pEnc);
    _pEnc->popDebugGroup();
}
