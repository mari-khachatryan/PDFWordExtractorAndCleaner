#include <iostream>
#include <fstream>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>

void readFromPdf(const std::string& pathPDF, const std::string& pathFile) {  //str format: "path/to/your/pdf/file.pdf"
	poppler-document pdf_doc(pathPDF);
	std::ofstream outputFile(pathFile);
	if(!outputFile.is_open()) {
		std::cout << "Unable to open the file for writing" << std::endl;
	}

	if(!pdf_doc.is_valid()) {
		std::cout << "Ivolid PDF document" << std::endl;
		return 1;
	}
	int num_pages = pdf_doc.get_page_count();

	for(int i = 0; i < num_pages; ++i) {
		const poppler::page& pdf_page = pdf_doc.create_page(i);
		std::string page_text = pdf_page.get_text().to_string();
		outputFile << page_text;
	}
}	

std::vector<std::string> split(const std::string& str, char ch) {
    std::vector<std::string> newV = {};
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < str.size()) {
        newV.push_back("");
        while (j < str.size()) {
            if (str[j] != ch) {
                newV[i] += str[j];
                ++j;
            } else {
                break;
            }
        }
        ++i;
        ++j; 
    }
    return newV;
}

std::vector<std::string> cleanWords(const std::vector<std::string>& source ) {
    std::vector<std::string> result = {};
    for(int i{0}; i < source.size(); i++) {
        std::string word{};
        for(char c : source[i]) {
            if(std::islower(c))
                word.push_back(c);
            else if(std::isupper(c))
                word.push_back(std::tolower(c));
        }
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        result.push_back(word);
    }
    return result;
}

bool binarySearch(const std::vector<std::string>& words,const std::string& target) {
    int left = 0;
    int right = words.size() - 1;

    while(left <= right) {
        int mid = left + (right - left)/2;
        if(words[mid] == target) {
            return true; //or mid;
        } else if(words[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

std::string shortenedString(const std::string& str) {
    if (!str.empty()) {
        std::string shortenedString = str.substr(0, str.length() - 1);
        return shortenedString;
    }
    return "";
}

std::vector<std::string> normalizeWord(const std::string& path, const std::vector<std::string>& words) {
    std::vector<std::string> dic = readDataFromFile(path);
    std::vector<std::string> normlizeMyVector = {};
    for(std::string word : words) {
        if(binarySearch(dic, word)) {
            normlizeMyVector.push_back(word);
        } else {
            word = shortenedString(word);
            if(binarySearch(dic, word)) {
                normlizeMyVector.push_back(word);
            }
        }
    }
    return normlizeMyVector;
}

int main() {
	readFromPdf("file.pdf", "file.txt");


	return 0;
}