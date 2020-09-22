/**
 * 郭志
 * 517021910503
 * */

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct huffman_node
{
	char id;
	int freq;
	string code;
	huffman_node* left;
	huffman_node* right;
	huffman_node(): left(NULL), right(NULL){}
};

typedef huffman_node *node_ptr;


class Solution{

    string srcFileName, indexFileName, resultFileName;
    fstream srcFileStream, indexFileStream, resultFileStream;
    node_ptr huffmanTree;
    //节点信息表
    node_ptr node_array[256];
    unordered_map<char, string> coding_table;
    char id;
    int maxDepth=0;
    unsigned long long total_byte_number=0;
	class compare
	{
	public:
		bool operator()(const node_ptr& c1, const node_ptr& c2) const
		{
            // ascll 值小的字符应该尽量放在前面,生成树的时候会进入左子树
			return c1->freq > c2->freq || (c1->freq==c2->freq && c1->id>c2->id);
		}
	};
    //priority queue of frequency from low to high
	priority_queue<node_ptr, vector<node_ptr>, compare> freqTable;

    void create_node_array()
    {
        for (int i = 0; i < 256; i++)
        {
            node_array[i] = new huffman_node;
            node_array[i]->id = i;
            node_array[i]->freq = 0;
        }
    }

    int binary_to_decimal(string& in)
    {
        int result = 0;
        for (int i = 0; i < in.size(); i++)
            result = result * 2 + in[i] - '0';
        return result;
    }

    void print_table(){
        priority_queue<node_ptr, vector<node_ptr>, compare> temp(freqTable);
        cout<<temp.size()<<endl;
        while(temp.size()>3){
            temp.pop();
        }
        vector<node_ptr> arrays;
        while(temp.size()>0){
            node_ptr node=temp.top();
            temp.pop();
            arrays.push_back(node);
        }
        for(int i=0;i<arrays.size();++i){
            //从大到小打印
            cout<<arrays[arrays.size()-1-i]->id<<" "<<arrays[arrays.size()-1-i]->freq<<endl;
        }
    }

    void traverse(node_ptr node, string code)
    {
        if (node->left == NULL && node->right == NULL)
        {
            node->code = code;
            coding_table[node->id]=code;
            maxDepth=max(maxDepth, int(code.size()));
        }
        else
        {
            // 左子树加0, 右子树加1
            traverse(node->left, code + '0');
            traverse(node->right, code + '1');
            //node->id = min(node->left->id, node->right->id);
            coding_table[node->id]=code;
        }
    }

    void print_tree(){
        cout<<maxDepth<<endl;
    }

    void print_code(){
        cout<<coding_table['e']<<endl;
    }
    
    void write_code(){
        indexFileStream.open(indexFileName, ios::out);
        for(int i=0;i<256;++i){
            char ch;
            string ch_code;
            if(node_array[i]->freq!=0){
                ch=node_array[i]->id;
                ch_code=node_array[i]->code;
                indexFileStream<<ch<<" "<<ch_code<<endl;
            }
        }
        indexFileStream.close();
    }

    void look_table(){
        priority_queue<node_ptr, vector<node_ptr>, compare> temp(freqTable);
        while(temp.size()>0){
            node_ptr node=temp.top();
            temp.pop();
            cout<<node->id<<" "<<node->freq<<" "<<node->code<<endl;
        }
    }

    void cal_total_byte_number(){
        total_byte_number=0;
        priority_queue<node_ptr, vector<node_ptr>, compare> temp(freqTable);
        while(temp.size()>0){
            node_ptr node=temp.top();
            temp.pop();
            total_byte_number+=(node->freq*(node->code.size()));
        }
    }


    // 将有效比特数转为小端字符格式
    vector<char> convert_byte_number(){
        unsigned long long res1=0,res2=0, prior= total_byte_number;
        vector<char> ans;
        for(int i=1;i<=64;i+=8){
            char ch= prior&0xff;
            prior=prior>>8;
            ans.push_back(ch);
        }

        return ans;
    }

    void print_byte_number(){
        cout<<total_byte_number<<endl;
    }

public:
    Solution(string s1, string s2, string s3): srcFileName(s1),  indexFileName(s2), resultFileName(s3){
        create_node_array();
    }

    void do_statistics(){
        srcFileStream.open(srcFileName, ios::in);
        srcFileStream.get(id);
        while(!srcFileStream.eof())
        {
            node_array[id]->freq++;
            srcFileStream.get(id);
        }
        srcFileStream.close();
        for(int i=0;i<256;++i){
            if(node_array[i]->freq){
                freqTable.push(node_array[i]);
            }
        }

        print_table();
    }
    
    void build_tree(){
        priority_queue<node_ptr, vector<node_ptr>, compare> temp(freqTable);
        while (temp.size() > 1)
        {
            //建立哈夫曼树,队列前面的放左子树
            huffmanTree = new huffman_node;
            huffmanTree->freq = 0;
            huffmanTree->left = temp.top();
            huffmanTree->freq += temp.top()->freq;
            temp.pop();
            huffmanTree->right = temp.top();
            huffmanTree->freq += temp.top()->freq;
            temp.pop();
            //一个树的 ASCII 码，为这个树中所有节点的 ASCII 码的最小值
            huffmanTree->id = min(huffmanTree->left->id, huffmanTree->right->id);
            temp.push(huffmanTree);
        }

        traverse(huffmanTree, "");
        print_tree();
    }

    void encode(){
        //look_table();
        print_code();
        write_code();
    }

    void compress(){
        srcFileStream.open(srcFileName, ios::in);
        resultFileStream.open(resultFileName, ios::out|ios::binary);
        string in="", s="";

        cal_total_byte_number();
        print_byte_number();
        vector<char> chs=convert_byte_number();
        for(auto ch: chs)
            in+=(char) ch;
        
        srcFileStream.get(id);
        /**
         * 8个bit为一组,当累计到8个bit时,转换为对应的char, 添加到结果中
         * */
        while(!srcFileStream.eof())
        {
            s += node_array[id]->code;
            while (s.size() > 8)
            {
                string tmp = s.substr(0,8);
                in += (char)binary_to_decimal(tmp);
                s = s.substr(8);
            }
            srcFileStream.get(id);
	    }

        int count = 8 - s.size();
        //在后面以二进制 0 进行补足
        if (s.size() < 8)
        {
            s.append(count, '0');
        }
        in += (char)binary_to_decimal(s);

        resultFileStream.write(in.c_str(), in.size());
        srcFileStream.close();
        resultFileStream.close();
    }

    void run(){
        do_statistics();
        build_tree();
        encode();
        compress();
    }

};


int main(int argc, char *argv[]){
    if(argc!=4){
        cout<<"Usage: \n ./a.out sample.txt sample.huffidx sample.huffzip"<<endl;
        exit(1);
    }

    Solution solu(argv[1], argv[2], argv[3]);
    solu.run();
    return 0;
}