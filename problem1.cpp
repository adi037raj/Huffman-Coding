/*
              AADITYA RAJ BARNWAL
	      2020 CSM 1001

*/
#include<bits/stdc++.h>
#define pf printf
#define sf scanf
using namespace std;
typedef struct node  // A Dynamic min heap
{
        char ch;
        int freq;
        struct node *left;
        struct node *right;
}node;

node * heap[200];
int heapSize=0;

void Insert(node * element)   // insertion code in heap
{
        heapSize++;
        heap[heapSize] = element;
        int now = heapSize;
        while(heap[now/2] -> freq > element -> freq)
        {
                heap[now] = heap[now/2];
                now /= 2;
        }
        heap[now] = element;
}
node * DeleteMin()
{
        node * minElement,*lastElement;
        int child,now;
        minElement = heap[1];
        lastElement = heap[heapSize--];
        for(now = 1; now*2 <= heapSize ;now = child)
        {
             child = now*2;
                 if(child != heapSize && heap[child+1]->freq < heap[child] -> freq )
                {
                        child++;
                }
                if(lastElement -> freq > heap[child] -> freq)
                {
                        heap[now] = heap[child];
                }
                else
                {
                        break;
                }
        }
        heap[now] = lastElement;
        return minElement;
}
struct Adi   // just for some ref i needed at later
{
    char c;
    string code;
};
Adi myAns[128];
map<char,string> freq_data; // map to store char string pair
map<string,char> reverse_data;// same but in reverse and its a hashmap
bool myfun(Adi x,Adi y)  // to sort the output so that a comes first and z at last
{
    return x.c<y.c;
}
int a=0;
void print(node *temp,char *code)  // for printing the binary code
{
        if(temp->left==NULL && temp->right==NULL)
        {
                reverse_data[code]=temp->ch;
                freq_data[temp->ch]=code;
                myAns[a].c=temp->ch;
                myAns[a++].code=code;
                return;
        }
        int length = strlen(code);
        char leftcode[100],rightcode[100];
        strcpy(leftcode,code);
        strcpy(rightcode,code);
        leftcode[length] = '0';
        leftcode[length+1] = '\0';
        rightcode[length] = '1';
        rightcode[length+1] = '\0';
        print(temp->left,leftcode);
        print(temp->right,rightcode);
        }

int main()
{
	int choice;
	pf("Enter 1 or 2:\n");
	sf("%d",&choice);
	if(choice==1)
	{
           heap[0] = (node *)malloc(sizeof(node));  /* just for a ref to the node i delete this at the time of processing*/
           heap[0]->freq = 0;
        	  int n ;
        	  pf("You entered a 1:\n");
           pf("Enter character-frequency table:\n");
           char ch;
           int freq,i;
           n=0;
           while(sf("%c%d",&ch,&freq)!=EOF)
             {
               	n++;
               	if(ch=='\n'|| ch=='\t') // as \n also a character
               	{
               	n--;
               	continue;
       	         }
                node * temp = (node *) malloc(sizeof(node));
                temp -> ch = ch;
                temp -> freq = freq;
                temp -> left = temp -> right = NULL;
                Insert(temp);
             }
             pf("Huffman code table is as follows:\nChar\tcodeword \n");
           if(n==1)
                {
                pf("%c\t%d\n",ch,freq);
                return 0;
                }
          for(i=0;i<n-1 ;i++) // doing the procedure mentioned in ClRS book
               {
                node * left = DeleteMin();
                node * right = DeleteMin();
                node * temp = (node *) malloc(sizeof(node));
                temp -> ch = 0;
                temp -> left = left;
                temp -> right = right;
                temp -> freq = left->freq + right -> freq;
                Insert(temp);
               }
              node *tree = DeleteMin();
             char code[100];
             code[0] = '\0';  // for printing that part


             print(tree,code);
     sort(myAns,myAns+n,myfun);
		for(int i=0;i<n;i++)
		{
		cout<<myAns[i].c<<"\t"<<myAns[i].code<<endl;
		}



          }
// main part
else if(choice==2)
      {
    pf("\nYou entered a 2:\n");
fstream file;
string filename="data.txt",word;
unordered_map<char,int> mp;
int space =0;
file.open(filename.c_str());
          while(!file.eof()) {


                getline(file,word);//take word and print
      for(int i=0;i<word.size();i++)
      {
          mp[word[i]]++;
      }
      mp[10]++;  // new line character
   }
   file.close();
   filename="FrequencyData.txt";
   file.open(filename,ios::out);
   string str;
   str.clear();
   int n=0;
   heap[0] = (node *)malloc(sizeof(node));
   heap[0]->freq = 0;
   for(int i=0;i<128;i++)
   {
       if(mp[i]!=0)
       {
           char tt=char(i);
           str.push_back(tt);
           str.push_back('\t');
           str.append(to_string(mp[i]));
           file<<str<<endl;
           str.clear();
n++;
           node * temp = (node *) malloc(sizeof(node));
                temp -> ch = tt;
                temp -> freq = mp[i];
                temp -> left = temp -> right = NULL;
                Insert(temp);

       }



   }
   file.close();
   for(int i=0;i<n-1 ;i++)
               {
                node * left = DeleteMin();
                node * right = DeleteMin();
                node * temp = (node *) malloc(sizeof(node));
                temp -> ch = 0;
                temp -> left = left;
                temp -> right = right;
                temp -> freq = left->freq + right -> freq;
                Insert(temp);
               }
              node *tree = DeleteMin();
             char code[100];
             code[0] = '\0';


             print(tree,code);


sort(myAns,myAns+n,myfun);

filename="HuffmanCodeData.txt";
file.open(filename,ios::out);
str.clear();
for(int i=0;i<n;i++)
{
    str.push_back(myAns[i].c);
    str.push_back('\t');
    str.append(myAns[i].code);
    file<<str<<endl;
    str.clear();
}
file.close();
filename="data.txt";
file.open(filename.c_str());
fstream en;
en.open("EncodedData.txt",ios::out);
while(!file.eof())
{
    getline(file,word);
for(int i=0;i<word.size();i++)
{
    str=freq_data[word[i]];
    en<<str<<" ";
}
en<<freq_data['\n']<<" ";


}
en.close();
filename="EncodedData.txt";
en.open(filename.c_str());
file.close();
file.open("DecodedData.txt",ios::out);
while(en>>word)
{
    char c=reverse_data[word];
   file<<c;

}
file.close();

cout<<"everything has completed.....\n";
 }
return 0;
}
