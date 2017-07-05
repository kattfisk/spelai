#ifndef INCLUDED_NFNNOTIFICATION
#define INCLUDED_NFNNOTIFICATION



/******************************************************************************

This component implements a type that can be used to notify the user. The
program continues when the user acknowledges the notification.

*******************************************************************************/



#include <string>



class NFNNotification{
public:

	/* Public creators */
	NFNNotification(const std::string &title = "", const std::string &text = "");
	NFNNotification(const NFNNotification &notification);
	~NFNNotification();

	/* Public manipulators */
	NFNNotification& operator=(const NFNNotification &notification);
	void setText(const std::string &text);
	void setTitle(const std::string &title);

	/* Public accessors */
	void               display()  const;
	const std::string& getText()  const;
	const std::string& getTitle() const;

	/* Public functions */
	static void notify(const std::string &title = "", const std::string &text = "");

private:

	/* Private data */
	std::string mTitle;
	std::string mText;
};

#endif