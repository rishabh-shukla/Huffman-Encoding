#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <map>

using namespace std;
map <string, char> mymap;
map <string, char> :: iterator it;
struct MinHeapNode
{
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;

    if (root->data != '$')
        {
            cout << root->data << ": " << str << "\n";
            mymap[str]=root->data;
        }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;


    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i){
        minHeap.push(new MinHeapNode(data[i], freq[i]));

}

    while (minHeap.size() != 1)
    {

        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }


    printCodes(minHeap.top(), "");
}


int main()
{
    char arr[100] ;
    int freq[100] ;
    int num=52;
    char c;
    string str;
    int f;
    cout<<"HUFFMAN ENCODING\n^^^^^^^^^^^^^^^^\n";
    //cout<<"Enter Total Number of Characters you want : ";
    //cin>> num;
    ifstream infile;
    infile.open("Character_Frequency.dat");
    for(int i=0;i<num;i++){
        infile >>c;
        infile >> f;
        arr[i]=c;
        freq[i]=f;
    }
    infile.close();
    cout<<"\nCodes for the characters have been generated according to their frequency in \nEnglish Language\nfrom Character_Frequency.dat\n";
    cout<<"\nHuffmann Codes for following Characters are : \n"<<endl;
    HuffmanCodes(arr, freq, num);
    //Huffman codes have been encoded
    ofstream outfile;
    outfile.open("Code_Assignment.dat");
    for (it=mymap.begin(); it!=mymap.end(); ++it)
    outfile << it->second<<"->"<<it->first<< endl;
    outfile.close();
    cout<<"\nCodes have been stored into Code_Assignment.dat\n";

    infile.open("Text.dat");
    outfile.open("Encoded_Message.dat");
    while(infile >> noskipws >>c)
    {
        //infile>>c;
        if((c-'a'>=0 && c-'a'<=25 ) || (c-'A'>=0 && c-'A'<=25))
            {
                for(it=mymap.begin();it!=mymap.end();++it)
                    if(it->second==c)
                        outfile<<it->first;

            }
            else outfile <<c;
    }
    outfile.close();
    infile.close();
    cout<<"\nMessage has been read from Text.dat and encoded into Encoded_Message.dat\n";
    //Message has been encoded


    cout<<"\nNow the decoding will start. \n";
   // getline(cin,str);
    infile.open("Encoded_Message.dat");
    while(infile>>noskipws>>c)
        str=str+c;
    //cout<<str;
    string t,ans,sp;

     t = "";
    ans = "";
    for( int i = 0; i < str.size(); i++ ) {
            while(str[i]!='0' && str[i]!='1' && i+1<str.size())
                {
                    if(str[i]=='\n')
                        sp+=" \n ";
                    else{
                    sp+=str[i];}
                    i++;
                }
        t += " ";
        ans="";
        t[t.size()-1] = str[i];
        it = mymap.find(t);
        if( it != mymap.end() ) {
            c = mymap[t];
            ans += " ";
            ans[ans.size()-1] = c;
            sp+=ans;
            t = "";
            while(str[i+1]!='0' && str[i+1]!='1' && i+1<str.size())
                {
                    if(str[i+1]=='\n')
                        sp+=" \n ";
                    else{
                    sp+=str[i+1];}
                    i++;
                }
            }
        }

    cout <<"\nDecoded message (stored in Decoded_Message.dat) -> \n\n"<< sp << endl<<endl;
    outfile.open("Decoded_Message.dat");
    outfile << sp<< endl;
    outfile.close();


    return 0;
}
