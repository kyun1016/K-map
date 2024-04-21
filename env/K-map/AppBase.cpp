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
//// 콘솔창이 있으면 디버깅에 편리합니다.
//// 디버깅할 때 애매한 값들을 cout으로 출력해서 확인해보세요.
//int main() {
//    // 내 모니터에 맞는 해상도로 조절하셔도 됩니다.
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
//    // 툴바까지 포함한 윈도우 전체 해상도가 아니라
//    // 우리가 실제로 그리는 해상도가 width x height가 되도록
//    // 윈도우를 만들 해상도를 다시 계산해서 CreateWindow()에서 사용
//
//    // 우리가 원하는 그림이 그려질 부분의 해상도
//    RECT wr = { 0, 0, width, height };
//
//    // 필요한 윈도우 크기(해상도) 계산
//    // wr의 값이 바뀜
//    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
//
//    // 윈도우를 만들때 위에서 계산한 wr 사용
//    HWND hwnd = CreateWindow(wc.lpszClassName, L"HongLabGraphics Example",
//        WS_OVERLAPPEDWINDOW,
//        100, // 윈도우 좌측 상단의 x 좌표
//        100, // 윈도우 좌측 상단의 y 좌표
//        wr.right - wr.left, // 윈도우 가로 방향 해상도
//        wr.bottom - wr.top, // 윈도우 세로 방향 해상도
//        NULL, NULL, wc.hInstance, NULL);
//
//    ShowWindow(hwnd, SW_SHOWDEFAULT);
//    UpdateWindow(hwnd);
//
//    // 예제 클래스의 인스턴스 생성 (unique_ptr로 만듦)
//    // 비교: example = new Example(...)
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
//// RegisterClassEx()에서 실제로 등록될 콜백 함수
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//
//    // g_appBase를 이용해서 간접적으로 멤버 함수 호출
//    return g_appBase->MsgProc(hWnd, msg, wParam, lParam);
//}
//
//// 생성자
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
//    // UnregisterClass(wc.lpszClassName, wc.hInstance);//생략
//
//    // COMPtr에서 알아서 release
//    // ComPtr automatically maintains a reference count for the underlying
//    // interface pointer and releases the interface when the reference count
//    // goes to zero.
//    // https:learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170
//    // 예시: m_d3dDevice.Reset(); 생략
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
//            ImGui_ImplDX11_NewFrame(); // GUI 프레임 시작
//            ImGui_ImplWin32_NewFrame();
//
//            ImGui::NewFrame(); // 어떤 것들을 렌더링 할지 기록 시작
//            ImGui::Begin("Scene Control");
//
//            // ImGui가 측정해주는 Framerate 출력
//            ImGui::Text("Average %.3f ms/frame (%.1f FPS)",
//                1000.0f / ImGui::GetIO().Framerate,
//                ImGui::GetIO().Framerate);
//
//            UpdateGUI(); // 추가적으로 사용할 GUI
//
//            m_guiWidth = 0;
//            // 화면을 크게 쓰기 위해 기능 정지
//            // ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
//            // m_guiWidth = int(ImGui::GetWindowWidth());
//
//            ImGui::End();
//            ImGui::Render(); // 렌더링할 것들 기록 끝
//
//            Update(ImGui::GetIO().DeltaTime); // 애니메이션 같은 변화
//
//            Render(); // 우리가 구현한 렌더링
//
//            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); // GUI 렌더링
//
//            // Switch the back buffer and the front buffer
//            // 주의: ImGui RenderDrawData() 다음에 Present() 호출
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
