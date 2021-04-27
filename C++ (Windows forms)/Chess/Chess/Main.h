#pragma once

#include "play.h"
#include <msclr\marshal_cppstd.h>

namespace Chess {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	public ref class Main : public System::Windows::Forms::Form {
	public:
		msclr::interop::marshal_context context;
		string* path1 = new string("W.csv");
		string* path2 = new string("W.csv");
		string* rating_from_file = new string("0");
	private: System::ComponentModel::BackgroundWorker^ worker;
	private: System::Windows::Forms::Label^ log;
	private: System::Windows::Forms::CheckBox^ train_in_game;
	private: System::Windows::Forms::NumericUpDown^ count;

	public:
		String^ rating_str = System::IO::File::ReadAllText("rating.chess");
	private: System::Windows::Forms::Label^ info;




	public:
		int rating_int = System::Convert::ToInt32(rating_str);
	public:
		Main(void) {
			srand(time(NULL));
			InitializeComponent();
			rating->Text = "Ваш рейтинг: " + rating_str;
		}

	protected:
		~Main() {
			if (components) {
				delete components;
				delete path1;
				delete path2;
				delete rating_from_file;
				delete rating_str;
			}
		}
	private: System::Windows::Forms::Button^ start;
	private: System::Windows::Forms::Button^ ai;
	private: System::Windows::Forms::Label^ rating;
	private: System::Windows::Forms::Button^ train;
	private: System::Windows::Forms::OpenFileDialog^ select;
	private: System::Windows::Forms::Button^ select_play_ai;
	private: System::Windows::Forms::Button^ select_train_ai;
	public: System::Windows::Forms::ProgressBar^ progress;
	private: System::ComponentModel::IContainer^ components;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->start = (gcnew System::Windows::Forms::Button());
			this->ai = (gcnew System::Windows::Forms::Button());
			this->rating = (gcnew System::Windows::Forms::Label());
			this->train = (gcnew System::Windows::Forms::Button());
			this->select = (gcnew System::Windows::Forms::OpenFileDialog());
			this->select_play_ai = (gcnew System::Windows::Forms::Button());
			this->select_train_ai = (gcnew System::Windows::Forms::Button());
			this->progress = (gcnew System::Windows::Forms::ProgressBar());
			this->count = (gcnew System::Windows::Forms::NumericUpDown());
			this->worker = (gcnew System::ComponentModel::BackgroundWorker());
			this->log = (gcnew System::Windows::Forms::Label());
			this->train_in_game = (gcnew System::Windows::Forms::CheckBox());
			this->info = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->count))->BeginInit();
			this->SuspendLayout();
			// 
			// start
			// 
			this->start->Cursor = System::Windows::Forms::Cursors::Hand;
			this->start->Location = System::Drawing::Point(154, 117);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(198, 48);
			this->start->TabIndex = 1;
			this->start->Text = L"Играть на двоих";
			this->start->UseVisualStyleBackColor = true;
			this->start->Click += gcnew System::EventHandler(this, &Main::play_Click);
			// 
			// ai
			// 
			this->ai->Cursor = System::Windows::Forms::Cursors::Hand;
			this->ai->Location = System::Drawing::Point(154, 180);
			this->ai->Name = L"ai";
			this->ai->Size = System::Drawing::Size(198, 48);
			this->ai->TabIndex = 2;
			this->ai->Text = L"Играть против ИИ";
			this->ai->UseVisualStyleBackColor = true;
			this->ai->Click += gcnew System::EventHandler(this, &Main::ai_Click);
			// 
			// rating
			// 
			this->rating->AutoSize = true;
			this->rating->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rating->Location = System::Drawing::Point(118, 54);
			this->rating->Name = L"rating";
			this->rating->Size = System::Drawing::Size(246, 38);
			this->rating->TabIndex = 3;
			this->rating->Text = L"Ваш рейтинг: 0";
			// 
			// train
			// 
			this->train->Cursor = System::Windows::Forms::Cursors::Hand;
			this->train->Location = System::Drawing::Point(154, 243);
			this->train->Name = L"train";
			this->train->Size = System::Drawing::Size(198, 48);
			this->train->TabIndex = 4;
			this->train->Text = L"Начать обучение";
			this->train->UseVisualStyleBackColor = true;
			this->train->Click += gcnew System::EventHandler(this, &Main::train_Click);
			// 
			// select
			// 
			this->select->FileName = L"W.csv";
			this->select->InitialDirectory = L"D:\\Catalog\\Projects\\MachineLearning\\Chess\\C++\\Chess\\Chess\\weights\\";
			this->select->RestoreDirectory = true;
			this->select->ShowHelp = true;
			// 
			// select_play_ai
			// 
			this->select_play_ai->Location = System::Drawing::Point(67, 193);
			this->select_play_ai->Name = L"select_play_ai";
			this->select_play_ai->Size = System::Drawing::Size(81, 23);
			this->select_play_ai->TabIndex = 5;
			this->select_play_ai->Text = L"W.csv";
			this->select_play_ai->UseVisualStyleBackColor = true;
			this->select_play_ai->Click += gcnew System::EventHandler(this, &Main::select_play_ai_Click);
			// 
			// select_train_ai
			// 
			this->select_train_ai->Location = System::Drawing::Point(67, 256);
			this->select_train_ai->Name = L"select_train_ai";
			this->select_train_ai->Size = System::Drawing::Size(81, 23);
			this->select_train_ai->TabIndex = 6;
			this->select_train_ai->Text = L"W.csv";
			this->select_train_ai->UseVisualStyleBackColor = true;
			this->select_train_ai->Click += gcnew System::EventHandler(this, &Main::select_train_ai_Click);
			// 
			// progress
			// 
			this->progress->BackColor = System::Drawing::Color::WhiteSmoke;
			this->progress->Location = System::Drawing::Point(154, 297);
			this->progress->Maximum = 1000;
			this->progress->Name = L"progress";
			this->progress->Size = System::Drawing::Size(198, 23);
			this->progress->Step = 1;
			this->progress->TabIndex = 7;
			this->progress->UseWaitCursor = true;
			// 
			// count
			// 
			this->count->Location = System::Drawing::Point(367, 257);
			this->count->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->count->Name = L"count";
			this->count->Size = System::Drawing::Size(61, 22);
			this->count->TabIndex = 8;
			this->count->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// worker
			// 
			this->worker->WorkerSupportsCancellation = true;
			this->worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Main::worker_DoWork);
			this->worker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Main::worker_ProgressChanged);
			this->worker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Main::worker_RunWorkerCompleted);
			// 
			// log
			// 
			this->log->Location = System::Drawing::Point(122, 345);
			this->log->Name = L"log";
			this->log->Size = System::Drawing::Size(228, 50);
			this->log->TabIndex = 9;
			this->log->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// train_in_game
			// 
			this->train_in_game->Location = System::Drawing::Point(367, 181);
			this->train_in_game->Name = L"train_in_game";
			this->train_in_game->Size = System::Drawing::Size(125, 48);
			this->train_in_game->TabIndex = 10;
			this->train_in_game->Text = L"обучаться во время игры";
			this->train_in_game->UseVisualStyleBackColor = true;
			// 
			// info
			// 
			this->info->Location = System::Drawing::Point(37, 345);
			this->info->Name = L"info";
			this->info->Size = System::Drawing::Size(417, 104);
			this->info->TabIndex = 11;
			this->info->Text = resources->GetString(L"info.Text");
			this->info->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(516, 495);
			this->Controls->Add(this->info);
			this->Controls->Add(this->train_in_game);
			this->Controls->Add(this->log);
			this->Controls->Add(this->count);
			this->Controls->Add(this->progress);
			this->Controls->Add(this->select_train_ai);
			this->Controls->Add(this->select_play_ai);
			this->Controls->Add(this->train);
			this->Controls->Add(this->rating);
			this->Controls->Add(this->ai);
			this->Controls->Add(this->start);
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Шахматы";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->count))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void rating_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Main_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: void rating_update() {
		rating_str = System::IO::File::ReadAllText("rating.chess");
		rating_int = System::Convert::ToInt32(rating_str);
	}
	private: System::Void play_Click(System::Object^ sender, System::EventArgs^ e) {
		rating_update();
		play^ pl = gcnew play(this, 0, true, *path1, this->progress, false, rating_int, rating);
		pl->Show();
		this->Hide();
	}
	private: System::Void ai_Click(System::Object^ sender, System::EventArgs^ e) {
		bool white = true;
		int ran = rand() % 2;
		if (ran == 1) white = false;
		rating_update();
		play^ pl = gcnew play(this, 1, white, *path1, this->progress, this->train_in_game->Checked, rating_int, rating);
		pl->Show();
		this->Hide();
	}
private: System::Void select_play_ai_Click(System::Object^ sender, System::EventArgs^ e) {
	if (select->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		*path1 = context.marshal_as<string>(System::IO::Path::GetFileName(select->FileName));
		select_play_ai->Text = System::IO::Path::GetFileName(select->FileName);
	}
}
private: System::Void select_train_ai_Click(System::Object^ sender, System::EventArgs^ e) {
	if (select->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		*path2 = context.marshal_as<string>(System::IO::Path::GetFileName(select->FileName));
		select_train_ai->Text = System::IO::Path::GetFileName(select->FileName);
	}
}
private: System::Void train_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!worker->IsBusy) {
		progress->Value = 0;
		int c = (int)count->Value;
		progress->Maximum = c;
		log->Text = "Обучение запущено";
		rating_update();
		play^ pl = gcnew play(this, 2, true, *path2, this->progress, true, rating_int, rating);
		pl->Show();
		worker->RunWorkerAsync(1);
	}
	else {
		log->Text = "Обучение запущено\n";
		log->Text += "Обучение ещё не законечно!";
	}
}
private: System::Void worker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	while (true) {
		if (worker->CancellationPending) {
			e->Cancel = true;
			break;
		}
		if (progress->Value == progress->Maximum) {
			break;
		}
		Sleep(1000);
	}
	worker->CancelAsync();
}
private: System::Void worker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
	progress->Value += e->ProgressPercentage;
}
private: System::Void worker_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
	log->Text = "Готово";
}
};
}
