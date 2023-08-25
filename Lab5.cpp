#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<string>
using namespace std;

typedef struct {
	double weight;
	int parent, lch, rch;
}HTNode,*HuffmanTree;

typedef  struct art//定义结点类型 
{
    char*  code;  //huffman编码
	char letter;  //代表符号
	int   num;   //出现次数
}ART,*INK;

typedef char** HuffmanCode;

void Select(HuffmanTree HT, int n, int& s1, int& s2) {
	long int min1 = 1000000000, min2 = 1000000000,k,j;
	for (int i = 1; i <= n; i++) {
		if (HT[i].parent == 0) {
			if (HT[i].weight <min1) {
				min1=HT[i].weight;
				k=i;
			}
		}
	}
		s1 = k;
		//cout<<s1<<endl;
		for (int i = 1; i <= n; i++) {
			if (HT[i].parent == 0 &&i!=k ) {
				if (HT[i].weight < min2) {
				min2 = HT[i].weight;
				j=i;
			}
			}
		}
		s2 = j;
		//cout<<s2<<endl;
	}
	//将输入频率不为0的字母或者空格赋值进入栈中 
void inputp(INK &P,int &n){
	P=new ART[28];
	int m1;n=0;char a[28]={'#',' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for(int i=1;i<=27;i++){
		cin>>m1;
		if(m1!=0){
		n++;
		P[n].letter =a[i];
		P[n].num=m1;
	}
	}
}

//计算总字符个数 
int CharCount(INK P,int n){
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=P[i].num;
	}
	return sum;
}

//构造哈夫曼树——哈夫曼算法初始化
void CreatHuffmanTree(HuffmanTree &HT, int n,INK P,double &WPL) {
	int m,s1,s2;WPL=0;
	if (n <= 1)return;
	m = 2 * n - 1;   //数组共2n-1个元素
	HT = new HTNode[m + 1]; //0号单元未用，HT[m]表示根结点
	for (int i = 1; i <= m; ++i) { //将2n-1个元素的lch、rch、parent置为0 
		HT[i].lch = 0; HT[i].rch = 0; HT[i].parent = 0;
	}
	for (int i = 1; i <= n; ++i) {
		//cout << "输入第" << i << "片叶子的权重" << endl;
		HT[i].weight=P[i].num;//输入前n个元素的weight值
	}
	//初始化结束，下面开始建立哈夫曼树
	for (int i = n+1; i <= m; i++) {
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lch = s1; HT[i].rch = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		WPL+=HT[i].weight;
	}
	//cout << "哈夫曼树的最终值" << HT[m].weight << endl;
}

void CreatHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n,INK &P) {
	int start,c,f;//从叶子到根逆向求每个字符的哈夫曼编码，存放在编码表HC中
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));    //HC = new char* [n + 1];             
	char *cd = (char*)malloc(n * sizeof(char));                 //cd = new char[n];                 
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		start = n - 1; c = i; f = HT[i].parent;
		while (f != 0) {
			--start;
			if (HT[f].lch == c) cd[start] = '0';
			else cd[start] = '1';
			c = f; f = HT[f].parent;
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
		P[i].code=HC[i];      //记录下每一个空格或者字母的编码 
	}
	free(cd);
}
//输出叶子的哈夫曼编码 
void show(INK P,int n){
	printf("字母   权值    编码\n");
	for(int i=1;i<=n;i++){
		cout<<P[i].letter<<"      "<<P[i].num<<"       "<<P[i].code<<endl;
	}
} 
//给定小段文字的二进制编码 
void CreatINK(INK P,int n,string c){
	cout<<"输出二进制编码=："; 
	int j=0;
	while(c[j]!='\n'){
		for(int i=1;i<=n;i++){
			if(c[j]==P[i].letter){
			cout<<P[i].code;
			break;
		}
		}
		j++;
	}
	cout<<endl;
} 
//输入输出流
void inputc(string &c){
	c="\n";
	getline(cin,c);       //清除cin的iostream的输入缓存 
	getline(cin,c);
} 
int main() {// 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 0 0 1 1 1 0 0 1 1 输入样例 
            // aazy
    int n;double sum1,WPL;HuffmanCode HC;HuffmanTree HT;string s;INK P;
	cout << "输入哈夫曼树频率数：" << endl;
	inputp(P,n);sum1=CharCount(P,n);
	string c,c1;char cs;
	inputc(c);
	c1=c+'\n';
	cout<<"输出总字符个数=："<<sum1<<endl;
	CreatHuffmanTree(HT,n,P,WPL);
	cout<<"输出WPL=："<<WPL<<endl;
	cout<<"输出平均每个字符比特值=："<<(WPL/sum1)<<endl;
	CreatHuffmanCode(HT, HC, n,P);
	//show(HT,HC,n);
	CreatINK(P,n,c1);
	cout<<"输出译文=："<<c<<endl;
	//show(P,n); 
	return 0;
}
