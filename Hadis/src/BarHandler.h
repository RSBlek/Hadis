#pragma once


ref class Bar {
public:
	System::String^ leftText;
	System::String^ righttext;
	short percent;
	unsigned long long id;
	unsigned char classid;
public:
	Bar(System::String^ left, System::String^ right, unsigned long long id,short percent,unsigned char classid) {
		this->leftText = left;
		this->righttext = right;
		this->percent = percent;
		this->classid = classid;
		this->id = id;
	}
};

public ref class BarHandler {
private:
	const short barspace = 5;
	const short barheight = 20;
	System::Drawing::StringFormat^ stringright;
	System::Drawing::StringFormat^ stringleft;
	System::Windows::Forms::PictureBox^ pb;
	MetroFramework::Controls::MetroScrollBar^ sb;
	System::Collections::Generic::List<Bar^>^ bars = gcnew System::Collections::Generic::List<Bar^>();
	System::Drawing::Font^ f = gcnew System::Drawing::Font("Calibri", 11);
	long long getClassColor(unsigned char classid);
public:
	void setPictureBox(System::Windows::Forms::PictureBox^ pb);
	void setScrollBar(MetroFramework::Controls::MetroScrollBar^ sb) { this->sb = sb; }
	void add(System::String^ left, System::String^ right, unsigned long long id,short percent, unsigned char classid);
	void draw(System::Drawing::Graphics^ g);
	void clear();
	unsigned long long getIdByPixel(int x, int y);
	BarHandler();
	
};