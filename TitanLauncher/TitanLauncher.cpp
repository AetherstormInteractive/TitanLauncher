#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/bookctrl.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

using json = nlohmann::ordered_json;

std::string configPath = "config/engineConfig.ini";

class MyFrame : public wxFrame
{
public:
    wxBookCtrl* book;
    wxChoice* listbox1;
    wxChoice* listbox2;
    wxChoice* listbox3;
    wxChoice* listbox4;
    wxTextCtrl* display_width;
    wxTextCtrl* display_height;
    wxTextCtrl* textLog;
    MyFrame(const wxString& title);
    void OnResListBoxDoubleClick(wxCommandEvent& event);
    void OnRatioListBoxDoubleClick(wxCommandEvent& event);
    void OnBackendListBoxDoubleClick(wxCommandEvent& event);
    void OnWindowListBoxDoubleClick(wxCommandEvent& event);
    void OnCustomResEnter1(wxCommandEvent& event);
    void OnCustomResEnter2(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE()
};

// Declare some IDs. These are arbitrary.
const int BOOKCTRL = 100;

const int LISTBOX1 = 102;
const int LISTBOX2 = 103;
const int LISTBOX3 = 104;
const int LISTBOX4 = 110;

const int TEXTBOX1 = 105;
const int TEXTBOX2 = 106;
const int TEXTBOX3 = 107;

const int STATICTEXT1 = 108;
const int STATICTEXT2 = 109;

const int FILE_QUIT = wxID_EXIT;
const int HELP_ABOUT = wxID_ABOUT;

// Attach the event handlers. Put this after MyFrame declaration.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_TEXT_ENTER(TEXTBOX2, MyFrame::OnCustomResEnter1)
EVT_TEXT_ENTER(TEXTBOX3, MyFrame::OnCustomResEnter2)
EVT_CHOICE(LISTBOX1,
    MyFrame::OnResListBoxDoubleClick)
    EVT_CHOICE(LISTBOX2,
        MyFrame::OnRatioListBoxDoubleClick)
    EVT_CHOICE(LISTBOX3,
        MyFrame::OnBackendListBoxDoubleClick)
    EVT_CHOICE(LISTBOX4,
        MyFrame::OnWindowListBoxDoubleClick)
    EVT_MENU(FILE_QUIT, MyFrame::OnQuit)
    EVT_MENU(HELP_ABOUT, MyFrame::OnAbout)
    END_EVENT_TABLE()

    IMPLEMENT_APP(MyApp)

    bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(
        _T("Titan Launcher"));
    frame->Show(true);
    return true;
}

bool is_fullscreen = false;

wxString ratio_choices[] =
{
 _T("4:3"),
 _T("16:9")
};

wxString widescreen_choices[] =
{
 _T("720x480"),
 _T("960x540"),
 _T("1280x720"),
 _T("1366x768"),
 _T("1600x900"),
 _T("1920x1080"),
 _T("2560x1440"),
 _T("3200x1800"),
 _T("3840x2160"),
};

wxString sd_choices[] =
{
    _T("640x480"),
    _T("800x600"),
    _T("960x720"),
    _T("1024x768"),
    _T("1280x960"),
    _T("1440x1080"),
    _T("1600x1200"),
    _T("1920x1440")
};

wxString backend_choices[] =
{
    _T("OpenGL"),
    _T("Vulkan"),
    _T("Metal"),
    _T("DirectX11"),
    _T("DirectX12"),
    _T("SDL2")
};

wxString window_mode_choices[] =
{
    _T("Fullscreen"),
    _T("Borderless Fullscreen"),
    _T("Windowed")
};


MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(wxGetDisplaySize().GetX() / 4, wxGetDisplaySize().GetY() / 4), wxSize(960, 540), wxNO_BORDER)
{
    SetIcon(wxICON(sample));
    wxMenu* fileMenu = new wxMenu;
    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(HELP_ABOUT, _T("&About...\tF1"),
        _T("Show about dialog"));
    fileMenu->Append(FILE_QUIT, _T("E&xit\tAlt-X"),
        _T("Quit this program"));
    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText(_T("So far so good."), 0);
    SetStatusText(_T("Welcome."), 1);

    book = new wxBookCtrl(this, BOOKCTRL);
    wxPanel* panel = new wxPanel(book);
    book->AddPage(panel, _T("Game"), true);

    panel = new wxPanel(book);

    listbox2 = new wxChoice(panel, LISTBOX2,
        wxPoint(15, 25), wxSize(50, 85),
        2, ratio_choices, wxLB_SINGLE);

    listbox1 = new wxChoice(panel, LISTBOX1,
        wxPoint(75, 25), wxSize(150, 150),
        9, widescreen_choices, wxLB_SINGLE);

    listbox3 = new wxChoice(panel, LISTBOX3,
        wxPoint(235, 25), wxSize(75, 150),
        6, backend_choices, wxLB_SINGLE);

    listbox4 = new wxChoice(panel, LISTBOX4,
        wxPoint(320, 25), wxSize(125, 150),
        3, window_mode_choices, wxLB_SINGLE);

    new wxStaticText(panel, STATICTEXT1, _T("Custom"), wxPoint(15, 60), wxSize(50, 12), wxALIGN_LEFT);
    display_width = new wxTextCtrl(panel, TEXTBOX2, _T("Width\n"),
        wxPoint(15, 85), wxSize(50, 20), wxTE_LEFT | wxTE_PROCESS_ENTER);

    display_height = new wxTextCtrl(panel, TEXTBOX3, _T("Height\n"),
        wxPoint(65, 85), wxSize(50, 20), wxTE_LEFT | wxTE_PROCESS_ENTER);

    book->AddPage(panel, _T("Display"), false);

    panel = new wxPanel(book);
    wxBoxSizer* mysizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(mysizer);
    textLog = new wxTextCtrl(panel, TEXTBOX1, _T("Log\n"),
        wxPoint(0, 250), wxSize(100, 50), wxTE_MULTILINE);
    mysizer->Add(textLog, 1, wxEXPAND | wxALL, 5);
    book->AddPage(panel, _T("Debug"), false);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf(_T("About.\n")
        _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About My Program"),
        wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnResListBoxDoubleClick(wxCommandEvent& event)
{
    *textLog << "ListBox double click string is: \n";
    *textLog << event.GetString();
    *textLog << "\n";

    std::ifstream in(configPath);
    json infile = json::parse(in);

    //widescreen 16:9
    if (event.GetString() == "3840x2160")
    {
        infile["Display"]["Width"] = 3840;
        infile["Display"]["Height"] = 2160;
    }
    else if (event.GetString() == "3200x1800")
    {
        infile["Display"]["Width"] = 3200;
        infile["Display"]["Height"] = 1800;
    }
    else if (event.GetString() == "2560x1440")
    {
        infile["Display"]["Width"] = 2560;
        infile["Display"]["Height"] = 1440;
    }
    else if (event.GetString() == "1920x1080")
    {
        infile["Display"]["Width"] = 1920;
        infile["Display"]["Height"] = 1080;
    }
    else if (event.GetString() == "1600x900")
    {
        infile["Display"]["Width"] = 1600;
        infile["Display"]["Height"] = 900;
    }
    else if (event.GetString() == "1366x768")
    {
        infile["Display"]["Width"] = 1366;
        infile["Display"]["Height"] = 768;
    }
    else if (event.GetString() == "1280x720")
    {
        infile["Display"]["Width"] = 1280;
        infile["Display"]["Height"] = 720;
    }
    else if (event.GetString() == "960x540")
    {
        infile["Display"]["Width"] = 960;
        infile["Display"]["Height"] = 540;
    }
    else if (event.GetString() == "720x480")
    {
        infile["Display"]["Width"] = 720;
        infile["Display"]["Height"] = 480;
    }
    
    // standard 4:3
    if (event.GetString() == "640x480")
    {
        infile["Display"]["Width"] = 640;
        infile["Display"]["Height"] = 480;
    }
    else if (event.GetString() == "800x600")
    {
        infile["Display"]["Width"] = 800;
        infile["Display"]["Height"] = 600;
    }
    else if (event.GetString() == "960x720")
    {
        infile["Display"]["Width"] = 960;
        infile["Display"]["Height"] = 720;
    }
    else if (event.GetString() == "1024x768")
    {
        infile["Display"]["Width"] = 1024;
        infile["Display"]["Height"] = 768;
    }
    else if (event.GetString() == "1280x960")
    {
        infile["Display"]["Width"] = 1280;
        infile["Display"]["Height"] = 960;
    }
    else if (event.GetString() == "1440x1080")
    {
        infile["Display"]["Width"] = 1440;
        infile["Display"]["Height"] = 1080;
    }
    else if (event.GetString() == "1600x1200")
    {
        infile["Display"]["Width"] = 1600;
        infile["Display"]["Height"] = 1200;
    }
    else if (event.GetString() == "1920x1440")
    {
        infile["Display"]["Width"] = 1920;
        infile["Display"]["Height"] = 1440;
    }

    std::ofstream out(configPath);
    out << std::setw(4) << infile << std::endl;

    in.close();
    out.close();
}

void MyFrame::OnRatioListBoxDoubleClick(wxCommandEvent& event)
{
    *textLog << "ListBox double click string is: \n";
    *textLog << event.GetString();
    *textLog << "\n";

    if (event.GetString() == "4:3")
    {
        listbox1->Clear();

        listbox1->Append(sd_choices[0]);
        listbox1->Append(sd_choices[1]);
        listbox1->Append(sd_choices[2]);
        listbox1->Append(sd_choices[3]);
        listbox1->Append(sd_choices[4]);
        listbox1->Append(sd_choices[5]);
        listbox1->Append(sd_choices[6]);
        listbox1->Append(sd_choices[7]);
    }
    else if (event.GetString() == "16:9")
    {
        listbox1->Clear();

        listbox1->Append(widescreen_choices[0]);
        listbox1->Append(widescreen_choices[1]);
        listbox1->Append(widescreen_choices[2]);
        listbox1->Append(widescreen_choices[3]);
        listbox1->Append(widescreen_choices[4]);
        listbox1->Append(widescreen_choices[5]);
        listbox1->Append(widescreen_choices[6]);
        listbox1->Append(widescreen_choices[7]);
        listbox1->Append(widescreen_choices[8]);
    }
}

void MyFrame::OnWindowListBoxDoubleClick(wxCommandEvent& event)
{
    if (event.GetString() == "Fullscreen")
    {
        std::ifstream in(configPath);
        json infile = json::parse(in);

        infile["Display"]["WindowMode"] = 1;

        std::ofstream out(configPath);
        out << std::setw(4) << infile << std::endl;

        in.close();
        out.close();
    }
    else if (event.GetString() == "Borderless Fullscreen")
    {
        std::ifstream in(configPath);
        json infile = json::parse(in);

        infile["Display"]["WindowMode"] = 2;

        std::ofstream out(configPath);
        out << std::setw(4) << infile << std::endl;

        in.close();
        out.close();
    }
    else if (event.GetString() == "Windowed")
    {
        std::ifstream in(configPath);
        json infile = json::parse(in);
        
        infile["Display"]["WindowMode"] = 0;

        std::ofstream out(configPath);
        out << std::setw(4) << infile << std::endl;

        in.close();
        out.close();
    }
}

void MyFrame::OnCustomResEnter1(wxCommandEvent& event)
{
    if (event.GetString().IsNumber())
    {
        std::ifstream in(configPath);
        json infile = json::parse(in);
        int num;
        num = wxAtoi(event.GetString());
        infile["Display"]["Width"] = num;

        std::ofstream out(configPath);
        out << std::setw(4) << infile << std::endl;

        in.close();
        out.close();
    }
}

void MyFrame::OnCustomResEnter2(wxCommandEvent& event)
{
    if (event.GetString().IsNumber())
    {
        std::ifstream in(configPath);
        json infile = json::parse(in);
        int num;
        num = wxAtoi(event.GetString());
        infile["Display"]["Height"] = num;

        std::ofstream out(configPath);
        out << std::setw(4) << infile << std::endl;

        in.close();
        out.close();
    }
}

void MyFrame::OnBackendListBoxDoubleClick(wxCommandEvent& event)
{
    std::ifstream in(configPath);
    json infile = json::parse(in);

    if (event.GetString() == "OpenGL")
    {
        infile["Display"]["Backend"] = "OpenGL";
    }
    else if (event.GetString() == "Metal")
    {
        infile["Display"]["Backend"] = "Metal";
    }
    else if (event.GetString() == "Vulkan")
    {
        infile["Display"]["Backend"] = "Vulkan";
    }
    else if (event.GetString() == "DirectX11")
    {
        infile["Display"]["Backend"] = "DirectX11";
    }
    else if (event.GetString() == "DirectX12")
    {
        infile["Display"]["Backend"] = "DirectX12";
    }
    else if (event.GetString() == "SDL2")
    {
        infile["Display"]["Backend"] = "SDL2";
    }

    std::ofstream out(configPath);
    out << std::setw(4) << infile << std::endl;

    in.close();
    out.close();
}
