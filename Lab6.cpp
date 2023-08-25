#include<iostream>
using namespace std;
#define INF_MAX 999999
#define MVNUM 100
#define OK 1
#define ERROR 0
#define MAXSIZE 1000
typedef int VRType;            //顶点的数据类型
typedef int ArcType;           //权值数据类型
typedef int Status;
typedef int VerTexType;
//邻接矩阵和顶点表
typedef struct ArcCell {
	VRType vexs[MVNUM];        //顶点表
	ArcType arcs[MVNUM][MVNUM];//权值矩阵
	int vexnum, arcnum;        //图的当前顶点数和边数
}AMGraph;
AMGraph G;
int visited[MVNUM];
//辅助数组初始化 
void Energy(int visited[], AMGraph G) {
	for (int i = 0; i < G.vexnum; i++)
		visited[i] = false;
}
//克鲁斯卡尔算法的存储边信息的数组
typedef struct {
	int begin;
	int end;
	int weight;
}Edge;
//取顶点编号函数
int LocateVex(AMGraph G, VRType v) {
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i]) return i;
	}
	return -1;
}
//无向网的构建(邻接矩阵)
Status CreatUDN(AMGraph& G) {
	int v1, v2; int w;
	cout << "请输入无向图的顶点数和边段数:";
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++)  G.vexs[i] = i;
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j] = INF_MAX;
		}
	for (int k = 0; k < G.arcnum; k++) {
		cout << "请输入第" << k << "边及其权值:";
		cin >> v1 >> v2 >> w;
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}
//深度优先搜索(邻接矩阵）
void DFS(AMGraph G, int v) {
	//int visited[G.vexnum];
	cout << v << ','; visited[v] = true;
	for (int w = 0; w < G.vexnum; w++) {
		if ((G.arcs[v][w] != INF_MAX) && (visited[w]) == 0)
			DFS(G, w);
	}
}
//循环队列的基本操作
typedef struct duilie {
	Status data[MAXSIZE];
	int front;
	int rear;
}ddd;

ddd Q;
//初始化一个空队列
void InitQueue(ddd& Q)
{
	Q.front = 0;
	Q.rear = 0;
}

//判断队列是否为空
Status QueueEmpty(ddd Q) {
	if (Q.front == Q.rear) return OK;
	else
		return ERROR;
}

//返回Q的元素个数，也就是队列的当前长度
int QueueLength(ddd Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//入队
void EnQueue(ddd& Q, Status& e) {
	if ((Q.rear + 1) % MAXSIZE == Q.front) {/*队列满的判断*/
		cout << "队满" << endl;
		return;
	}
	Q.data[Q.rear] = e;  //将元素e赋值给队尾
	Q.rear = (Q.rear + 1) % MAXSIZE; //rear指针向后移一个位置，在末尾则转到数组头部
}

//出队
void DeQueue(ddd& Q, Status& e)
{
	if (Q.front == Q.rear) {
		cout << "队空" << endl;
		return;
	}
	e = Q.data[Q.front]; //将队头元素赋值给e
	Q.front = (Q.front + 1) % MAXSIZE; //front指针向后移一位置，若到最后转到数组头部
}

//广度优先搜索(邻接矩阵）
void BFS(AMGraph G, int v) {
	Status u;
	for (int i = 0; i < G.vexnum; i++) visited[i] = false;
	cout << v << ','; visited[v] = true;
	InitQueue(Q);  //初始化一个空队列（循环队列）
	EnQueue(Q, v); //入队
	while (!QueueEmpty(Q)) {
		DeQueue(Q, u);
		for (int i = 0; i < G.vexnum; i++) {
			if (!visited[i] && G.arcs[u][i] != INF_MAX) {
				cout << G.vexs[i] << ','; visited[i] = true; EnQueue(Q, G.vexs[i]);
			}
		}
	}
	cout << endl;
}
//构造的一个辅助数组两个域分别用来存储权值和边
struct dd {
	VRType adjvex;
	ArcType lowest;
};  dd closedge[MVNUM];

//求U和V-U的最小权值的对应边
int minimum(dd closedge[]) {
	double min1 = INF_MAX; int k = -1;
	for (int i = 0; i < G.vexnum; i++) {
		if (closedge[i].lowest < min1 && closedge[i].lowest>0) {
			min1 = closedge[i].lowest;
			k = i;
		}
	}
	return k;
}
//普里姆算法构建最小生成树
void MiniSpanTree_PRIM(AMGraph G, VRType u) {
	int k = LocateVex(G, u);
	for (int j = 0; j < G.vexnum; j++) //辅助数组初始化
		if (j != k) closedge[j] = { u,G.arcs[k][j] };
	closedge[k].lowest = 0;          //初始，U={u}
	for (int i = 0; i < G.vexnum - 1; i++) {
		k = minimum(closedge);       //求出T的下一个节点，第k个节点
		if(closedge[k].adjvex<G.vexs[k])
		cout << closedge[k].adjvex << "-" << G.vexs[k] << ",";//输出生成树的边
		else
			cout << G.vexs[k] << "-" << closedge[k].adjvex << ",";
		closedge[k].lowest = 0;     //第k个顶点并入U集
		for (int j = 0; j < G.vexnum; j++) {
			if (G.arcs[k][j] < closedge[j].lowest)
				closedge[j] = { G.vexs[k],G.arcs[k][j] };//新顶点并入U后重新选择最小边
		}
	}
	cout << endl;
}
//初始化edges数组和升序排列 
void OperationEdge(AMGraph G, Edge* edges)
{
	int i, j, k;
	k = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = i + 1; j < G.vexnum; j++)//只需要转化邻接矩阵的一半，无向图
		{
			if (G.arcs[i][j] != INF_MAX && G.arcs[i][j] != 0)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arcs[i][j];
				k++;
			}
		}
	}
	for (i = 0; i < k - 1; i++)//简单交换排序
	{
		for (j = i + 1; j < k; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				Edge tmp;
				tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
	for (int m = 0; m < k; m++) {
		if (edges[m].begin > edges[m].end) {
			VRType swap = edges[m].end;
			edges[m].end = edges[m].begin;
			edges[m].begin = swap;
		}
	}
}
//查询函数
int Find(int* parent, int f)
{
	while (parent[f] > 0)
	{
		f = parent[f];
	}

	return f;
}
//克鲁斯卡尔算法
void MiniSpanTree_Kruskal(AMGraph G)
{
	int m, n, k = 0;
	Edge edges[MVNUM];//定义边集数组
	int parents[MVNUM];//该数组用来判断边与边是否形成环路
	OperationEdge(G, edges);
	for (int i = 0; i < G.vexnum; i++)
		parents[i] = 0;
	int cou = 0;
	for (int i = 0; i < G.vexnum; i++)//循环每一条边
	{
		if (cou == G.vexnum - 1) {
			cout << "最小生成树构造完成！！！" << endl;
			break;
		}
		n = Find(parents, edges[i].begin);
		m = Find(parents, edges[i].end);
		if (m != n)//如果m != n，说明此边没有和现有生成树形成环路
		{
			cou++;
			parents[n] = m;
			cout << edges[i].begin << "-" << edges[i].end << ',';
		}
	}
	cout << endl;
}

//迪杰斯特拉算法计算最短路径
void ShortestPath_DIJ(AMGraph G, int v0)//用Dijkstra算法求有向图G的v0到其余顶点的最短路径 
{
	int i, n, v, min, w;//下面所用到的所有变量 
	n = G.vexnum;//顶点个数 
	bool S[MVNUM];//辅助数组S[]的定义 
	int D[MVNUM], Path[MVNUM];//辅助数组D[]和Path[]的定义 
	for (v = 0; v < n; v++)//辅助数组的初始化 
	{
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if (D[v] < INF_MAX)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;//初始化结束 
	for (i = 1; i < n; i++)//对其余n-1个顶点，依次进行计算 
	{
		min = INF_MAX;//暂定最小权值 
		for (w = 0; w < n; w++)
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];//选择一条从v0出发的最短路径，终点为v 
			}
		S[v] = true;//用于记录已选择过 
		for (w = 0; w < n; w++)//更新从v0出发到集合V-S上所有顶点的最短路径长度 
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];//更新D[w] 
				Path[w] = v;//更新w的前驱为v 
			}
	}
	//打印辅助数组最后结果 
	for (i = 1; i < n; i++)//打印D[] 
		cout << "=:0到" << i << "的长度" << D[i] << endl;
	printf("\n");
}
int main() {
	int v = 0, u = 0;
	CreatUDN(G);
	Energy(visited, G);
	cout << "输出深度优先遍历结果=:";
	DFS(G, v);
	cout << endl;
	cout << "输出广度优先遍历结果=:";
	BFS(G, v);
	cout << "输出普里姆算法构建最小生成树=:";
	MiniSpanTree_PRIM(G, u);
	cout << "输出克鲁斯卡尔算法构建最小生成树=:";
	MiniSpanTree_Kruskal(G);
	cout << "输出迪杰斯特拉算法构建最小生成树" << endl;
	ShortestPath_DIJ(G, v);
	return 0;
}

