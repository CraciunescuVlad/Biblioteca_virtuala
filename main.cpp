#include "shared/classes/administrator/Administrator.h"
#include "shared/classes/utilizator/Utilizator.h"
#include "shared/classes/utilizator/Imprumut.h"
#include "shared/classes/gestionareFisiere/GestionareFisiere.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <algorithm>

// Variabila globala care retine modul selectat: 0 = niciunul, 1 = utilizator, 2 = administrator
int mod_selectat = 0;

// Functia care deseneaza interfata pentru utilizator
void interfata_utilizator() {
    // Obiect static de tip Utilizator, retine starea
    static Utilizator utilizator;
    static char isbn[100] = "";
    static int nr_exemplare = 1;
    static char numeUtilizator[100] = "";

    // Pentru afisarea cosului in interfata
    static bool afiseazaCos = false;
    static vector<string> cosVizibil;

    // Pentru feedback dupa imprumut sau alte actiuni
    static bool imprumutEfectuat = false;
    static string mesajFeedback = "";
    static string mesajImprumut = "";
    static ImVec4 culoareFeedback = ImVec4(1, 1, 1, 1);

    ImGui::Begin("Panou Utilizator");

    // Input ISBN si nr. exemplare
    ImGui::InputText("ISBN", isbn, IM_ARRAYSIZE(isbn));
    ImGui::InputInt("Numar exemplare", &nr_exemplare);

    // Buton pentru adaugare carte in cos
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

    // Modifica carte din cos
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

    // Sterge carte din cos
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

    // Vizualizeaza cos
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

    // Input nume utilizator si efectuare imprumut
    ImGui::InputText("Nume utilizator", numeUtilizator, IM_ARRAYSIZE(numeUtilizator));
    if (ImGui::Button("Imprumuta")) {
        auto cosCurent = GestionareFisiere::incarcaCos();
        if (cosCurent.empty()) {
            mesajImprumut = "Eroare: cosul este gol. Nu se poate efectua imprumutul.";
            imprumutEfectuat = true;
        } else {
            utilizator.imprumuta(numeUtilizator, false);
            mesajImprumut = string("Imprumut realizat cu succes pentru: ") + numeUtilizator;
            imprumutEfectuat = true;
        }
    }

    // Feedback vizual dupa imprumut
    if (imprumutEfectuat) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", mesajImprumut.c_str());
    }

    // Buton pentru revenire la ecranul principal
    if (ImGui::Button("\u2B90 \u00CEnapoi")) {
        extern int mod_selectat;
        mod_selectat = 0;
    }

    ImGui::End();
}


// Funcția care construiește interfața grafică pentru administratorul bibliotecii
void interfata_administrator() {
    // Obiect pentru gestionarea operațiilor de administrator
    static Administrator admin;

    // Buffere pentru introducerea datelor unei cărți
    static char isbn[100] = "";
    static char titlu[100] = "";
    static char autor[100] = "";
    static int stoc = 1;

    // Variabile pentru afișarea mesajelor de feedback
    static bool actiuneCuMesaj = false;
    static std::string mesajActiune = "";

    // Variabile de control pentru afișarea diferitelor formulare
    static bool showAddForm = false;
    static bool showDeleteForm = false;
    static bool showUpdateForm = false;
    static bool showCarti = false;
    static bool showImprumuturi = false;

    // Liste pentru afișarea datelor în interfață
    static std::vector<Carte> cartiVizibile;
    static std::vector<std::string> imprumuturiVizibile;

    // Începe fereastra pentru panoul de administrator
    ImGui::Begin("Panou Administrator");

    // Buton pentru a activa formularul de adăugare a unei cărți
    if (ImGui::Button("Adauga carte")) {
        showAddForm = !showAddForm;
        showDeleteForm = false;
        showUpdateForm = false;
        actiuneCuMesaj = false;
    }

    // Formularul efectiv pentru adăugarea unei cărți
    if (showAddForm) {
        ImGui::InputText("ISBN", isbn, IM_ARRAYSIZE(isbn));
        ImGui::InputText("Titlu", titlu, IM_ARRAYSIZE(titlu));
        ImGui::InputText("Autor", autor, IM_ARRAYSIZE(autor));
        ImGui::InputInt("Stoc", &stoc);

        // Confirmă adăugarea cărții
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

    // Buton pentru a activa formularul de ștergere a unei cărți
    if (ImGui::Button("Sterge carte")) {
        showDeleteForm = !showDeleteForm;
        showAddForm = false;
        showUpdateForm = false;
        actiuneCuMesaj = false;
    }

    // Formularul efectiv pentru ștergerea unei cărți
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

    // Buton pentru a activa formularul de modificare a stocului unei cărți
    if (ImGui::Button("Modifica stoc")) {
        showUpdateForm = !showUpdateForm;
        showAddForm = false;
        showDeleteForm = false;
        actiuneCuMesaj = false;
    }

    // Formularul efectiv pentru modificarea stocului
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

    // Buton pentru a vizualiza toate cărțile din bibliotecă
    if (ImGui::Button("Vizualizeaza carti")) {
        cartiVizibile = admin.getCarti();
        showCarti = true;
        showImprumuturi = false;
    }

    // Afișarea efectivă a cărților într-un format lizibil
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

    // Buton pentru a vizualiza fișele de împrumut
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

    // Afișează fișele de împrumut încărcate din fișier
    if (showImprumuturi) {
        ImGui::Separator();
        ImGui::Text("Imprumuturi:");
        for (const auto& linie : imprumuturiVizibile) {
            ImGui::BulletText("%s", linie.c_str());
        }
    }

    // Afișează mesajul de feedback după o acțiune
    if (actiuneCuMesaj) {
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", mesajActiune.c_str());
    }

    // Buton pentru a reveni la meniul principal (modul de selecție)
    if (ImGui::Button("⮐ Inapoi")) {
        extern int mod_selectat;
        mod_selectat = 0;
    }

    // Finalizează fereastra de interfață grafică
    ImGui::End();
}



int main() {
    // Inițializează biblioteca GLFW (folosită pentru crearea ferestrei și manipularea evenimentelor)
    if (!glfwInit()) return -1; // Dacă inițializarea eșuează, oprește programul

    // Creează o fereastră de 1280x720 cu titlul "Biblioteca Virtuala"
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Biblioteca Virtuala", NULL, NULL);
    if (!window) {
        glfwTerminate(); // Închide GLFW dacă fereastra nu s-a putut crea
        return -1;
    }

    // Setează contextul OpenGL pentru această fereastră
    glfwMakeContextCurrent(window);

    // Activează sincronizarea cadrelor cu rata de refresh a monitorului (evită tearing-ul)
    glfwSwapInterval(1);

    // Inițializează contextul Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; // Obiect folosit pentru opțiuni și configurări (nefolosit explicit aici)

    // Setează stilul vizual (temă închisă)
    ImGui::StyleColorsDark();

    // Inițializează Dear ImGui pentru a lucra cu GLFW și OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130"); // Specifică versiunea GLSL folosită

    // Bucla principală a aplicației – se execută până când utilizatorul închide fereastra
    while (!glfwWindowShouldClose(window)) {
        // Verifică și procesează evenimentele de sistem (ex: apăsări taste, clickuri)
        glfwPollEvents();

        // Creează un nou frame (cadru) pentru interfața ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Afișează meniul de selecție dacă niciun mod nu e activat
        if (mod_selectat == 0) {
            ImGui::Begin("Selecteaza mod:");
            if (ImGui::Button("Utilizator")) mod_selectat = 1;
            if (ImGui::Button("Administrator")) mod_selectat = 2;
            ImGui::End();
        }
        // Afișează interfața pentru utilizator
        else if (mod_selectat == 1) {
            interfata_utilizator();
        }
        // Afișează interfața pentru administrator
        else if (mod_selectat == 2) {
            interfata_administrator();
        }

        // Finalizează desenarea elementelor ImGui
        ImGui::Render();

        // Obține dimensiunile ferestrei (pentru a seta viewport-ul OpenGL corect)
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // Curăță ecranul cu o culoare gri închis
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenează conținutul interfeței grafice
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Afișează frame-ul desenat în fereastră
        glfwSwapBuffers(window);
    }

    // Curățare la închiderea aplicației – închide și eliberează resursele ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Închide fereastra și oprește GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0; // Încheie programul cu succes
}

