#ifndef UTEXTEDIT_H
#define UTEXTEDIT_H

#include "uwidget.h" // Base class: uWidget

class uTextEdit : public uWidget {

public:
	uTextEdit();
	~uTextEdit();

	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int x, int y, int button);

private:
	bool editing;
};

#endif // UTEXTEDIT_H
