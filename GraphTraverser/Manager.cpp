#include "Manager.h"
#include <cstring>
#include <fstream>
#include "strSplit.h"
#include "fileParser.h"
#include <stack>
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
		Result result;
		fstream cmd;
		cmd.open(filepath);
		if (cmd.fail()) {
			fout << "====== SYSTEM ======" << endl;
			fout << "CommandFileNotExist" << endl;
			fout << "====================" << endl;
			PrintError(Result::CommandFileNotExist);
			return;
		}
		string * t;
		string * param;
		while (t = fileParser(cmd))
		{
			if (t[0] == "LOAD") {
				result = Load(t[1].c_str());	
			}
			else if (t[0] == "PRINT") {
				result = Print();
			}
			else if (t[0] =="DFS") {
				result = FindPathDfs(stoi(t[1]), stoi(t[2]));
			}
			else if (t[0] == "DIJKSTRA") {
				result = FindShortestPathDijkstraUsingSet(stoi(t[1]), stoi(t[2]));
			}
			else {
				result = Result::NonDefinedCommand;
			}

			if (result == Result::Success) {
				if (t[0] == "LOAD") {
					fout << "======" << t[0] << "======" << endl;
					fout << "Success" << endl;
					fout << "====================" << endl;
				}
			}else if (result == Result::NonDefinedCommand) {
				fout << "======" << t[0] << "======" << endl;
				fout << "CommandFileNotExist" << endl;
				fout << "====================" << endl;
			}
			else if (result == Result::VertexKeyNotExist) {
				fout << "====== SYSTEM ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "====================" << endl;
			}
			else if (result == Result::InvalidAlgorithm) {
				fout << "====== SYSTEM ======" << endl;
				fout << "InvalidAlgorithm" << endl;
				fout << "====================" << endl;
			}
			else if (result == Result::GraphNotExist) {
				fout << "====== SYSTEM ======" << endl;
				fout << "GraphNotExist" << endl;
				fout << "====================" << endl;
			}
			else if (result == Result::InvalidVertexKey) {
				fout << "====== SYSTEM ======" << endl;
				fout << "InvalidVertexKey" << endl;
				fout << "====================" << endl;
			}
			else if (result == Result::NegativeCycleDetected) {
				fout << "====== SYSTEM ======" << endl;
				fout << "NegativeCycleDetected" << endl;
				fout << "====================" << endl;
			}
			else {
				fout << "====== SYSTEM ======" << endl;
				fout << "UnKnownError" << endl;
				fout << "====================" << endl;
			}

		}
		system("pause");
}
void Manager::PrintError(Result result)
{
		std::cout << "Error code: " << result << std::endl;
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
	m_graph._initAdj(size);
	for (i = 0; i < size; i++) {
		m_graph.AddVertex(i);
	}
	i = 0;
	while (t = fileParser(loadfile)) {
		for (int j = 0; j < size; j++) {
			if (i != j && stoi(t[j]) != 0)
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
	try {
		m_graph.Print(fout);
		return Result::Success;
	}
	catch (int err) {
		return (Result)err;
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
	try {
		std::vector<int> dist = m_graph.FindPathDfs(startVertexKey, endVertexKey);
		std::vector<int>::iterator i;
		fout << "====== DFS ======" << endl;
		for (i = dist.begin(); i != dist.end(); i++) {
			fout << (*i) << " ";
		}
		fout << endl;
		fout << "===================" << endl;
		return Result::Success;
	}
	catch (int err) {
		return (Result)err;
	}
	
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
	try {
		std::vector<int> dist = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);
		fout << "====== DIJKSTRA ======" << endl;
		std::vector<int>::iterator i;
		for (i = dist.begin(); i != dist.end(); i++) {
			fout << (*i) << " ";
		}
		fout << endl;
		fout << "===================" << endl;
		return Result::Success;
	}
	catch (int err) {
		return (Result)err;
	}
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
	fout << "====== DIJKSTRAMIN ======" << endl;
	fout << "±¸Çö ¾ÈµÊ" << endl;
	fout << "===================" << endl;
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
	fout << "====== BellmanFord ======" << endl;
	fout << "±¸Çö ¾ÈµÊ" << endl;
	fout << "===================" << endl;
	return Result::Success;
}
