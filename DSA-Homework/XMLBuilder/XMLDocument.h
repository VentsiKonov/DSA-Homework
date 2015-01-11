#pragma once
#include "List.h"
#include "Queue.h"
#include <string>
using std::string;
typedef std::pair < string, string > Attr;
#include <fstream>
class XMLDocument {
public:
	XMLDocument();
	XMLDocument(const char* name, const char* value = nullptr);

	class Iterator {
	private:
		Queue<XMLDocument*> queue;

	public:
		Iterator(XMLDocument* first);
		Iterator operator++(int);
		Iterator& operator++();
		Iterator& operator+=(size_t n);
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		XMLDocument& operator*() const;
	};
	
	XMLDocument& addTag(const char* tagName, const char* value = nullptr);
	XMLDocument& removeTag(const char* tagName);
	const char* getValue() const;
	const char* getTagName() const;
	void setValue(const char* value);

	XMLDocument& addAttribute(const char* attributeName, const char* attributeValue);
	XMLDocument& removeAttribute(const char* attributeName);
	const char* getAttrValue(const char* attributeName);
	XMLDocument& setAttribute(const char* attributeName, const char* attributeValue);

	//XMLDocument& find(const char* path, size_t length, char delimiter);
	List<XMLDocument*> find(const char* path, size_t length, char delimiter);
	
	void print(std::ostream& out, bool formatted = true, size_t offset = 0);
	
	Iterator begin();
	Iterator end() const;

private:
	string name;
	string value;
	List<XMLDocument> children;
	List<Attr> attributes;

	List<string> parsePath(const char* path, size_t length, char delimiter);
};

// Next thing - iterator