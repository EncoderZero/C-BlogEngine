#include<Windows.h>
#include<ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// Name: Kevin Kan
// Date: Aug 8 2015
// Class: Blog
// Purpose: Handles the Blog post functionality.
class Blog
{
private:
	string blogName, author, dateCreated,location="";
	SYSTEMTIME time;

public:
	Blog();
	void setName(string name){
		blogName = name;
	};
	string getName(){
		return blogName;
	}
	void setAuthor(string authorName){
		author = authorName;
	};
	string getAuthor(){
		return author;
	}
	void setContent(){
		string input="";
		fstream writeBlog(location, ios::out);
		if (writeBlog){
			cout << "Please type '-end' on a new line to stop typing the blog's content." << endl;
			do{
				getline(cin,input);
				if (input != "-end"){
					writeBlog << input << endl;
				}
			} while (input != "-end");
		}
		
	};
	void getContent(){
		fstream blogIndex(location, ios::in);
		if (blogIndex){//if there is a location file location
			string tempRead, parsed;
			Blog newBlog;
			int ch;
			cout <<endl<< "Blog File Contains:" << endl;
			while ((ch = blogIndex.peek()) != EOF){
				getline(blogIndex, tempRead);
				cout << tempRead<<endl;
			}
			blogIndex.close();
		}
		else{
			cout << "ERROR READING FILE " << location << endl;
		}
	}
	void setLocation(string contentLocation){
		location = contentLocation;
	};
	string getLocation(){
		return location;
	}
	void setDate(string date){
		dateCreated = date;
	};
	string getDate(){
		return dateCreated;
	}
	void createNew(string name, string authorName, string contentLocation){
		setName(name);
		setAuthor(authorName);
		setLocation(contentLocation);
		setContent();
		
		//time function modified from https://www.youtube.com/watch?v=Z_qHEWXUxnE

		GetLocalTime(&time);
		char buffer[256];
		sprintf_s(buffer,
			"%d-%02d-%02d %02d:%02d:%02d.%03d",
			time.wYear,
			time.wMonth,
			time.wDay,
			time.wHour,
			time.wMinute,
			time.wSecond,
			time.wMilliseconds);
		
		string dt = buffer;
		cout << "The local date and time is: " << dt << endl;
		//end of modified time code
		dateCreated = dt;
		createHtml();
		

	}
	void createHtml(){
		fstream writeBlog("html/" + blogName + ".html", ios::out);
		if (writeBlog){
			writeBlog << "<!DOCTYPE html> \n <html> <head><meta charset = 'utf-8' > <title>" + blogName + "</title></head>" << endl;
			writeBlog << " \n <body> <h1>" + blogName + "</h1>" << endl;
			writeBlog << "<pre>" << endl;
			fstream blogIndex(location, ios::in);
			if (blogIndex){//if there is a location file location
				string tempRead, parsed;
				Blog newBlog;
				int ch;
				while ((ch = blogIndex.peek()) != EOF){
					getline(blogIndex, tempRead);
					writeBlog << tempRead << endl;
				}
				blogIndex.close();
			}
			else{
				cout << "ERROR READING FILE " << location << endl;
			}
			writeBlog << "</pre></body></html>" << endl;
		}
		else{
			cout << "could not create file" << endl;
		}
	}
	;

};

Blog::Blog()
{
	
}

