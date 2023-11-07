#pragma once

namespace pp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::IO;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ openButton;
    private: System::Windows::Forms::TextBox^ outputTextBox;
    private: System::Windows::Forms::TextBox^ outputTextBox1;
    private: System::Windows::Forms::TextBox^ outputTextBox2;


    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->openButton = (gcnew System::Windows::Forms::Button());
               this->outputTextBox = (gcnew System::Windows::Forms::TextBox());
               this->outputTextBox1 = (gcnew System::Windows::Forms::TextBox());
               this->outputTextBox2 = (gcnew System::Windows::Forms::TextBox());
               this->SuspendLayout();
               // 
               // openButton
               // 
               this->openButton->Location = System::Drawing::Point(12, 12);
               this->openButton->Name = L"openButton";
               this->openButton->Size = System::Drawing::Size(121, 23);
               this->openButton->TabIndex = 0;
               this->openButton->Text = L"Open Files";
               this->openButton->UseVisualStyleBackColor = true;
               this->openButton->Click += gcnew System::EventHandler(this, &MyForm::openButton_Click);
               // 
               // outputTextBox
               // 
               this->outputTextBox->Location = System::Drawing::Point(12, 41);
               this->outputTextBox->Multiline = true;
               this->outputTextBox->Name = L"outputTextBox";
               this->outputTextBox->Size = System::Drawing::Size(341, 356);
               this->outputTextBox->TabIndex = 1;
               this->outputTextBox->TextChanged += gcnew System::EventHandler(this, &MyForm::outputTextBox_TextChanged);
               // 
               // outputTextBox1
               // 
               this->outputTextBox1->Location = System::Drawing::Point(359, 41);
               this->outputTextBox1->Multiline = true;
               this->outputTextBox1->Name = L"outputTextBox1";
               this->outputTextBox1->Size = System::Drawing::Size(393, 356);
               this->outputTextBox1->TabIndex = 2;
               this->outputTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
               // 
               // outputTextBox2
               // 
               this->outputTextBox2->Location = System::Drawing::Point(758, 41);
               this->outputTextBox2->Multiline = true;
               this->outputTextBox2->Name = L"outputTextBox2";
               this->outputTextBox2->Size = System::Drawing::Size(345, 356);
               this->outputTextBox2->TabIndex = 3;
               // 
               // MyForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(1115, 409);
               this->Controls->Add(this->outputTextBox2);
               this->Controls->Add(this->outputTextBox1);
               this->Controls->Add(this->outputTextBox);
               this->Controls->Add(this->openButton);
               this->Name = L"MyForm";
               this->Text = L"File Comparison";
               this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private:
        System::Void openButton_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void outputTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}
