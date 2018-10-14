#pragma once


namespace Liegenschaftsbewertung
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary> 
	/// Zusammenfassung für Form1
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			InitializeComponent();
		}
  
	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::MenuItem *  File;
	private: System::Windows::Forms::MenuItem *  New;
	private: System::Windows::Forms::MenuItem *  Open;
	private: System::Windows::Forms::MenuItem *  Save;

	private: System::Windows::Forms::MenuItem *  Exit;
	private: System::Windows::Forms::MenuItem *  Close;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::Label *  label1;



	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container * components;

		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung. 
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->File = new System::Windows::Forms::MenuItem();
			this->New = new System::Windows::Forms::MenuItem();
			this->Open = new System::Windows::Forms::MenuItem();
			this->Save = new System::Windows::Forms::MenuItem();
			this->Close = new System::Windows::Forms::MenuItem();
			this->Exit = new System::Windows::Forms::MenuItem();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->label1 = new System::Windows::Forms::Label();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__1[0] = this->File;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			// 
			// File
			// 
			this->File->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__2[0] = this->New;
			__mcTemp__2[1] = this->Open;
			__mcTemp__2[2] = this->Save;
			__mcTemp__2[3] = this->Close;
			__mcTemp__2[4] = this->Exit;
			this->File->MenuItems->AddRange(__mcTemp__2);
			this->File->Text = S"Datei";
			// 
			// New
			// 
			this->New->Index = 0;
			this->New->Text = S"Neu";
			// 
			// Open
			// 
			this->Open->Index = 1;
			this->Open->Text = S"Öffnen";
			// 
			// Save
			// 
			this->Save->Index = 2;
			this->Save->Text = S"Speichern";
			// 
			// Close
			// 
			this->Close->Index = 3;
			this->Close->Text = S"Schliessen";
			// 
			// Exit
			// 
			this->Exit->Index = 4;
			this->Exit->Text = S"&Beenden";
			this->Exit->Click += new System::EventHandler(this, Exit_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(40, 24);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(656, 368);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(648, 342);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"tabPage1";
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(648, 342);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"tabPage2";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(32, 32);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(120, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = S"label1";
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(768, 445);
			this->Controls->Add(this->tabControl1);
			this->Menu = this->mainMenu1;
			this->Name = S"Form1";
			this->Text = S"Liegenschaftsbewertung";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->ResumeLayout(false);

		}	
	private: System::Void Exit_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 
				 if((int)Windows::Forms::MessageBox::Show("Wollen sie wirklich beenden?", "Beenden", Windows::Forms::MessageBoxButtons::YesNoCancel, Windows::Forms::MessageBoxIcon::Warning)==(int)Windows::Forms::DialogResult::Yes)
					 exit(0);
				 
			 }

	};
}


