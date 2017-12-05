#include "Manager.h"
#include <cstring>
#include <fstream>
#include "strSplit.h"
#include "fileParser.h"
Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    ferr.open(ERROR_LOG_PATH);

		fstream cmd;
		cmd.open(filepath);
		if (cmd.fail()) return;
		string * t;
		string * param;
		while (t = fileParser(cmd))
		{
			if (t[0] == "LOAD") {
				Load(t[1].c_str());
				
			}
			else if (t[0] == "PRINT") {
				Print();
			}
		}
		system("pause");
}
void Manager::PrintError(Result result)
{
    ferr << "Error code: " << result << std::endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
	fstream loadfile;
	loadfile.open(filepath);
	if (loadfile.fail()) return Result::LoadFileNotExist;
	string * t, * param;
	t = fileParser(loadfile);	// Size of Graph
	int size = stoi(t[0]);
	int i = 0;
	for (i = 0; i < size; i++) {
		m_graph.AddVertex(i);
	}
	i = 0;
	while (t = fileParser(loadfile)) {
		for (int j = 0; j < size; j++) {
			if(i!=j)
				m_graph.AddEdge(i, j, stoi(t[j]));
		}
		i++;
	}

	return Result::Success;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
	if (m_graph.isEmpty()) return Result::GraphNotExist;
	else {
		m_graph.Print(fout);
		return Result::Success;
	}

}
/// <summary>
/// find the path from startVertexKey to endVertexKey with DFS (stack)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	return Result::Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{

	return Result::Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	return Result::Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	return Result::Success;
}
