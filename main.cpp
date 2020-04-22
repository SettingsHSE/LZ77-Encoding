#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Node
{
    int offset;
    int length;
    char next;

    Node(int of, int le, char ne)
    {
        offset = of;
        length = le;
        next = ne;
    }
};

std::vector<Node*> Encode(std::string s)
{
    std::vector<Node*> answer;

    const int buf_size = 3072;
    const int preview_size = 1024;

    int position = 0;

    while (position < s.length())
    {
        int max_index = 0, max_length = 0, cur_index, cur_length;
        for (int j = std::max(0, (position - buf_size)); j < position; j++)
        {
            cur_index = j, cur_length = 0;

            while (s[cur_index] == s[cur_length + position] && cur_index < std::min((position + preview_size), (int)s.length()))
            {
                cur_index++;
                cur_length++;
            }

            if (cur_length > max_length)
            {
                max_index = position - j;
                max_length = cur_length;
            }
        }

        position += max_length;
        answer.push_back(new Node(max_index, max_length, s[position]));
        position++;
    }

    return answer;
}

int main()
{
    std::fstream fin;
    fin.open("input.txt", std::ios::in);
    if(fin.is_open()) {
        std::string input;
        fin >> input;
        fin.close();

        std::vector<Node*> encoded = Encode(input);

        std::fstream fout;
        fout.open("output.txt", std::ios::out);
        fout << encoded.size() << "\n";
        for(auto & node : encoded)
        {
            fout << node->offset << " " << node->length << " " << node->next << " ";
        }
        fout.close();
    }

    return 0;
}