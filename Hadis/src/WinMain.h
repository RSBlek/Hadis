#pragma once
#include "stdafx.h"
#include "BarHandler.h"

using namespace System::Runtime::InteropServices;

namespace Hadis {
	[DllImport("HadisMain.dll",
		EntryPoint = "?start@@YAXH@Z",
		ExactSpelling = true,
		CallingConvention = CallingConvention::Cdecl)]
	extern void start(int ip);
	[DllImport("HadisMain.dll",
		EntryPoint = "?getPlayerStatInfo@@YAPAV?$vector@VPlayerStatInfo@@V?$allocator@VPlayerStatInfo@@@std@@@std@@IW4PlayerStatInfoType@PlayerStatInfo@@@Z",
		ExactSpelling = true,
		CallingConvention = CallingConvention::Cdecl)]
	extern std::vector<PlayerStatInfo>* getPlayerStatInfo(unsigned int target, PlayerStatInfo::PlayerStatInfoType type);

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;


	/// <summary>
	/// Zusammenfassung für WinMain
	/// </summary>
	public ref class WinMain : public MetroFramework::Forms::MetroForm
	{
	private: System::Windows::Forms::Timer^  timer1;

	private: System::Windows::Forms::RichTextBox^  rtPlayerlist;
	private: System::Windows::Forms::RichTextBox^  rtSpells;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::RichTextBox^  rtAttackStatus;
	private: System::Windows::Forms::TabPage^  tabPage4;


	private: System::Windows::Forms::RichTextBox^  rtDamageDone;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::RichTextBox^  rtAttack;

	private: System::Windows::Forms::PictureBox^  pbMain;

	public:
		BarHandler^ bh = gcnew BarHandler();
	private: MetroFramework::Controls::MetroTabControl^  tcBars;
	private: System::Windows::Forms::TabPage^  tpDamageDone;
	private: System::Windows::Forms::TabPage^  tpDps;
	public:

	private: System::Windows::Forms::TabPage^  tpHeal;

	private: MetroFramework::Controls::MetroPanel^  metroPanel1;
	private: MetroFramework::Controls::MetroScrollBar^  metroScrollBar1;
	private: System::Windows::Forms::Button^  btnHome;
	private: System::Windows::Forms::Button^  btnSettings;
	private: MetroFramework::Controls::MetroTabControl^  tcMain;

	private: MetroFramework::Controls::MetroTabPage^  tpMain;
	private: MetroFramework::Controls::MetroTabPage^  tpSettings;
	private: MetroFramework::Controls::MetroComboBox^  cbDevices;
	private: System::Windows::Forms::Button^  button2;
	private: MetroFramework::Controls::MetroLabel^  lblDevice;


	public:
		WinMain(void)
		{
			InitializeComponent();
			bh->setPictureBox(pbMain);
			bh->setScrollBar(metroScrollBar1);
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~WinMain()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  button1;
	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WinMain::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->rtPlayerlist = (gcnew System::Windows::Forms::RichTextBox());
			this->rtSpells = (gcnew System::Windows::Forms::RichTextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->rtAttackStatus = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->rtAttack = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->rtDamageDone = (gcnew System::Windows::Forms::RichTextBox());
			this->pbMain = (gcnew System::Windows::Forms::PictureBox());
			this->tcBars = (gcnew MetroFramework::Controls::MetroTabControl());
			this->tpDamageDone = (gcnew System::Windows::Forms::TabPage());
			this->tpDps = (gcnew System::Windows::Forms::TabPage());
			this->tpHeal = (gcnew System::Windows::Forms::TabPage());
			this->metroPanel1 = (gcnew MetroFramework::Controls::MetroPanel());
			this->metroScrollBar1 = (gcnew MetroFramework::Controls::MetroScrollBar());
			this->btnHome = (gcnew System::Windows::Forms::Button());
			this->btnSettings = (gcnew System::Windows::Forms::Button());
			this->tcMain = (gcnew MetroFramework::Controls::MetroTabControl());
			this->tpMain = (gcnew MetroFramework::Controls::MetroTabPage());
			this->tpSettings = (gcnew MetroFramework::Controls::MetroTabPage());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->lblDevice = (gcnew MetroFramework::Controls::MetroLabel());
			this->cbDevices = (gcnew MetroFramework::Controls::MetroComboBox());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMain))->BeginInit();
			this->tcBars->SuspendLayout();
			this->metroPanel1->SuspendLayout();
			this->tcMain->SuspendLayout();
			this->tpMain->SuspendLayout();
			this->tpSettings->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(-4, 49);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start Sniffer";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &WinMain::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 300;
			this->timer1->Tick += gcnew System::EventHandler(this, &WinMain::timer1_Tick);
			// 
			// rtPlayerlist
			// 
			this->rtPlayerlist->Location = System::Drawing::Point(6, 3);
			this->rtPlayerlist->Name = L"rtPlayerlist";
			this->rtPlayerlist->Size = System::Drawing::Size(505, 296);
			this->rtPlayerlist->TabIndex = 5;
			this->rtPlayerlist->Text = L"";
			// 
			// rtSpells
			// 
			this->rtSpells->Location = System::Drawing::Point(6, 6);
			this->rtSpells->Name = L"rtSpells";
			this->rtSpells->Size = System::Drawing::Size(651, 380);
			this->rtSpells->TabIndex = 6;
			this->rtSpells->Text = L"";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(148, 270);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(122, 97);
			this->tabControl1->TabIndex = 7;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->rtPlayerlist);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(114, 71);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Playerlist";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->rtSpells);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(114, 71);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"CastSpellList";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->rtAttackStatus);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(114, 71);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"AttackStatusList";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// rtAttackStatus
			// 
			this->rtAttackStatus->Location = System::Drawing::Point(6, 6);
			this->rtAttackStatus->Name = L"rtAttackStatus";
			this->rtAttackStatus->Size = System::Drawing::Size(653, 380);
			this->rtAttackStatus->TabIndex = 7;
			this->rtAttackStatus->Text = L"";
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->rtAttack);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(114, 71);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"AttackList";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// rtAttack
			// 
			this->rtAttack->Location = System::Drawing::Point(3, 3);
			this->rtAttack->Name = L"rtAttack";
			this->rtAttack->Size = System::Drawing::Size(656, 368);
			this->rtAttack->TabIndex = 0;
			this->rtAttack->Text = L"";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->rtDamageDone);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(114, 71);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Damage Done";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// rtDamageDone
			// 
			this->rtDamageDone->Location = System::Drawing::Point(3, 3);
			this->rtDamageDone->Name = L"rtDamageDone";
			this->rtDamageDone->Size = System::Drawing::Size(209, 76);
			this->rtDamageDone->TabIndex = 0;
			this->rtDamageDone->Text = L"";
			// 
			// pbMain
			// 
			this->pbMain->BackColor = System::Drawing::Color::Transparent;
			this->pbMain->Location = System::Drawing::Point(3, 3);
			this->pbMain->Name = L"pbMain";
			this->pbMain->Size = System::Drawing::Size(342, 135);
			this->pbMain->TabIndex = 0;
			this->pbMain->TabStop = false;
			this->pbMain->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WinMain::pbMain_Paint);
			this->pbMain->DoubleClick += gcnew System::EventHandler(this, &WinMain::pbMain_DoubleClick);
			this->pbMain->MouseEnter += gcnew System::EventHandler(this, &WinMain::pbMain_MouseEnter);
			this->pbMain->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &WinMain::pbMain_MouseMove);
			// 
			// tcBars
			// 
			this->tcBars->Controls->Add(this->tpDamageDone);
			this->tcBars->Controls->Add(this->tpDps);
			this->tcBars->Controls->Add(this->tpHeal);
			this->tcBars->HotTrack = true;
			this->tcBars->Location = System::Drawing::Point(-6, -7);
			this->tcBars->Name = L"tcBars";
			this->tcBars->SelectedIndex = 0;
			this->tcBars->Size = System::Drawing::Size(356, 41);
			this->tcBars->Style = MetroFramework::MetroColorStyle::Green;
			this->tcBars->TabIndex = 9;
			this->tcBars->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tcBars->UseSelectable = true;
			this->tcBars->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &WinMain::tcBars_Selected);
			// 
			// tpDamageDone
			// 
			this->tpDamageDone->BackColor = System::Drawing::Color::Transparent;
			this->tpDamageDone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tpDamageDone->ForeColor = System::Drawing::Color::White;
			this->tpDamageDone->Location = System::Drawing::Point(4, 38);
			this->tpDamageDone->Name = L"tpDamageDone";
			this->tpDamageDone->Size = System::Drawing::Size(348, -1);
			this->tpDamageDone->TabIndex = 0;
			this->tpDamageDone->Text = L"Damage Done";
			// 
			// tpDps
			// 
			this->tpDps->Location = System::Drawing::Point(4, 38);
			this->tpDps->Name = L"tpDps";
			this->tpDps->Size = System::Drawing::Size(348, -1);
			this->tpDps->TabIndex = 1;
			this->tpDps->Text = L"DPS";
			// 
			// tpHeal
			// 
			this->tpHeal->Location = System::Drawing::Point(4, 38);
			this->tpHeal->Name = L"tpHeal";
			this->tpHeal->Size = System::Drawing::Size(348, -1);
			this->tpHeal->TabIndex = 2;
			this->tpHeal->Text = L"Heal";
			// 
			// metroPanel1
			// 
			this->metroPanel1->Controls->Add(this->pbMain);
			this->metroPanel1->HorizontalScrollbarBarColor = false;
			this->metroPanel1->HorizontalScrollbarHighlightOnWheel = false;
			this->metroPanel1->HorizontalScrollbarSize = 10;
			this->metroPanel1->Location = System::Drawing::Point(2, 41);
			this->metroPanel1->Name = L"metroPanel1";
			this->metroPanel1->Size = System::Drawing::Size(348, 316);
			this->metroPanel1->TabIndex = 10;
			this->metroPanel1->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->metroPanel1->UseStyleColors = true;
			this->metroPanel1->VerticalScrollbarBarColor = true;
			this->metroPanel1->VerticalScrollbarHighlightOnWheel = true;
			this->metroPanel1->VerticalScrollbarSize = 15;
			this->metroPanel1->MouseEnter += gcnew System::EventHandler(this, &WinMain::metroPanel1_MouseEnter);
			// 
			// metroScrollBar1
			// 
			this->metroScrollBar1->LargeChange = 10;
			this->metroScrollBar1->Location = System::Drawing::Point(353, 41);
			this->metroScrollBar1->Maximum = 100;
			this->metroScrollBar1->Minimum = 0;
			this->metroScrollBar1->MouseWheelBarPartitions = 10;
			this->metroScrollBar1->Name = L"metroScrollBar1";
			this->metroScrollBar1->Orientation = MetroFramework::Controls::MetroScrollOrientation::Vertical;
			this->metroScrollBar1->ScrollbarSize = 12;
			this->metroScrollBar1->Size = System::Drawing::Size(12, 316);
			this->metroScrollBar1->TabIndex = 11;
			this->metroScrollBar1->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->metroScrollBar1->UseBarColor = true;
			this->metroScrollBar1->UseSelectable = true;
			this->metroScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &WinMain::metroScrollBar1_Scroll);
			// 
			// btnHome
			// 
			this->btnHome->FlatAppearance->BorderSize = 0;
			this->btnHome->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnHome->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnHome.Image")));
			this->btnHome->Location = System::Drawing::Point(24, 15);
			this->btnHome->Name = L"btnHome";
			this->btnHome->Size = System::Drawing::Size(36, 36);
			this->btnHome->TabIndex = 12;
			this->btnHome->UseVisualStyleBackColor = true;
			this->btnHome->Click += gcnew System::EventHandler(this, &WinMain::btnHome_Click);
			// 
			// btnSettings
			// 
			this->btnSettings->FlatAppearance->BorderSize = 0;
			this->btnSettings->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSettings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSettings.Image")));
			this->btnSettings->Location = System::Drawing::Point(70, 15);
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(36, 36);
			this->btnSettings->TabIndex = 13;
			this->btnSettings->UseVisualStyleBackColor = true;
			this->btnSettings->Click += gcnew System::EventHandler(this, &WinMain::btnSettings_Click);
			// 
			// tcMain
			// 
			this->tcMain->CausesValidation = false;
			this->tcMain->Controls->Add(this->tpMain);
			this->tcMain->Controls->Add(this->tpSettings);
			this->tcMain->Location = System::Drawing::Point(13, 22);
			this->tcMain->Name = L"tcMain";
			this->tcMain->SelectedIndex = 1;
			this->tcMain->Size = System::Drawing::Size(368, 413);
			this->tcMain->TabIndex = 14;
			this->tcMain->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tcMain->UseSelectable = true;
			this->tcMain->UseStyleColors = true;
			// 
			// tpMain
			// 
			this->tpMain->BackColor = System::Drawing::Color::Transparent;
			this->tpMain->Controls->Add(this->tcBars);
			this->tpMain->Controls->Add(this->metroScrollBar1);
			this->tpMain->Controls->Add(this->metroPanel1);
			this->tpMain->HorizontalScrollbarBarColor = true;
			this->tpMain->HorizontalScrollbarHighlightOnWheel = false;
			this->tpMain->HorizontalScrollbarSize = 10;
			this->tpMain->Location = System::Drawing::Point(4, 38);
			this->tpMain->Name = L"tpMain";
			this->tpMain->Size = System::Drawing::Size(360, 371);
			this->tpMain->TabIndex = 0;
			this->tpMain->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tpMain->VerticalScrollbarBarColor = true;
			this->tpMain->VerticalScrollbarHighlightOnWheel = false;
			this->tpMain->VerticalScrollbarSize = 10;
			// 
			// tpSettings
			// 
			this->tpSettings->BackColor = System::Drawing::Color::Transparent;
			this->tpSettings->Controls->Add(this->button2);
			this->tpSettings->Controls->Add(this->lblDevice);
			this->tpSettings->Controls->Add(this->tabControl1);
			this->tpSettings->Controls->Add(this->cbDevices);
			this->tpSettings->Controls->Add(this->button1);
			this->tpSettings->HorizontalScrollbarBarColor = true;
			this->tpSettings->HorizontalScrollbarHighlightOnWheel = false;
			this->tpSettings->HorizontalScrollbarSize = 10;
			this->tpSettings->Location = System::Drawing::Point(4, 38);
			this->tpSettings->Name = L"tpSettings";
			this->tpSettings->Size = System::Drawing::Size(360, 371);
			this->tpSettings->TabIndex = 1;
			this->tpSettings->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tpSettings->VerticalScrollbarBarColor = true;
			this->tpSettings->VerticalScrollbarHighlightOnWheel = false;
			this->tpSettings->VerticalScrollbarSize = 10;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(126, 134);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 15;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &WinMain::button2_Click);
			// 
			// lblDevice
			// 
			this->lblDevice->AutoSize = true;
			this->lblDevice->Location = System::Drawing::Point(3, 25);
			this->lblDevice->Name = L"lblDevice";
			this->lblDevice->Size = System::Drawing::Size(103, 19);
			this->lblDevice->TabIndex = 9;
			this->lblDevice->Text = L"Network Device:";
			this->lblDevice->Theme = MetroFramework::MetroThemeStyle::Dark;
			// 
			// cbDevices
			// 
			this->cbDevices->FormattingEnabled = true;
			this->cbDevices->ItemHeight = 23;
			this->cbDevices->Location = System::Drawing::Point(117, 20);
			this->cbDevices->Name = L"cbDevices";
			this->cbDevices->Size = System::Drawing::Size(237, 29);
			this->cbDevices->Style = MetroFramework::MetroColorStyle::Green;
			this->cbDevices->TabIndex = 8;
			this->cbDevices->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->cbDevices->UseSelectable = true;
			// 
			// WinMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(393, 450);
			this->Controls->Add(this->btnSettings);
			this->Controls->Add(this->btnHome);
			this->Controls->Add(this->tcMain);
			this->Name = L"WinMain";
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &WinMain::WinMain_FormClosing);
			this->Load += gcnew System::EventHandler(this, &WinMain::WinMain_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage5->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMain))->EndInit();
			this->tcBars->ResumeLayout(false);
			this->metroPanel1->ResumeLayout(false);
			this->tcMain->ResumeLayout(false);
			this->tpMain->ResumeLayout(false);
			this->tpSettings->ResumeLayout(false);
			this->tpSettings->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void WinMain_Load(System::Object^  sender, System::EventArgs^  e) {
		System::Collections::Generic::List<NetDevice^>^ devices = NetDevice::getDevices();
		for (int i = 0; i < devices->Count; i++) {
			cbDevices->Items->Add(devices[i]);
		}
		if (cbDevices->Items->Count > 0) cbDevices->SelectedIndex = 0;
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (cbDevices->SelectedItem == nullptr ) {
			MessageBoxA(NULL, "Please select a network interface", "Hadis Error", 0);
			return;
		}
		NetDevice^ netdev = (NetDevice^)cbDevices->SelectedItem;	
		start(netdev->ip);
	}


private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	bh->clear();
	std::vector<PlayerStatInfo>* pdd;

	if (tcBars->SelectedIndex == 0) {
		pdd = getPlayerStatInfo(0, PlayerStatInfo::PlayerStatInfoType::Damage);
	}
	else if (tcBars->SelectedIndex == 2) {
		pdd = getPlayerStatInfo(0, PlayerStatInfo::PlayerStatInfoType::Heal);
	}
	else if (tcBars->SelectedIndex == 1) {
		pdd = getPlayerStatInfo(0, PlayerStatInfo::PlayerStatInfoType::Dps);
	}

	for (size_t i = 0; i < pdd->size(); i++) {
		System::String^ lefttext = gcnew System::String((*pdd)[i].player.c_str());
		lefttext = (i + 1) + ". " + lefttext;
		System::String^ righttext = (*pdd)[i].value.ToString();
		righttext = righttext + " (" + (*pdd)[i].percentage.ToString() + "%)";
		bh->add(lefttext, righttext, (*pdd)[i].playerid,(*pdd)[i].percentage, (*pdd)[i].classid);
	}

	pbMain->Invalidate();


}

private: System::Void WinMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	
}


private: System::Void pbMain_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	MetroFramework::Controls::MetroPanel^ p = metroPanel1;	
	bh->draw(e->Graphics);
	metroScrollBar1->Maximum = pbMain->Height - metroPanel1->Height + 15;
}

private: System::Void metroScrollBar1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
	metroPanel1->VerticalScroll->Value = metroScrollBar1->Value;
}
private: System::Void metroPanel1_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	metroScrollBar1->Focus();
}
private: System::Void pbMain_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	metroScrollBar1->Focus();
}
private: System::Void btnHome_Click(System::Object^  sender, System::EventArgs^  e) {
	tcMain->SelectedIndex = 0;
}
private: System::Void btnSettings_Click(System::Object^  sender, System::EventArgs^  e) {
	tcMain->SelectedIndex = 1;
}

private: System::Void tcBars_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e) {
	timer1_Tick(nullptr, nullptr);
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	bh->add("Test", "Hallo",123, 50, 3);
	bh->add("Test", "Hallo", 3434, 25, 2);
	pbMain->Invalidate();
}

private: System::Void pbMain_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	MouseEventArgs^ mouseargs = dynamic_cast<MouseEventArgs^>(e);
	if (mouseargs == nullptr) return; //Event arguments are not a mouse event
	System::Windows::Forms::MessageBox::Show(bh->getIdByPixel(mouseargs->X, mouseargs->Y).ToString());

}

private: System::Void pbMain_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	MouseEventArgs^ mouseargs = dynamic_cast<MouseEventArgs^>(e);
	if (mouseargs == nullptr) return; //Event arguments are not a mouse event
	//System::Windows::Forms::MessageBox::Show(bh->getIdByPixel(mouseargs->X, mouseargs->Y).ToString());
	if (bh->getIdByPixel(mouseargs->X, mouseargs->Y) != 0)
		pbMain->Cursor = System::Windows::Forms::Cursors::Hand;
	else
		pbMain->Cursor = System::Windows::Forms::Cursors::Arrow;
}
};
}
