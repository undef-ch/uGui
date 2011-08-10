#include "utextedit.h"

uTextEdit::uTextEdit()
{
	width = 100;
	height = 20;
}

uTextEdit::~uTextEdit()
{
}

void uTextEdit::draw()
{
	ofRect(x, y, width, height);
}
void uTextEdit::keyPressed(int key)
{
}

void uTextEdit::mousePressed(int x, int y, int button)
{
}

void uTextEdit::mouseReleased(int x, int y, int button)
{
}

