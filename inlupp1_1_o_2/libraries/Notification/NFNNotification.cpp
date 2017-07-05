#include <string>
//#include "Windows.h"
//#include "Winuser.h"
#include "NFNNotification.h"



/* NFNNotification */

/* Public creators */
NFNNotification::NFNNotification(const std::string &title, const std::string &text) :
	mTitle(title),
	mText(text){
}


NFNNotification::NFNNotification(const NFNNotification &notification) :
	mTitle(notification.mTitle),
	mText(notification.mText){
}

NFNNotification::~NFNNotification(){
	mTitle = "";
	mText  = "";
}

/* Public manipulators */
NFNNotification& NFNNotification::operator=(const NFNNotification &notification){
	mTitle = notification.mTitle;
	mText  = notification.mText;
	return *this;
}

void NFNNotification::setText(const std::string &text){
	mText = text;
}

void NFNNotification::setTitle(const std::string &title){
	mTitle = title;
}

/* Public accessors */
void  NFNNotification::display() const{
	// We don't need to display anything
	//MessageBox(NULL, mText.c_str(), mTitle.c_str(), MB_OK | MB_SETFOREGROUND);
}

const std::string& NFNNotification::getText() const{
	return mText;
}

const std::string& NFNNotification::getTitle() const{
	return mTitle;
}

/* Public functions */
void NFNNotification::notify(const std::string &title, const std::string &text){
	NFNNotification notification(title, text);
	notification.display();
}
