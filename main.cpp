#include "administrator/Administrator.h"
#include "utilizator/Utilizator.h"
#include "utilizator/Imprumut.h"
#include "fisiere/GestionareFisiere.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <algorithm>

int mod_selectat = 0;

void interfata_utilizator() {
    static Utilizator utilizator;
    static char isbn[100] = "";
    static int nr_exemplare = 1;
    static char numeUtilizator[100] = "";

    static bool afiseazaCos = false;
    static vector<string> cosVizibil;

    static bool imprumutEfectuat = false;
    static string mesajFeedback = "";
    static string mesajImprumut = "";
    static ImVec4 culoareFeedback = ImVec4(1, 1, 1, 1);

    ImGui::Begin("Panou Utilizator");

    ImGui::InputText("ISBN", isbn, IM_ARRAYSIZE(isbn));
    ImGui::InputInt("Numar exemplare", &nr_exemplare);

    if (ImGui::Button("Adauga in cos")) {
        if (nr_exemplare <= 0) {
            mesajFeedback = "Numarul de exemplare trebuie sa fie pozitiv.";
            culoareFeedback = ImVec4(1, 0.4f, 0.4f, 1);
        } else {
            auto carti = GestionareFisiere::incarcaCarti();
            bool exista = any_of(carti.begin(), carti.end(), [&](const Carte& c) { return c.getISBN() == isbn; });
            if (!exista) {
                mesajFeedback = "Cartea nu exista in biblioteca!";
                culoareFeedback = ImVec4(1, 0.4f, 0.4f, 1);
            } else {
                utilizator.adaugaCarte(isbn, nr_exemplare, false);
                mesajFeedback = "Carte adaugata in cos!";
                culoareFeedback = ImVec4(0.3f, 1, 0.3f, 1);
            }
        }
    }

    if (ImGui::Button("Modifica carte")) {
        if (nr_exemplare <= 0) {
            mesajFeedback = "Numarul de exemplare trebuie sa fie pozitiv.";
            culoareFeedback = ImVec4(1, 0.4f, 0.4f, 1);
        } else {
            auto cosMap = utilizator.getCosMap();
            if (cosMap.find(isbn) == cosMap.end()) {
                mesajFeedback = "Cartea nu exista in cos!";
                culoareFeedback = ImVec4(1, 0.4f, 0.4f, 1);
            } else {
                utilizator.modificaCarte(isbn, nr_exemplare, false);
                mesajFeedback = "Carte modificata cu succes.";
                culoareFeedback = ImVec4(0.3f, 1, 0.3f, 1);
            }
        }
    }

    if (ImGui::Button("Sterge carte")) {
        auto cosMap = utilizator.getCosMap();
        if (cosMap.find(isbn) == cosMap.end()) {
            mesajFeedback = "Cartea nu exista in cos!";
            culoareFeedback = ImVec4(1, 0.4f, 0.4f, 1);
        } else {
            utilizator.stergeCarte(isbn, false);
            mesajFeedback = "Carte stearsa din cos.";
            culoareFeedback = ImVec4(0.3f, 1, 0.3f, 1);
        }
    }

    ImGui::Separator();

    if (ImGui::Button("Vizualizeaza cos")) {
        afiseazaCos = true;
        cosVizibil = utilizator.getCos();
    }

    if (afiseazaCos) {
        ImGui::Text("Cosul de carti:");
        for (const auto& linie : cosVizibil) {
            ImGui::BulletText("%s", linie.c_str());
        }
    }

    ImGui::InputText("Nume utilizator", numeUtilizator, IM_ARRAYSIZE(numeUtilizator));
    if (ImGui::Button("Imprumuta")) {
        auto cosCurent = GestionareFisiere::incarcaCos();
        if (cosCurent.empty()) {
            mesajImprumut = "Eroare: cosul este gol. Nu se poate efectua imprumutul.";
            imprumutEfectuat = true;
        } else {
            utilizator.imprumuta(numeUtilizator, false);  // false => nu afiseaza in terminal
            mesajImprumut = string("Imprumut realizat cu succes pentru: ") + numeUtilizator;
            imprumutEfectuat = true;
        }
    }

    if (imprumutEfectuat) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", mesajImprumut.c_str());
    }


    if (ImGui::Button("⮐ Înapoi")) {
        extern int mod_selectat;
        mod_selectat = 0;
    }

    ImGui::End();
}

void interfata_administrator() {
    static Administrator admin;
    static char isbn[100] = "";
    static char titlu[100] = "";
    static char autor[100] = "";
    static int stoc = 1;

    static bool actiuneCuMesaj = false;
    static std::string mesajActiune = "";

    static bool showAddForm = false;
    static bool showDeleteForm = false;
    static bool showUpdateForm = false;
    static bool showCarti = false;
    static bool showImprumuturi = false;

    static std::vector<Carte> cartiVizibile;
    static std::vector<std::string> imprumuturiVizibile;

    ImGui::Begin("Panou Administrator");

    if (ImGui::Button("Adauga carte")) {
        showAddForm = !showAddForm;
        showDeleteForm = false;
        showUpdateForm = false;
        actiuneCuMesaj = false;
    }

    if (showAddForm) {
        ImGui::InputText("ISBN", isbn, IM_ARRAYSIZE(isbn));
        ImGui::InputText("Titlu", titlu, IM_ARRAYSIZE(titlu));
        ImGui::InputText("Autor", autor, IM_ARRAYSIZE(autor));
        ImGui::InputInt("Stoc", &stoc);

        if (ImGui::Button("Confirma adaugare")) {
            if (stoc < 0) {
                mesajActiune = "Eroare: Stocul nu poate fi negativ.";
            } else {
                admin.adaugaCarte(Carte(isbn, titlu, autor, stoc), false);
                mesajActiune = "Carte adaugata cu succes.";
            }
            actiuneCuMesaj = true;
            showAddForm = false;
        }
    }

    if (ImGui::Button("Sterge carte")) {
        showDeleteForm = !showDeleteForm;
        showAddForm = false;
        showUpdateForm = false;
        actiuneCuMesaj = false;
    }

    if (showDeleteForm) {
        ImGui::InputText("ISBN de sters", isbn, IM_ARRAYSIZE(isbn));
        if (ImGui::Button("Confirma stergere")) {
            auto carti = admin.getCarti();
            bool gasit = false;
            for (const auto& c : carti) {
                if (c.getISBN() == isbn) {
                    gasit = true;
                    break;
                }
            }
            if (gasit) {
                admin.stergeCarte(isbn, false);
                mesajActiune = "Carte stearsa cu succes.";
            } else {
                mesajActiune = "Eroare: Carte inexistenta.";
            }
            actiuneCuMesaj = true;
            showDeleteForm = false;
        }
    }

    if (ImGui::Button("Modifica stoc")) {
        showUpdateForm = !showUpdateForm;
        showAddForm = false;
        showDeleteForm = false;
        actiuneCuMesaj = false;
    }

    if (showUpdateForm) {
        ImGui::InputText("ISBN pentru modificare", isbn, IM_ARRAYSIZE(isbn));
        ImGui::InputInt("Noul stoc", &stoc);
        if (ImGui::Button("Confirma modificare")) {
            if (stoc < 0) {
                mesajActiune = "Eroare: Stocul nu poate fi negativ.";
            } else {
                auto carti = admin.getCarti();
                bool gasit = false;
                for (const auto& c : carti) {
                    if (c.getISBN() == isbn) {
                        gasit = true;
                        break;
                    }
                }
                if (gasit) {
                    admin.modificaStoc(isbn, stoc, false);
                    mesajActiune = "Stoc modificat cu succes.";
                } else {
                    mesajActiune = "Eroare: Carte inexistenta.";
                }
            }
            actiuneCuMesaj = true;
            showUpdateForm = false;
        }
    }

    if (ImGui::Button("Vizualizeaza carti")) {
        cartiVizibile = admin.getCarti();
        showCarti = true;
        showImprumuturi = false;
    }

    if (showCarti) {
        ImGui::Separator();
        ImGui::Text("Carti disponibile:");
        for (const auto& carte : cartiVizibile) {
            string info = "ISBN: " + carte.getISBN()
                         + " | Titlu: " + carte.getTitlu()
                         + " | Autor: " + carte.getAutor()
                         + " | Stoc: " + to_string(carte.getStoc());
             ImGui::TextWrapped("%s", info.c_str());
        }
    }

    if (ImGui::Button("Vizualizeaza imprumuturi")) {
        std::ifstream fin("imprumuturi.txt");
        imprumuturiVizibile.clear();
        std::string linie;
        while (std::getline(fin, linie)) {
            imprumuturiVizibile.push_back(linie);
        }
        showImprumuturi = true;
        showCarti = false;
    }

    if (showImprumuturi) {
        ImGui::Separator();
        ImGui::Text("Imprumuturi:");
        for (const auto& linie : imprumuturiVizibile) {
            ImGui::BulletText("%s", linie.c_str());
        }
    }

    if (actiuneCuMesaj) {
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", mesajActiune.c_str());
    }

    if (ImGui::Button("⮐ Inapoi")) {
        extern int mod_selectat;
        mod_selectat = 0;
    }

    ImGui::End();
}


int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Biblioteca Virtuala", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (mod_selectat == 0) {
            ImGui::Begin("Selecteaza mod:");
            if (ImGui::Button("Utilizator")) mod_selectat = 1;
            if (ImGui::Button("Administrator")) mod_selectat = 2;
            ImGui::End();
        }
        else if (mod_selectat == 1) {
            interfata_utilizator();
        }
        else if (mod_selectat == 2) {
            interfata_administrator();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
