#include "XMLDocument.h"

XMLDocument::XMLDocument() {
	name = "root";
}

XMLDocument::XMLDocument(const char* name, const char* value) {
	this->name = name;
	if (value != nullptr) {
		this->value = value;
	}
}

void XMLDocument::print(std::ostream& out, bool formatted, size_t offset) {
	if (formatted)
		for (size_t i = 0; i < offset; i++) {
			out << " ";
		}
	out << "<" << name;

	if (!attributes.IsEmpty())
		for (List<Attr>::Iterator i = attributes.Begin(); i != attributes.End(); ++i) {
			out << " " << (*i).first << "=\"" << (*i).second << "\"";
		}

	if (children.IsEmpty() && value.empty()) {
		out << "/>" << (formatted ? "\n" : "");
		return;
	}

	out << ">" << (formatted ? "\n" : "");
	if (!value.empty() && formatted) {
		for (size_t i = 0; i < offset + 1; i++) {
			out << " ";
		}
		out << value << "\n";
	}
	for (List<XMLDocument>::Iterator i = children.Begin(); i != children.End(); ++i) {
		(*i).print(out, formatted, offset + 1);
	}
	
	if(formatted)
		for (size_t i = 0; i < offset; i++) {
		out << " ";
		}
	out << "</" << name << ">" << (formatted ? "\n" : "");
}

XMLDocument& XMLDocument::addTag(const char* tagName, const char* tagValue) {
	children.PushBack(XMLDocument(tagName, tagValue));
	return children.Back();
}

XMLDocument& XMLDocument::addAttribute(const char* attrName, const char* attrVal) {
	attributes.PushBack(Attr(attrName, attrVal));
	return *this;
}

XMLDocument& XMLDocument::removeAttribute(const char* attrName) {
	List<Attr>::Iterator i = attributes.Begin();
	for (size_t index = 0; i != attributes.End(); ++i, ++index) {
		if ((*i).first.compare(attrName) == 0) {
			attributes.PopAt(index); // Potentially slow
			break;
		}
	}
	return *this;
}

const char* XMLDocument::getValue() const{
	return value.c_str();
}

const char* XMLDocument::getAttrValue(const char* attributeName) {
	for (List<Attr>::Iterator i = attributes.Begin(); i != attributes.End(); ++i) {
		if ((*i).first.compare(attributeName) == 0) {
			return (*i).second.c_str();
		}
	}
	return nullptr;
}

XMLDocument& XMLDocument::setAttribute(const char* attributeName, const char* attributeValue) {
	for (List<Attr>::Iterator i = attributes.Begin(); i != attributes.End(); ++i) {
		if ((*i).first.compare(attributeName) == 0) {
			(*i).second = attributeValue;
			return *this;
		}
	}

	addAttribute(attributeName, attributeValue);
	return *this;
}

void XMLDocument::setValue(const char* value) {
	this->value = value;
}

List<string> XMLDocument::parsePath(const char* path, size_t length, char delimiter) {
	string temp = "";
	List<string> returnValue;
	for (size_t i = 0; i < length; ++i) {
		if (path[i] == delimiter) {
			returnValue.PushBack(temp);
			temp = "";
		}
		else {
			temp += path[i];
		}
	}
	if (!temp.empty())
		returnValue.PushBack(temp);

	return returnValue;
}

// TODO : Make XMLDocumentProxy with all the functions wrapped to be able to edit multiple items too
List<XMLDocument*> XMLDocument::find(const char* path, size_t length, char delimiter) {
	List<XMLDocument*> returnValue;
	List<string> parsedPath = parsePath(path, length, delimiter);
	if (parsedPath.Front() == name) 
		parsedPath.PopFront();
	returnValue.PushFront(this);
	size_t frontSize;
	string current;
	XMLDocument* i;
	while (!parsedPath.IsEmpty()) {
		current = parsedPath.PopFront();
		frontSize = returnValue.Size();
		for (size_t elem = 0; elem < frontSize; ++elem) {
			i = returnValue.PopFront();
			for (List<XMLDocument>::Iterator child = i->children.Begin(); child != i->children.End(); ++child) {
				if ((*child).name == current) {
					returnValue.PushBack(&*child);
				}
			}
		}
	}
	return returnValue;
}

XMLDocument& XMLDocument::removeTag(const char* tagName) {
	List<XMLDocument>::Iterator i = children.Begin();
	for (size_t count = 0; i != children.End(); ++i, ++count) {
		if ((*i).name.compare(tagName) == 0) {
			children.PopAt(count);
			break;
		}
	}
	return *this;
}

const char* XMLDocument::getTagName() const {
	return this->name.c_str();
}

XMLDocument::Iterator::Iterator(XMLDocument* start) {
	if (start != nullptr)
		queue.Push(start);
}

XMLDocument::Iterator& XMLDocument::Iterator::operator++() {
	XMLDocument* current = queue.Pop();
	for (List<XMLDocument>::Iterator i = current->children.Begin(); i != current->children.End(); ++i) {
		queue.Push(&*i);
	}
	return *this;
}

XMLDocument::Iterator& XMLDocument::Iterator::operator+=(size_t n) {
	while (n > 0) {
		++(*this);
		--n;
	}

	return *this;
}

bool XMLDocument::Iterator::operator==(const XMLDocument::Iterator& other) const{
	return (queue.Size() == other.queue.Size() && (queue.Size() == 0 || queue.Peek() == other.queue.Peek()));
}

bool XMLDocument::Iterator::operator!=(const XMLDocument::Iterator& other) const {
	return !(*this == other);
}

XMLDocument& XMLDocument::Iterator::operator*() const{
	return *queue.Peek();
}

XMLDocument::Iterator XMLDocument::begin() {
	return Iterator(this);
}

XMLDocument::Iterator XMLDocument::end() const {
	return Iterator(nullptr);
}

XMLDocument::Iterator XMLDocument::Iterator::operator++(int) {
	Iterator returnValue = Iterator(*this);
	++(*this);
	return returnValue;
}