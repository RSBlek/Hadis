#include "stdafx.h"
#include "BarHandler.h"

using namespace System::Drawing;

BarHandler::BarHandler() {
	stringright = gcnew System::Drawing::StringFormat();
	stringright->Alignment = System::Drawing::StringAlignment::Far;
	stringright->LineAlignment = System::Drawing::StringAlignment::Center;
	stringleft = gcnew System::Drawing::StringFormat();
	stringleft->Alignment = System::Drawing::StringAlignment::Near;
	stringleft->LineAlignment = System::Drawing::StringAlignment::Center;
}

void BarHandler::clear() {
	bars->Clear();
}

long long BarHandler::getClassColor(unsigned char classid) {
	if (classid == 0) //Warrior
		return 0xFF2983b3FF184593;
	else if (classid == 1) //Scout
		return 0xFF358254FF286340;
	else if (classid == 2) //Mage
		return 0xFF78499cFF6b418c;
	else if (classid == 3) //Priest
		return 0xFF838074FF696058;
	else if (classid == 4) //Engineer
		return 0xFF976b21FFa02e1d;
	else if (classid == 5) //Artist
		return 0xFF974587FF67365e;
	return 0;
}

void BarHandler::setPictureBox(System::Windows::Forms::PictureBox^ pb) {
	this->pb = pb;
}

void BarHandler::add(System::String^ left, System::String^ right, unsigned long long id,short percent,unsigned char classid) {
	Bar^ bar = gcnew Bar(left, right, id,percent, classid);
	bars->Add(bar);
}

unsigned long long BarHandler::getIdByPixel(int x, int y) {
	int currentY = 0;
	int currentBar = 0;
	while (currentY <= y) {
		if (y >= (currentY) && y <= (currentY + barheight)) {
			if (currentBar >= bars->Count) return 0;
			return bars[currentBar]->id;
		}
		currentY = currentY + barspace + barheight;
		currentBar++;
	}
	return 0;
}

void BarHandler::draw(System::Drawing::Graphics^ g) {
 	g->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;
	int pbheight = (bars->Count) * (barspace + barheight) + 1;
	pb->Height = pbheight;
	for (int i = 0; i < bars->Count; i++) {
		long long gradientcolors = getClassColor(bars[i]->classid);
		int topcolor = (gradientcolors & 0xFFFFFFFF00000000) >> 32;
		int botcolor = (gradientcolors & 0x00000000FFFFFFFF);
		int x = 0;
		int y = i * barspace + i * barheight;
		int width = pb->Width - 1;
		int height = barheight;

		System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);
		System::Drawing::Drawing2D::LinearGradientBrush^ rectbrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(rect, System::Drawing::Color::FromArgb(topcolor), System::Drawing::Color::FromArgb(botcolor), 90);
		System::Drawing::Rectangle fillrect = System::Drawing::Rectangle(x, y, (width * bars[i]->percent) / 100, height);
		g->FillRectangle(rectbrush, fillrect);
		Pen^ borderpen = gcnew Pen(System::Drawing::Color::FromArgb(botcolor));
		g->DrawRectangle(borderpen , rect);
		g->DrawString(bars[i]->leftText, f, MetroFramework::MetroBrushes::White , rect, stringleft);
		g->DrawString(bars[i]->righttext, f, MetroFramework::MetroBrushes::White, rect, stringright);
		delete rectbrush;

	}
}