#include "../src/header/ImGuiClass.h"


#include "../imGui/imgui.h"
#include "../imGui/imgui_impl_win32.h"
#include "../imGui/imgui_impl_dx11.h"


ImGuiClass::ImGuiClass()
{

	

	
};




ImGuiClass::ImGuiClass(ImGuiClass& other)
{

}

ImGuiClass::~ImGuiClass()
{

}

void ImGuiClass::Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, deviceContext);

}

void ImGuiClass::Shutdown()
{
	
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


}

void ImGuiClass::Render(CameraClass* other)
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//col2 = other->GetAmbientColor();
	Dirc = other->GetRotation();

	ImGui::Begin("Profiler");

	ImGui::Text("This is some useful text.");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();

	{
		ImGui::Begin("3d Object");
		
		ImGui::Text("Direction");
		ImGui::DragFloat3("", (float*)&Dirc, 0.0174532925f * 1.0f);

		ImGui::Text("Light Color");
		//ImGui::ColorEdit4("Ambient Color", (float*) &col2);

		ImGui::End();
	}
	other->SetRotation(Dirc.x, Dirc.y, Dirc.z);
	//other->SetDirection(Dirc.x, Dirc.y, Dirc.z);
	//other->SetAmbientColor(col2.x, col2.y, col2.z, col2.w);
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}




