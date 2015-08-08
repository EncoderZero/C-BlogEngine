#include<Site.h>
#include<ctime>
using namespace std;

void keyCommands()
{
	cout << "Please enter one of the following commands:"<<endl; 
	cout << "help - displays this command list." << endl;
	cout << "compile - to complie the data to html format and end the program." << endl;
	cout << "newCss - to add a new css file to the html structure." << endl;
	cout << "newJs - to add a new javascript file to the html structure." << endl;
	cout << "removeScript - to remove a new css or javascript file from the html structure." << endl;
	cout << "addBlog - to add a new blog entry." << endl;
	cout << "listBlog - to view a list of blog titles" << endl;
	cout << "deleteBlog - to open the delete menu" << endl<<endl;
}

int main()
{
	Site newSite;
	string input,comand;
	cout << "***************************************************" << endl;
	cout << "            Welcome to Blog Engine" << endl;
	cout << "***************************************************" << endl<<endl;
	//newSite.addBlog();
	while (comand != "compile"){
		cout << "Please enter a command, type help to see a list of commands." << endl;
		cin >> ws;
		getline(cin, comand);
		if (comand == "siteName"){
			cout << "Please enter the site name." << endl;
			getline(cin, input);
			newSite.setName(input);
		}
		else if (comand == "newCss"){
			cout << "Please enter the new Css file name to be added in the styles folder." << endl;
			getline(cin, input);
			newSite.addCss(input);
		}
		else if (comand == "newJs"){
			cout << "Please enter the new JavaScript file name to be added in the scripts folder." << endl;
			getline(cin, input);
			newSite.addJs(input);
		}
		else if (comand == "removeScript"){
			cout << "Please enter the Css or JavaScript file location you wish to remove." << endl;
			getline(cin, input);
			newSite.removeConfigUrl(input);
		}
		else if (comand == "addBlog"){
			newSite.addBlog();
		}
		else if (comand == "listBlog")
		{
			newSite.seeBlogList();
		}
		else if (comand == "deleteBlog")
		{
			cout << "Please enter a blog name to delete." << endl;
			getline(cin, input);
			newSite.deleteBlog(input);
		}
		else if (comand == "viewBlog"){
			cout << "Please enter a blog name to view." << endl;
			getline(cin, input);
			newSite.viewBlog(input);

		}
		else if (comand == "compile"){
			cout << "thank you, good bye" << endl;
		}
		else if (comand == "help"){
			keyCommands();
		}
		else{
			cout << "Sorry, but :" << comand << " is not a recognized command." << endl;
			keyCommands();
		}

	}
	
	newSite.saveConfig();
	newSite.createIndexPage();
	cout << "Press any key to exit..." << endl;
	cin.ignore();
	cin.get();
	return 0;
}