#include <vector>
#include <iostream>
#include <fstream>
#include <queue>


class Vertex
{
public:
	int const id;
	Vertex(int id) :id(id)
	{

	}
};
class Edge
{
public:
	const Vertex &from, &to;
	int w;
	Edge(Vertex& v1, Vertex& v2, int w) :from(v1), to(v2), w(w)
	{
			
	}
	Edge(Vertex& v1, Vertex& v2) :from(v1), to(v2), w(1)
	{

	}

};
class Graph
{
public:
	std::vector<Vertex> nodes;
	std::vector<std::vector<Edge*>> esFrom;

	std::vector<Edge*> edges;
	

	Graph(int n)
	{
		//nodes.resize(n);
		for (int i = 0; i < n; i++)
		{
			nodes.push_back(Vertex(i));
		}
		esFrom.resize(n);
	}
	void AddEdge(int from,int to)
	{
		if (from == to) return;
		Edge* e = new  Edge(nodes[from], nodes[to]);
		edges.push_back(e);
		
		esFrom[from].push_back(edges.back());
		esFrom[to].push_back(edges.back());
		
	}

	std::wofstream f;
	void WriteGraph(std::string fileName)
	{
		f = std::wofstream(fileName);
		f << "window.prog=`\n";
		for (auto &n : nodes)
		{
			f << n.id << std::endl;
		}
		for (auto& e : edges)
		{
			f << e->from.id <<"-" <<e->to.id << std::endl;
		}
		f << "draw\n";
	}

	void WriteEnd()
	{
		f << "`\n";
		f.close();
	}

	void RunAlgoritm(int start)
	{
		auto visited =std::vector <bool>(nodes.size(),false) ;
		BFS(start, visited);
	}
	void BFS(int start, std::vector <bool>& visited)
	{
		std::queue<int> q;
		q.push(start);              //в качестве начальной вершины используем 0.
		visited[start] = true;
		f << start << ",color=yellow\n";
		f << "w,500\n";
		while (!q.empty()) {
			int cur = q.front();  //извлекаем из очереди текущую вершину
			q.pop();
			f << cur << ",color=grey\n";
			f << "w,500\n";
			//Здесь должна быть обработка текущей вершины.
			//cout << "BFS at vertex " << cur + 1 << endl;
			for (Edge* e : esFrom[cur])
			{
				const Vertex sosed = (e->from.id == cur) ? e->to : e->from;

				int eid = sosed.id;


				if (!visited[eid])
				{
					//f << eid << ",color=yellow\n";
					//f << "w,500\n";
				
					q.push(eid);

					visited[eid] = true;
					//f << eid << ",color=blue\n";
				}

			}
			
		}
		
	}
	void RunRecursive(int v,std::vector <bool>& visited)
	{
		for (Edge *e : esFrom[v])
		{
			const Vertex& sosed = (e->from.id == v) ? e->to : e->from;

			int eid = sosed.id;
			
			if (!visited[eid])
			{
				visited[eid] = true;
				f << eid << ",color=yellow\n";
				f <<"w,500\n";
				RunRecursive(eid,visited);
				visited[eid] = false;
				f << eid << ",color=blue\n";
			}
		}
	}




/*
	~Graph()
	{
		for (int i = 0; i < edges.size(); i++)
		{
			delete edges[i];
		}
	}
*/
};