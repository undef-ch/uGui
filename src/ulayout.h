#ifndef ULAYOUT_H
#define ULAYOUT_H

#include "uutils.h"

class uLayout {

public:
	uLayout();
	~uLayout();
	void setWidget(uWidget* widget);

private:
	void onWidgetEvent(uWidgetEvent& e);

	uWidget* widget;
};

#endif // ULAYOUT_H
