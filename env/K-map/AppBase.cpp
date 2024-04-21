//#include "AppBase.h"
//
//#include <imgui.h>
//#include <imgui_impl_dx11.h>
//#include <imgui_impl_win32.h>
//#include <iostream>
//#include <memory>
//#include <windows.h>
//
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//// �ܼ�â�� ������ ����뿡 ���մϴ�.
//// ������� �� �ָ��� ������ cout���� ����ؼ� Ȯ���غ�����.
//int main() {
//    // �� ����Ϳ� �´� �ػ󵵷� �����ϼŵ� �˴ϴ�.
//    const int width = 1280, height = 960;
//
//    WNDCLASSEX wc = { sizeof(WNDCLASSEX),
//                     CS_CLASSDC,
//                     WndProc,
//                     0L,
//                     0L,
//                     GetModuleHandle(NULL),
//                     NULL,
//                     NULL,
//                     NULL,
//                     NULL,
//                     L"HongLabGraphics", // lpszClassName, L-string
//                     NULL };
//
//    RegisterClassEx(&wc);
//
//    // ���ٱ��� ������ ������ ��ü �ػ󵵰� �ƴ϶�
//    // �츮�� ������ �׸��� �ػ󵵰� width x height�� �ǵ���
//    // �����츦 ���� �ػ󵵸� �ٽ� ����ؼ� CreateWindow()���� ���
//
//    // �츮�� ���ϴ� �׸��� �׷��� �κ��� �ػ�
//    RECT wr = { 0, 0, width, height };
//
//    // �ʿ��� ������ ũ��(�ػ�) ���
//    // wr�� ���� �ٲ�
//    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
//
//    // �����츦 ���鶧 ������ ����� wr ���
//    HWND hwnd = CreateWindow(wc.lpszClassName, L"HongLabGraphics Example",
//        WS_OVERLAPPEDWINDOW,
//        100, // ������ ���� ����� x ��ǥ
//        100, // ������ ���� ����� y ��ǥ
//        wr.right - wr.left, // ������ ���� ���� �ػ�
//        wr.bottom - wr.top, // ������ ���� ���� �ػ�
//        NULL, NULL, wc.hInstance, NULL);
//
//    ShowWindow(hwnd, SW_SHOWDEFAULT);
//    UpdateWindow(hwnd);
//
//    // ���� Ŭ������ �ν��Ͻ� ���� (unique_ptr�� ����)
//    // ��: example = new Example(...)
//    auto example = std::make_unique<hlab::Example>(hwnd, width, height);
//
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO();
//    (void)io;
//    io.DisplaySize = ImVec2(width, height);
//    ImGui::StyleColorsLight();
//
//    // Setup Platform/Renderer backends
//    ImGui_ImplDX11_Init(example->device, example->deviceContext);
//    ImGui_ImplWin32_Init(hwnd);
//
//    // Main message loop
//    MSG msg = {};
//    while (WM_QUIT != msg.message) {
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        else {
//            // Start the Dear ImGui frame
//            ImGui_ImplDX11_NewFrame();
//            ImGui_ImplWin32_NewFrame();
//            ImGui::NewFrame();
//            ImGui::Begin("Scene Control");
//
//            ImGui::SliderFloat("earthDistance",
//                &example->rasterization.distSunToEarth, 0.0f,
//                0.6f);
//            ImGui::SliderFloat("earthAngularVelocity",
//                &example->rasterization.earthAngularVelocity,
//                0.0f, 2.0f);
//            ImGui::SliderFloat("moonDistance",
//                &example->rasterization.distEarthToMoon, 0.0f,
//                0.2f);
//            ImGui::SliderFloat("moonAngularVelocity",
//                &example->rasterization.moonAngularVelocity,
//                0.0f, 5.0f);
//
//            ImGui::End();
//            ImGui::Render();
//
//            example->Update();
//            example->Render();
//
//            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
//
//            // switch the back buffer and the front buffer
//            example->swapChain->Present(1, 0);
//        }
//    }
//
//    // Cleanup
//    ImGui_ImplDX11_Shutdown();
//    ImGui_ImplWin32_Shutdown();
//    ImGui::DestroyContext();
//
//    example->Clean();
//    DestroyWindow(hwnd);
//    UnregisterClass(wc.lpszClassName, wc.hInstance);
//
//    return 0;
//}
//
//AppBase* g_appBase = nullptr;
//
//// RegisterClassEx()���� ������ ��ϵ� �ݹ� �Լ�
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//
//    // g_appBase�� �̿��ؼ� ���������� ��� �Լ� ȣ��
//    return g_appBase->MsgProc(hWnd, msg, wParam, lParam);
//}
//
//// ������
//AppBase::AppBase()
//    : m_screenWidth(1280), m_screenHeight(960), m_mainWindow(0),
//    m_screenViewport(D3D11_VIEWPORT()) {
//
//    g_appBase = this;
//}
//
//AppBase::~AppBase() {
//    g_appBase = nullptr;
//
//    // Cleanup
//    ImGui_ImplDX11_Shutdown();
//    ImGui_ImplWin32_Shutdown();
//    ImGui::DestroyContext();
//
//    DestroyWindow(m_mainWindow);
//    // UnregisterClass(wc.lpszClassName, wc.hInstance);//����
//
//    // COMPtr���� �˾Ƽ� release
//    // ComPtr automatically maintains a reference count for the underlying
//    // interface pointer and releases the interface when the reference count
//    // goes to zero.
//    // https:learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170
//    // ����: m_d3dDevice.Reset(); ����
//}
//
//float AppBase::GetAspectRatio() const {
//    return float(m_screenWidth - m_guiWidth) / m_screenHeight;
//}
//
//int AppBase::Run() {
//
//    // Main message loop
//    MSG msg = { 0 };
//    while (WM_QUIT != msg.message) {
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        else {
//            ImGui_ImplDX11_NewFrame(); // GUI ������ ����
//            ImGui_ImplWin32_NewFrame();
//
//            ImGui::NewFrame(); // � �͵��� ������ ���� ��� ����
//            ImGui::Begin("Scene Control");
//
//            // ImGui�� �������ִ� Framerate ���
//            ImGui::Text("Average %.3f ms/frame (%.1f FPS)",
//                1000.0f / ImGui::GetIO().Framerate,
//                ImGui::GetIO().Framerate);
//
//            UpdateGUI(); // �߰������� ����� GUI
//
//            m_guiWidth = 0;
//            // ȭ���� ũ�� ���� ���� ��� ����
//            // ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
//            // m_guiWidth = int(ImGui::GetWindowWidth());
//
//            ImGui::End();
//            ImGui::Render(); // �������� �͵� ��� ��
//
//            Update(ImGui::GetIO().DeltaTime); // �ִϸ��̼� ���� ��ȭ
//
//            Render(); // �츮�� ������ ������
//
//            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); // GUI ������
//
//            // Switch the back buffer and the front buffer
//            // ����: ImGui RenderDrawData() ������ Present() ȣ��
//            m_swapChain->Present(1, 0);
//        }
//    }
//
//    return 0;
//}
//
//// Forward declare message handler from imgui_impl_win32.cpp
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
//    UINT msg,
//    WPARAM wParam,
//    LPARAM lParam);
//
//// Windows procedure
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
//        return true;
//
//    switch (msg) {
//    case WM_SIZE:
//        // Reset and resize swapchain
//        return 0;
//    case WM_SYSCOMMAND:
//        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
//            return 0;
//        break;
//    case WM_MOUSEMOVE:
//        // std::cout << "Mouse " << LOWORD(lParam) << " " << HIWORD(lParam) <<
//        // std::endl;
//        break;
//    case WM_LBUTTONUP:
//        // std::cout << "WM_LBUTTONUP Left mouse button" << std::endl;
//        break;
//    case WM_RBUTTONUP:
//        // std::cout << "WM_RBUTTONUP Right mouse button" << std::endl;
//        break;
//    case WM_KEYDOWN:
//        // std::cout << "WM_KEYDOWN " << (int)wParam << std::endl;
//        break;
//    case WM_DESTROY:
//        ::PostQuitMessage(0);
//        return 0;
//    }
//
//    return ::DefWindowProc(hWnd, msg, wParam, lParam);
//}
