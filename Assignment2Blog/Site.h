// Name: Kevin Kan
// Date: July 17 2015
// Class: Site
// Purpose: Handles the site creation and blog managmement.
#include<string>
#include<iomanip>
#include<iostream>
#include<Blog.h>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

#ifndef SITE
#define SITE
#endif
struct configFile{
	string type;
	string value;
};


class Site
{
private:
	string siteName;
	vector<Blog> blogList;
	vector<string> cssUrlList, jsUrlList;

public:
	Site();
	void setName(string name){
		if (name!=""){
			siteName = name;
			saveConfig();
		}
	};
	void addCss(string newCssUrl){
		cssUrlList.push_back('"'+newCssUrl+'"');
		saveConfig();
	}
	void addJs(string newJsUrl){
		jsUrlList.push_back('"' + newJsUrl + '"');
		saveConfig();
	}
	void removeConfigUrl(string urlToRemove){
		string removetemp = '"' + urlToRemove + '"';
		cssUrlList.erase(remove(cssUrlList.begin(), cssUrlList.end(), removetemp), cssUrlList.end());
		jsUrlList.erase(remove(jsUrlList.begin(), jsUrlList.end(), removetemp), jsUrlList.end());
		saveConfig();
	}
	void saveConfig(){
		fstream saveConfig("site-config.txt", ios::out);
		if (saveConfig){
			saveConfig << "name " + siteName << endl;
			for (int i = 0; i < cssUrlList.size(); i++)
			{
				saveConfig << "style " + cssUrlList[i]<<endl;
			}
			for (int i = 0; i < jsUrlList.size(); i++)
			{
				saveConfig << "script " + jsUrlList[i]<<endl;
			}
		}
		else{
			cout <<endl << "Error Could not save to config file!!" << endl;
		}
	}
	void addBlog(){
		Blog newBlog;
		string name, author;
		cout << "Please enter Blog name" << endl;
		getline(cin, name);
		cout << "Please enter Blog Author" << endl;
		getline(cin, author);
		newBlog.createNew(name,author,name+".txt");
		blogList.push_back(newBlog);
		saveBlogList();
	}
	void seeBlogList()
	{
		cout << endl<<endl << "Blog List:" << endl<<endl;
		for (int i = 0; i < blogList.size(); i++){
			cout << blogList[i].getName()<< endl;
		}
		cout << endl;
	}
	void viewBlog(string blogTitle){// find and display a blog with the given title
		bool found = false;
		for (int i = 0; i < blogList.size()&&found==false; i++){
			if (blogTitle == blogList[i].getName())
			{
				cout << blogList[i].getName() << endl;
				blogList[i].getContent();
				found = true;
			}
		}
		if (!found){
			cout << "Could not find blog : " << blogTitle << endl<<endl;
		}
	}
	void deleteBlog(string blogtitle){//delete a blog from the list and remove it from the blog list file
		for (int i = 0; i < blogList.size(); i++){
			if (blogtitle == blogList[i].getName())
			{
				blogList.erase(blogList.begin() + i);
			}
		}
		saveBlogList();
	}
	void saveBlogList(){//save the blogs and create the html for them
		fstream saveBlog("blog-index.txt", ios::out);
		if (saveBlog){
			for (int i = 0; i < blogList.size(); i++)
			{
				saveBlog << '"' + blogList[i].getName() + '"' + " " + '"' + blogList[i].getAuthor() + '"' + " " + '"' 
					+ blogList[i].getDate() + '"' + " "+'"' + blogList[i].getLocation() + '"' + " "  << endl;
				blogList[i].createHtml();
			}
		}
		else{
			cout << endl << "Error Could not save to blog-index.txt file!!" << endl;
		}
	}
	void createIndexPage()
	{
		fstream indexPage("html/index.html", ios::out);
		if (indexPage){
			indexPage << "<!DOCTYPE html> \n <html> <head><meta charset = 'utf-8' > <title>" + siteName + "</title>"<<endl;
			for (int i = 0; i < cssUrlList.size(); i++){
				string stripedUrl = cssUrlList[i];
				stripedUrl.erase(stripedUrl.begin());
				stripedUrl.erase(stripedUrl.end()-1);
				indexPage << "<link rel='stylesheet' href='css/" + stripedUrl + "'>" << endl;
				ofstream checkCss;
				checkCss.open("css/" + stripedUrl);
				if (checkCss.bad()){//if css file does not exist create one
					cout << "nofile creating one" << endl;
					checkCss.open("css/" + stripedUrl, ios_base::out);
					cin.get();
				}
				checkCss.close();
			}
			for (int i = 0; i < jsUrlList.size(); i++){
				string stripedUrl = jsUrlList[i];
				stripedUrl.erase(stripedUrl.begin());
				stripedUrl.erase(stripedUrl.end() - 1);
				indexPage << "<script type='text/javascript' src='scripts/" + stripedUrl + "'></script>" << endl;
				ofstream checkJS;
				checkJS.open("css/" + stripedUrl);
				if (checkJS.bad()){//if javascript file doesn't exist create one
					cout << "nofile creating one" << endl;
					checkJS.open("css/" + stripedUrl, ios_base::out);
					cin.get();
				}
				checkJS.close();
			}
			indexPage << "</head>" << endl;
			indexPage << " \n <body> <h1>" + siteName + "</h1>" << endl;
			for (int i = 0; i < blogList.size(); i++)
			{
				indexPage << "<a href='"+blogList[i].getName()+".html'>"+ blogList[i].getName() + "</a>"<< endl;
			}
			indexPage << "</body></html>" << endl;
		}
		else{
			cout << endl << "Error Could not save to index.html file!!" << endl;
		}
	}
	;

};

Site::Site()
{
	configFile newFile;
	char ch;
	//read site config
	fstream siteConfig("site-config.txt", ios::in);
	if (siteConfig){
		while ((ch = siteConfig.peek()) != EOF){
			siteConfig >> newFile.type;
			siteConfig >> ws;
			getline(siteConfig, newFile.value);
			/*cout << setw(20) << newFile.type << setw(20) << newFile.value << endl;*/
			if (newFile.type=="name"){
				siteName = newFile.value;
			}
			else if (newFile.type == "style"){
				cssUrlList.push_back(newFile.value);
			}
			else if (newFile.type == "script"){
				jsUrlList.push_back(newFile.value);
			}
		}
		siteConfig.close();
	}
	
	//read the blogs
	fstream blogIndex("blog-index.txt", ios::in);
	if (blogIndex){
		string tempRead,parsed;
		Blog newBlog;
		while ((ch = blogIndex.peek()) != EOF){
			
			getline(blogIndex, tempRead);
			stringstream newStream(tempRead);
			
			getline(newStream, parsed, '"');//parse out the space
			getline(newStream, parsed, '"');//parse out the text in quotes
			newBlog.setName(parsed);//set the blog name

			getline(newStream, parsed, '"');
			getline(newStream, parsed, '"');
			newBlog.setAuthor(parsed);//set the author

			getline(newStream, parsed, '"');
			getline(newStream, parsed, '"');
			newBlog.setDate(parsed);//set the date

			getline(newStream, parsed, '"');
			getline(newStream, parsed, '"');
			newBlog.setLocation(parsed);//set the location of the file

			blogList.push_back(newBlog);

			//newBlog.getContent();// get the blog content
		}
		/*for (int i = 0; i < blogList.size(); i++)
		{
			cout << "BlogName" << blogList[i].getName() << endl;
		}*/
		blogIndex.close();
	}
	
}
