#pragma once

#include <msclr/marshal_cppstd.h>


namespace BaseComputerSoftware {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	static std::string fileName, currentPath, newFolder;

	/// <summary>
	/// Summary for Files_Transfer
	/// </summary>
	public ref class Files_Transfer : public System::Windows::Forms::Form
	{
	public:
		Files_Transfer(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Files_Transfer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1182, 659);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Piotr Bejenka";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->Location = System::Drawing::Point(490, 100);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(300, 69);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Select File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Files_Transfer::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->Location = System::Drawing::Point(490, 200);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(300, 69);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Select New Directory";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Files_Transfer::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->Location = System::Drawing::Point(490, 300);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(300, 69);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Move File";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Files_Transfer::button3_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button4->Location = System::Drawing::Point(12, 623);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(150, 46);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Back";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Files_Transfer::button4_Click);
			// 
			// Files_Transfer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"Files_Transfer";
			this->Text = L"Files_Transfer";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ FileToMove = gcnew OpenFileDialog();
		//FileToMove->Multiselect = true;
		//FileToMove->InitialDirectory = "F:\\";

		if (FileToMove->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}

		msclr::interop::marshal_context context;
		currentPath = context.marshal_as<std::string>(FileToMove->FileName);
		fileName = context.marshal_as<std::string>(FileToMove->SafeFileName);
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		FolderBrowserDialog^ Folder = gcnew FolderBrowserDialog();
		//Folder->SelectedPath = "C:\\Users\\User8\\Desktop\\opr\\opr\\nagrania";

		if (Folder->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}

		msclr::interop::marshal_context context;
		newFolder = context.marshal_as<std::string>(Folder->SelectedPath);
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		const char *ch_curr_P = currentPath.c_str();
		std::string newPath = newFolder + "\\" + fileName;
		const char *ch_new_P = newPath.c_str();

		if (rename(ch_curr_P, ch_new_P))
			MessageBox::Show("The process has failed.");
		else
			MessageBox::Show("The file has been successfully moved.");
	}

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		Close();
	}
};
}
