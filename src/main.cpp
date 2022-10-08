// MIT License
//
// Copyright (c) 2022 Aaron Robinson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>
#include <ctime>

auto get_timestamp() -> std::string
{
    auto t = std::time(nullptr);
    auto tm = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(tm, "%F-%T");
    return oss.str();
}

auto create_file() -> std::ofstream
{
    std::ostringstream oss;
    oss << "record-" << get_timestamp() << ".txt";
    auto output_file = oss.str();

    std::ofstream output(output_file, std::ios::out);
    std::cout << "New record file created: " << output_file << std::endl;
    return output;
}

auto main() -> int
{
    std::cout <<
R"**(=============================
    QRCode email recorder
=============================
)**" << std::endl;

    auto output = create_file();
    std::regex const match_email("<.+>");
    std::string input;
    for (;;)
    {
        // Read in the line from the scanner.
        // Example QRCode email format is: "Aaron Robinson" <linuxuser27@gmail.com>\n
        std::getline(std::cin, input);
        if (input.empty())
            break;

        // Match the email value. Format is: "NAME" <EMAIL>\n
        std::smatch m;
        if (!std::regex_search(input, m, match_email))
            continue;

        // Verify the captured email is at least 2 in length - delimited by <>.
        auto email_maybe = m[0];
        if (email_maybe.length() <= 2)
            continue;

        // Extract the email itself.
        auto email = email_maybe.str();
        email = email.substr(1, email.length() - 2);
        std::cout << "[[" << email << "]]" << std::endl;

        if (!output)
            output = create_file();

        // Write out the email to file.
        // One line per email.
        output << email << std::endl;
    }

    return EXIT_SUCCESS;
}