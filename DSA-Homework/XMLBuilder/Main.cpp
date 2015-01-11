#include <iostream>
#include "XMLDocument.h"
int main() {
	XMLDocument doc("asd", "sdf");
	doc.addTag("tag1").addAttribute("attr1", "val").addTag("tag").addAttribute("innerAttr", "val").addTag("tag4");
	doc.addTag("tag1", "tag2val").addTag("tag");

	char path[] = "asd/tag1/tag";
	List<XMLDocument*> a = doc.find(path, strlen(path), '/');
	doc.removeTag("tag2");
	doc.print(std::cout, true);
	std::cout << "\n";
	XMLDocument::Iterator i = doc.begin();
	while (i != doc.end()) {
		std::cout << (*i).getTagName() << "\n";
		++i;
	}

	return 0;
}