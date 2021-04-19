#pragma once

#include "opencv2/opencv.hpp"
#include <msclr/marshal_cppstd.h>


namespace BaseComputerSoftware {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace std;
	using namespace cv;

	static std::string File_To_Process;

	/// <summary>
	/// Summary for Analytical_Software
	/// </summary>
	public ref class Analytical_Software : public System::Windows::Forms::Form
	{
	public:
		Analytical_Software(void)
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
		~Analytical_Software()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
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
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(196, 20);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1056, 594);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->Location = System::Drawing::Point(12, 50);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(165, 50);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Select File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Analytical_Software::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->Location = System::Drawing::Point(12, 150);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(165, 50);
			this->button2->TabIndex = 3;
			this->button2->Text = L"START";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Analytical_Software::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->Location = System::Drawing::Point(12, 623);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(150, 46);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Back";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Analytical_Software::button3_Click);
			// 
			// Analytical_Software
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Name = L"Analytical_Software";
			this->Text = L"Analytical_Software";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ File = gcnew OpenFileDialog();

		if (File->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}

		msclr::interop::marshal_context context;
		File_To_Process = context.marshal_as<std::string>(File->FileName);
	}



	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		if(File_To_Process.substr(File_To_Process.find_last_of(".") + 1) != "mp4")
		{
			MessageBox::Show("Invalid file format! \n\nThe .mp4 file is required.");
			return;
		}

		const char *chFile_To_Process = File_To_Process.c_str();
		VideoCapture vid(chFile_To_Process);

		while (vid.isOpened())
		{
			Mat b_img, p_img;
			vid >> b_img;

			if (b_img.empty())
				break;

			cvtColor(b_img, p_img, COLOR_BGR2GRAY);

			GaussianBlur(p_img, p_img, cv::Size2i::Size_(7, 7), 0);

			threshold(p_img, p_img, 100, 255, THRESH_BINARY);

			bitwise_not(p_img, p_img);

			vector<vector<cv::Point> > contours;
			vector<Vec4i> hierarchy;

			findContours(p_img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);

			for (int i = 0; i < contours.size(); i++)
			{
				drawContours(b_img, contours, i, Scalar(0, 100, 255), 1, 8, hierarchy, 0, cv::Point2i::Point_());

				RotatedRect minRect = minAreaRect(Mat(contours[i]));

				Point2f rect_points[4];
				minRect.points(rect_points);

				Point2f p0, p1, p2, p3;
				p0 = rect_points[0];
				p1 = rect_points[1];
				p2 = rect_points[2];
				p3 = rect_points[3];

				float r_min[4];
				for (int j = 0; j < 4; j++)
				{
					r_min[j] = abs(sqrt((b_img.size().width / 2 - rect_points[j].x)*(b_img.size().width / 2 - rect_points[j].x) +
						(b_img.size().height / 2 - rect_points[j].y)*(b_img.size().height / 2 - rect_points[j].y)));
				}

				if ((min_element(r_min, r_min + 4) == &r_min[0] || min_element(r_min, r_min + 4) == &r_min[1]) && minRect.size.width > minRect.size.height)
				{
					rect_points[0] = p3;
					rect_points[1] = p0;
					rect_points[2] = p1;
					rect_points[3] = p2;
				}
				if ((min_element(r_min, r_min + 4) == &r_min[0] || min_element(r_min, r_min + 4) == &r_min[3]) && minRect.size.width < minRect.size.height)
				{
					rect_points[0] = p2;
					rect_points[1] = p3;
					rect_points[2] = p0;
					rect_points[3] = p1;
				}
				if ((min_element(r_min, r_min + 4) == &r_min[1] || min_element(r_min, r_min + 4) == &r_min[2]) && minRect.size.width < minRect.size.height)
				{
					rect_points[0] = p0;
					rect_points[1] = p1;
					rect_points[2] = p2;
					rect_points[3] = p3;
				}
				if ((min_element(r_min, r_min + 4) == &r_min[2] || min_element(r_min, r_min + 4) == &r_min[3]) && minRect.size.width > minRect.size.height)
				{
					rect_points[0] = p1;
					rect_points[1] = p2;
					rect_points[2] = p3;
					rect_points[3] = p0;
				}

				/*
				float O[4], S[4];	//	O - distances of the extreme points of the rectangular contour of the real object from the camera in mm
									//	S - distances of the outline points from the center of the frame in pixels
				float F = 3.04;	//	F - focal length	(rpi cam v2 focal length equals 3.04 mm)
				float D = 100;	//	D - diameter	(diameter of the pipeline from which the recording comes)
				float R = D/2;	//	R - radius

				for (int j = 0; j < 4; j++)
				{
					S[j] = sqrt((b_img.size().width / 2 - rect_points[j].x)*(b_img.size().width / 2 - rect_points[j].x) + (b_img.size().height / 2 - rect_points[j].y)*(b_img.size().height / 2 - rect_points[j].y));
					O[j] = (R * F) / S[j];
				}

				float L = sqrt((O[1] - O[0])*(O[1] - O[0]) + (rect_points[0].y - rect_points[1].y)*(rect_points[0].y - rect_points[1].y));
				float W = sqrt((O[3] - O[0])*(O[3] - O[0]) + (rect_points[3].y - rect_points[0].y)*(rect_points[3].y - rect_points[0].y));								

				std::string width = std::to_string(W);
				std::string length = std::to_string(L);

				putText(b_img, " width: " + width, Point2f(rect_points[1].x - 20, rect_points[1].y + 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0));
				putText(b_img, "length: " + length, Point2f(rect_points[1].x - 20, rect_points[1].y + 50), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0));
				*/

				circle(b_img, Point2f(b_img.size().width / 2, b_img.size().height / 2), 1, Scalar(255, 255, 255), 2);
				circle(b_img, rect_points[0], 2, Scalar(255, 0, 0), 2);
				circle(b_img, rect_points[1], 2, Scalar(0, 255, 0), 2);
				circle(b_img, rect_points[3], 2, Scalar(0, 0, 255), 2);

				for (int j = 0; j < 4; j++)
				{
					line(b_img, rect_points[j], rect_points[(j + 1) % 4], Scalar(255, 255, 0), 1);
				}
			}


			System::Drawing::Graphics^ graphics = pictureBox1->CreateGraphics();
			System::IntPtr ptr(b_img.ptr());
			System::Drawing::Bitmap^ bm = gcnew System::Drawing::Bitmap(b_img.cols, b_img.rows, b_img.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
			System::Drawing::RectangleF rectf(0, 0, pictureBox1->Width, pictureBox1->Height);
			graphics->DrawImage(bm, rectf);

			waitKey(33);
		}

		vid.release();

		MessageBox::Show("The visual inspection has been completed.");
	}
	


	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		Close();
	}
};
}
