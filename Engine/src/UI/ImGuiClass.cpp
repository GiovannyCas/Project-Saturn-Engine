#include <header/ImGuiClass.h>


#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>




UI::ImGuiClass::ImGuiClass()
{

};


void UI::ImGuiClass::Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
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

void UI::ImGuiClass::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}
void UI::ImGuiClass::Shutdown()
{

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


}

bool UI::ImGuiClass::GetIsAmbientLightOn()
{
	return isAmbientLightOn;
}

bool UI::ImGuiClass::GetIsTextureOn()
{
	return isTextureOn;
}

bool UI::ImGuiClass::GetIsNormalMapOn()
{
	return isNormalMapOn;
}

DirectX::XMFLOAT3 UI::ImGuiClass::GetModelPosition()
{
	return modelPosition;
}

void UI::ImGuiClass::Render(Camera::CameraClass* other)
{
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	cameraPoistion = other->GetPosition();
	cameraRotation = other->GetRotation();

	ImGui::Begin("Profiler");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();

	{
		ImGui::Begin("Scene");
		
		ImGui::Text("Camera");

		ImGui::DragFloat3("Position", (float*)&cameraPoistion, 0.0174532925f * 1.0f);
		ImGui::SameLine(); 
		HelpMarker("To Move Foward Press:  W \nTo Move Backward Press: S \nTo Turn Left Press: A \nTo Turn Right Press: D");
		ImGui::DragFloat3("Rotation", (float*)&cameraRotation, 0.0174532925f * 1.0f);
		ImGui::SameLine();
		HelpMarker("To Move Upward Press: Up Arrow \nTo Move Downward Press: Down Arrow \nTo LookUp Press: Left Arrow \nTo LookDown Press: Right Arrow");
		ImGui::Text("\nModel Object");
	
		

		ImGui::Text("Render Shader Type:");
		
		if (ImGui::Checkbox("Render Model with Ambient Light",&isAmbientLightOn))
		{
			isTextureOn = false;
			isNormalMapOn = false;
		}
		
		if (ImGui::Checkbox("Render Model with Texture",&isTextureOn))
		{
			isAmbientLightOn = false;
			isNormalMapOn = false;
		}

		if (ImGui::Checkbox("Render Model with Normal Map", &isNormalMapOn))
		{
			isAmbientLightOn = false;
			isTextureOn = false;
		}
		

		ImGui::End();
	}

	other->SetPosition(cameraPoistion.x, cameraPoistion.y, cameraPoistion.z);
	other->SetRotation(cameraRotation.x, cameraRotation.y, cameraRotation.z);
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}




