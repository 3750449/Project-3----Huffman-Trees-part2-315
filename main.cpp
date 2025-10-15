#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "Scanner.hpp"
#include "utils.hpp"

#include <iomanip> // for .freq
#include "BinSearchTree.hpp"
#include "PriorityQueue.hpp"
#include <algorithm> // for sort() --

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";


    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
        exitOnError(status, inputFileName);


    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);


    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.

    auto fileToWords = Scanner(tokensFilePath);
    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
	    exitOnError(status, inputFileName);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);


    //part 2 stuff

    //Build BST
    WordBinSearchTree bst;
    bst.bulkInsert(words);

    std::vector<std::pair<std::string,int>> countsLex;
    bst.inorderCollect(countsLex);

    //create placeholders and find BST values
    unsigned height = bst.height();
    std::size_t unique = bst.size();
    std::size_t total  = words.size();
    int minFreq = 0;
    int maxFreq = 0;

    if (!countsLex.empty()) {

        minFreq = maxFreq = countsLex.front().second;

        for (auto& [w,c] : countsLex) {

            if (c < minFreq)
                minFreq = c;

            if (c > maxFreq)
                maxFreq = c;

        }

    }

    //Print values
    std::cout << "BST height: "       << (countsLex.empty()?0:height) << '\n'
              << "BST unique words: " << (countsLex.empty()?0:unique) << '\n'
              << "Total tokens: "     << total                        << '\n'
              << "Min frequency: "    << (countsLex.empty()?0:minFreq)<< '\n'
              << "Max frequency: "    << (countsLex.empty()?0:maxFreq)<< '\n';

    //Sort and write .freq
    auto freqPath = dirName + "/" + inputFileBaseName + ".freq";
    auto sorted = countsLex;

    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b){

                  if (a.second != b.second)
                      return a.second > b.second;

        return a.first < b.first;
    });

    std::ofstream freqOut(freqPath);

    if (!freqOut)
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, freqPath);

    for (auto& [w,c] : sorted) {

        freqOut << std::setw(10) << c << ' ' << w << '\n';

        if (!freqOut)
            exitOnError(FAILED_TO_WRITE_FILE, freqPath);

    }

    return 0;
}
