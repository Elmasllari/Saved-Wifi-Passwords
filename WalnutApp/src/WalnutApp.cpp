#include "Walnut/Application.h"

#include "Walnut/EntryPoint.h"


#include "Walnut/Image.h"

#include "Walnut/Syscpp.h"


std::vector<std::string> pass = Password();
std::vector<std::string> usn = UserName();
const char* p;
const char* u;

//forget button & confirmation
bool PopUp() {
    bool confirmation = false;

    if (ImGui::BeginPopupContextItem("my popup")) // <-- use last item id as popup id
    {
        ImGui::Text("Are you sure you want to forget this network?");

        if (ImGui::Button("Yes")) {
            confirmation = true;

        }
        if (ImGui::Button("No")) {
            confirmation = false;

        }

        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    if (ImGui::Button("Forget"))
        ImGui::OpenPopup("my popup");

    return confirmation;
}

class ExampleLayer : public Walnut::Layer {
public: bool testl = false;

      virtual void OnUIRender() override {

          static float window_scale = 1.0f;
          int x = GetSystemMetrics(SM_CXSCREEN);
          int y = GetSystemMetrics(SM_CYSCREEN);
          ImGui::SetNextWindowSize(ImVec2(x - 300, y - 100));
          ImGui::StyleColorsLight();

          ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoResize);

          ImGui::SetWindowFontScale(1.5);
          ImGui::LabelText("Password", "Wifi Network");
          ImGui::SetWindowFontScale(window_scale);

          for (int i = 0, rows = 0, columns = 0; i < usn.size(); i++) { //every username and password
              u = usn[i].c_str();
              p = pass[i].c_str();
              ImGui::LabelText(p, u);

             
          }

          ImGui::End();

      }

};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv) {
    Walnut::ApplicationSpecification spec;
    spec.Name = "Saved Wifi Passwords";

    DPI_AWARENESS_CONTEXT u = SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);

    spec.Width = x;
    spec.Height = y;

    Walnut::Application* app = new Walnut::Application(spec);
    app->PushLayer < ExampleLayer >();
    app->SetMenubarCallback([app]() {

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                app->Close();
            }
            ImGui::EndMenu();
        }
        });
    return app;
}
