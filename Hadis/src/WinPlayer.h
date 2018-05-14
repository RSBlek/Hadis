#pragma once
#include "stdafx.h"
#include "BarHandler.h"

using namespace System::Runtime::InteropServices;

namespace Hadis {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;


	/// <summary>
	/// Zusammenfassung für WinPlayer
	/// </summary>
	public ref class WinPlayer : public MetroFramework::Forms::MetroForm
	{
















	private: System::Windows::Forms::PictureBox^  pbMain;

	public:
		BarHandler ^ bh = gcnew BarHandler();



	public:



	private: MetroFramework::Controls::MetroPanel^  metroPanel1;
	private: MetroFramework::Controls::MetroScrollBar^  metroScrollBar1;




	private: MetroFramework::Controls::MetroTabControl^  tcMain;
	private: MetroFramework::Controls::MetroTabPage^  tpSummary;
	private: MetroFramework::Controls::MetroTabPage^  tpDetails;









	public:
		WinPlayer(int x, int y)
		{
			InitializeComponent();
			bh->setPictureBox(pbMain);
			bh->setScrollBar(metroScrollBar1);
			
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~WinPlayer()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::ComponentModel::IContainer^  components;


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
			this->pbMain = (gcnew System::Windows::Forms::PictureBox());
			this->metroPanel1 = (gcnew MetroFramework::Controls::MetroPanel());
			this->metroScrollBar1 = (gcnew MetroFramework::Controls::MetroScrollBar());
			this->tcMain = (gcnew MetroFramework::Controls::MetroTabControl());
			this->tpSummary = (gcnew MetroFramework::Controls::MetroTabPage());
			this->tpDetails = (gcnew MetroFramework::Controls::MetroTabPage());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMain))->BeginInit();
			this->metroPanel1->SuspendLayout();
			this->tcMain->SuspendLayout();
			this->tpSummary->SuspendLayout();
			this->SuspendLayout();
			// 
			// pbMain
			// 
			this->pbMain->BackColor = System::Drawing::Color::Transparent;
			this->pbMain->Location = System::Drawing::Point(3, 3);
			this->pbMain->Name = L"pbMain";
			this->pbMain->Size = System::Drawing::Size(342, 135);
			this->pbMain->TabIndex = 0;
			this->pbMain->TabStop = false;
			this->pbMain->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WinPlayer::pbMain_Paint);
			this->pbMain->DoubleClick += gcnew System::EventHandler(this, &WinPlayer::pbMain_DoubleClick);
			this->pbMain->MouseEnter += gcnew System::EventHandler(this, &WinPlayer::pbMain_MouseEnter);
			this->pbMain->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &WinPlayer::pbMain_MouseMove);
			// 
			// metroPanel1
			// 
			this->metroPanel1->Controls->Add(this->pbMain);
			this->metroPanel1->HorizontalScrollbarBarColor = false;
			this->metroPanel1->HorizontalScrollbarHighlightOnWheel = false;
			this->metroPanel1->HorizontalScrollbarSize = 10;
			this->metroPanel1->Location = System::Drawing::Point(1, 7);
			this->metroPanel1->Name = L"metroPanel1";
			this->metroPanel1->Size = System::Drawing::Size(348, 360);
			this->metroPanel1->TabIndex = 10;
			this->metroPanel1->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->metroPanel1->UseStyleColors = true;
			this->metroPanel1->VerticalScrollbarBarColor = true;
			this->metroPanel1->VerticalScrollbarHighlightOnWheel = true;
			this->metroPanel1->VerticalScrollbarSize = 15;
			this->metroPanel1->MouseEnter += gcnew System::EventHandler(this, &WinPlayer::metroPanel1_MouseEnter);
			// 
			// metroScrollBar1
			// 
			this->metroScrollBar1->LargeChange = 10;
			this->metroScrollBar1->Location = System::Drawing::Point(352, 7);
			this->metroScrollBar1->Maximum = 100;
			this->metroScrollBar1->Minimum = 0;
			this->metroScrollBar1->MouseWheelBarPartitions = 10;
			this->metroScrollBar1->Name = L"metroScrollBar1";
			this->metroScrollBar1->Orientation = MetroFramework::Controls::MetroScrollOrientation::Vertical;
			this->metroScrollBar1->ScrollbarSize = 12;
			this->metroScrollBar1->Size = System::Drawing::Size(12, 360);
			this->metroScrollBar1->TabIndex = 11;
			this->metroScrollBar1->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->metroScrollBar1->UseBarColor = true;
			this->metroScrollBar1->UseSelectable = true;
			this->metroScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &WinPlayer::metroScrollBar1_Scroll);
			// 
			// tcMain
			// 
			this->tcMain->CausesValidation = false;
			this->tcMain->Controls->Add(this->tpSummary);
			this->tcMain->Controls->Add(this->tpDetails);
			this->tcMain->FontWeight = MetroFramework::MetroTabControlWeight::Regular;
			this->tcMain->Location = System::Drawing::Point(13, 22);
			this->tcMain->Name = L"tcMain";
			this->tcMain->SelectedIndex = 0;
			this->tcMain->Size = System::Drawing::Size(368, 413);
			this->tcMain->Style = MetroFramework::MetroColorStyle::Green;
			this->tcMain->TabIndex = 14;
			this->tcMain->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tcMain->UseSelectable = true;
			// 
			// tpSummary
			// 
			this->tpSummary->BackColor = System::Drawing::Color::Transparent;
			this->tpSummary->Controls->Add(this->metroScrollBar1);
			this->tpSummary->Controls->Add(this->metroPanel1);
			this->tpSummary->ForeColor = System::Drawing::Color::Black;
			this->tpSummary->HorizontalScrollbarBarColor = true;
			this->tpSummary->HorizontalScrollbarHighlightOnWheel = false;
			this->tpSummary->HorizontalScrollbarSize = 10;
			this->tpSummary->Location = System::Drawing::Point(4, 38);
			this->tpSummary->Name = L"tpSummary";
			this->tpSummary->Size = System::Drawing::Size(360, 371);
			this->tpSummary->TabIndex = 0;
			this->tpSummary->Text = L"Summary";
			this->tpSummary->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tpSummary->VerticalScrollbarBarColor = true;
			this->tpSummary->VerticalScrollbarHighlightOnWheel = false;
			this->tpSummary->VerticalScrollbarSize = 10;
			// 
			// tpDetails
			// 
			this->tpDetails->BackColor = System::Drawing::Color::Transparent;
			this->tpDetails->HorizontalScrollbarBarColor = true;
			this->tpDetails->HorizontalScrollbarHighlightOnWheel = false;
			this->tpDetails->HorizontalScrollbarSize = 10;
			this->tpDetails->Location = System::Drawing::Point(4, 38);
			this->tpDetails->Name = L"tpDetails";
			this->tpDetails->Size = System::Drawing::Size(360, 371);
			this->tpDetails->TabIndex = 1;
			this->tpDetails->Text = L"Details";
			this->tpDetails->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->tpDetails->VerticalScrollbarBarColor = true;
			this->tpDetails->VerticalScrollbarHighlightOnWheel = false;
			this->tpDetails->VerticalScrollbarSize = 10;
			// 
			// WinPlayer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(393, 450);
			this->Controls->Add(this->tcMain);
			this->Name = L"WinPlayer";
			this->StartPosition = System::Windows::Forms::FormStartPosition::WindowsDefaultLocation;
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Theme = MetroFramework::MetroThemeStyle::Dark;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &WinPlayer::WinPlayer_FormClosing);
			this->Load += gcnew System::EventHandler(this, &WinPlayer::WinPlayer_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMain))->EndInit();
			this->metroPanel1->ResumeLayout(false);
			this->tcMain->ResumeLayout(false);
			this->tpSummary->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void WinPlayer_Load(System::Object^  sender, System::EventArgs^  e) {
		
	}

	private: System::Void WinPlayer_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

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

	private: System::Void pbMain_DoubleClick(System::Object^  sender, System::EventArgs^  e) {

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
